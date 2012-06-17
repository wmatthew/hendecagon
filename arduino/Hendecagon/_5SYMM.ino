//==========================================================
// Game: Symmetry
#define SYMM_PHASE_DRAW    1
#define SYMM_PHASE_PICK    2
#define SYMM_PHASE_EVAL    3
#define SYMM_PHASE_OUTCOME 4

int symmScore;
int symmOneTap[10]  = {107, 219, 163, 119, 27, 51, 339, 165, 93, 45 };
int symmTwoTaps[10] = {299, 203, 157, 139, 77, 87,  43,  79, 39, 83 };
bool symmPattern[NUM_INPUTS];
bool symmRobotPlan[NUM_INPUTS];
int symmCenter;
int symmTestIndex;
int symmBlink;

// Round 1: human fixes pattern (2 choices)
// Round 2: human fixes pattern (2 choices)
// Round 3: human fixes pattern (1 choice)
// Round 4: computer fixes human's pattern

void setupGameSymm() {
  //Serial.println("Setup Game: Symmetry");
  symmScore = 0;
  startSymmRound();
}

void startSymmRound() {
  Serial.print("Starting Symm. Score: ");
  Serial.println(symmScore);
  gamePhase = SYMM_PHASE_DRAW;
  userEvent();
  paintOff();
  for (int i=0; i<11; i++) {
     symmPattern[i] = false;
  }
  if (isHumanDrawing()) {
    snapTo(YELLOW);
  } else {
    snapTo(BLUE);
    int value = symmScore <= 1 ? symmTwoTaps[random(10)] : symmOneTap[random(10)];
    int shift = random(11);
    bool invert = random(2);
    bool reverse = random(2) == 0;
    for (int i=0; i<11; i++) {
      int index = (i + shift)%11;
      if (reverse) index = 10-index;
      symmRobotPlan[i] = (((value >> index) & 1) == invert);
    }  
  }
}

bool tickGameSymm() {

  if (gamePhase == SYMM_PHASE_DRAW) {
    if (timeSinceUserEvent() > 10000) {
      snapTo(isHumanDrawing() ? BLUE : YELLOW);
      gamePhase = SYMM_PHASE_PICK;
      userEvent();
    } else if (timeSinceUserEvent() > 8000) {
      if (timeSinceAnimEvent() > 100) {
        animEvent();
        symmBlink = (symmBlink + 1) % 2;
        snapTo(symmBlink == 0 ? OFF : isHumanDrawing() ? YELLOW : BLUE);
      }
    }

    // Computer draws design
    if (!isHumanDrawing() && timeSinceAnimEvent() > 500) {
      animEvent();
      if (timeSinceUserEvent() < 4000) {
        // draw randomly
        symmFlip(random(11));     
      } else {
        // actually draw design
        int rand = random(11);
        for (int i=0; i<11; i++) {
          int index = (rand + i) % 11;
          if (symmPattern[index] != symmRobotPlan[index]) {
            symmFlip(index);
            break;
          }
        }
      }
      symmRedraw();
    } 

    if (isHumanDrawing() && wasExactlyOnePressed()) {
      int press = getPressed();
      symmFlip(press);
      symmRedraw();      
    }
  }
  
  if (gamePhase == SYMM_PHASE_PICK) {
    int pick = NO_INPUTS;
    if (isHumanDrawing() && timeSinceUserEvent() > 2000 ) {
      pick = symmRobotPick();
    } else if (!isHumanDrawing() && wasExactlyOnePressed()) {
      pick = getPressed();
    }
    
    if (pick != NO_INPUTS) {
      symmFlip(pick);
      symmRedraw();
      symmCenter = symmFindCenter();      
      snapTo(OFF);
      gamePhase = SYMM_PHASE_EVAL;
      symmTestIndex = 0;
      symmBlink = 0;    
      animEvent();
      userEvent();
    }
  }

  if (gamePhase == SYMM_PHASE_EVAL) {
    if (timeSinceAnimEvent() > 100 && timeSinceUserEvent() > 700) {
      animEvent();
      symmBlink = (symmBlink+1) % 8;

      int a = (symmCenter + symmTestIndex + 11 ) % 11;
      int b = (symmCenter - symmTestIndex + 11 ) % 11;
      paint(a, (symmBlink%2==0) ? WHITE : OFF );
      paint(b, (symmBlink%2==0) ? WHITE : OFF );

      if (symmBlink == 0) {
        if (symmPattern[a] != symmPattern[b]) {
          // INCORRECT
          paintOnly(a, RED);
          paint(b, RED);
          gamePhase = SYMM_PHASE_OUTCOME;
          if (isHumanDrawing()) {
            Serial.println("SYMM: Computer was stumped");
            snapTo(GREEN);          
            symmScore ++;
            return false;
          } else {
            Serial.println("SYMM: Human was stumped");
            snapTo(RED);
            symmScore = 0;
            return false;
          }
        } else {
          paint(a, OFF);
          paint(b, OFF);
        }
  
        symmTestIndex++;
  
        if (symmTestIndex >= 6) {
          // CORRECT        
          paintOff();
          gamePhase = SYMM_PHASE_OUTCOME;
          if (isHumanDrawing()) {
            Serial.println("SYMM: Computer made it symmetrical!");
            snapTo(RED);
            symmScore = 0;
          } else {
            Serial.println("SYMM: Human made it symmetrical!");
            snapTo(GREEN);
            symmScore ++;
          }
        }
      }
    }    
  }

  if (gamePhase == SYMM_PHASE_OUTCOME) {
    if (timeSinceAnimEvent() > OUTCOME_DELAY) {
      if (symmScore >= 4) {
        return true;
      }
      startSymmRound();      
    }
  }  
  
  return false;
}

//================================================================================================
// Utils

bool isHumanDrawing() {
  return symmScore >= 3;
}

int symmRobotPick() {
  int bestPick = 0;
  int bestPickDist = 0;

  for (int pick=0; pick<11; pick++) {
    int dist = 0;
    for (int center=0; center<11; center++) {
      for (int offset=1; offset<=5; offset++) {
        int ax = (center+offset+11)%11;
        int bx = (center-offset+11)%11;
        bool match = (symmPattern[ax] == symmPattern[bx]);
        bool eitherWasPicked = (ax == pick) || (bx == pick);
        if (match != eitherWasPicked) {
          dist = max(dist, offset);
        } else {
          break;
        }        
      }
    }
    if (dist > bestPickDist) {
      bestPickDist = dist;
      bestPick = pick;
    }
  }
  return bestPick;
}

void symmFlip(int index) {
  symmPattern[index] = !symmPattern[index];
}

void symmRedraw() {
  for (int i=0; i<11; i++) {
    paint(i, symmPattern[i] ? WHITE : OFF);  
  }
}

int symmFindCenter() {
  int bestDist = -1;
  int bestIndex = 0;
  for (int i=0; i<11; i++) {
    int dist = 0;
    for (int j=1; j<=5; j++) {
      if (symmPattern[(11+i+j)%11] == symmPattern[(11+i-j)%11]) {
        dist = j;
      } else {
        break;
      }
    }
    if (dist > bestDist) {
      bestDist = dist;
      bestIndex = i;
    }
  }
  return bestIndex;
}

