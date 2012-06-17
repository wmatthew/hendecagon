//==========================================================
// Game: Black Hole
#define HOLE_PHASE_INTRO   1
#define HOLE_PHASE_TURN    2
#define HOLE_PHASE_OUTCOME 3

int hole;
int holeIntroIndex;
bool holeBoard[6];
bool isUserTurn;

int holeLoseStates[] = {
 0,  2,  5,  8, 10, 15, 17,
20, 22, 25, 29, 32, 34, 37,
40, 42, 47, 51, 59, 60, 62
};

void setupGameHole() {
  Serial.println("Setup Game: Hole");
  gamePhase = HOLE_PHASE_INTRO;
  holeIntroIndex = 0;
  isUserTurn = true;
  animEvent();
  hole = random(11);
  for (int i=0; i<6; i++) {
    holeBoard[i] = (i==0);
  }
  holeRefresh();
}

boolean tickGameHole() {
  if (gamePhase == HOLE_PHASE_INTRO) {
    if (timeSinceAnimEvent() > 180) {
      animEvent();
      holeBoard[holeIntroIndex] = true;
      holeIntroIndex++;
      if (holeIntroIndex == 6) {
        userEvent();
        gamePhase = HOLE_PHASE_TURN;
      }
      holeRefresh();
    }
    return false;
  }
  
  if (gamePhase == HOLE_PHASE_OUTCOME) {
    if (timeSinceUserEvent() > OUTCOME_DELAY) {
      bool computerWon = !isUserTurn;
      if (computerWon) {
        setupGameHole();
      } else {
        return true; // user won
      }
    }      
  }

  if (gamePhase == HOLE_PHASE_TURN) {
    int pick = NO_INPUTS;
    
    if (isUserTurn && wasExactlyOnePressed()) {
      // User Turn
      userEvent();
      pick = getPressed();
      isUserTurn = false;        
    }

    if (!isUserTurn && timeSinceUserEvent() > 1000) {
      // Robot Turn
      pick = holeRobotMove();
      isUserTurn = true;
    }

    if (pick != NO_INPUTS) {
      int dist = distFromHole(pick);
      if (holeBoard[dist] == false) {
        paint((hole+dist+11) % 11, RED);
        paint((hole-dist+11) % 11, RED);
        snapTo(isUserTurn ? GREEN : RED);
        gamePhase = HOLE_PHASE_OUTCOME;
        userEvent();
        return false;
      } else {
        holeBoard[dist] = false;
        if (dist > 0) {
          holeBoard[dist-1] = true;
        }
      }    
    }
    
    holeRefresh();
  }
  
  return false;
}

//==========================

// If you toggle this (0..5), what is the int rep of the board?
int hole_isGoodMove(int index) {
  int sum = 0;
  for (int i=0; i<6; i++) {
    if ((i == index - 1) ||
        (holeBoard[i] && i != index)) {
      sum += (1 << i);
    }
  }
  
  for (int i=0; i<21; i++) {
    if (holeLoseStates[i] == sum) {
      return true; // it's a good move to make the other person in a lose state
    }
  }  
  return false;
}

int holeRobotMove() {

  int offset = random(6);
  // Pick a move that avoids lose states
  for (int i=0; i<6; i++) {
    int index = (offset+i)%6;
    if (holeBoard[index] && hole_isGoodMove(index)) {
      Serial.println("Hole: r winning");
      return (hole+index) % 11;
    }    
  }
  
  // Fallback: pick a random lit cell
  for (int i=0; i<6; i++) {
    int index = (offset+i)%6;
    if (holeBoard[index]) {
      Serial.println("Hole: r losing");
      return (hole+index) % 11;
    }
  }

  // Fallback: random (lose)
  Serial.println("Hole: r losing hard");
  return random(11);
}

int distFromHole(int button) {
  int diff = (hole - button + 11) % 11;
  return min(diff, 11-diff);
}

void holeRefresh() {
  snapTo(isUserTurn ? YELLOW : BLUE);

  for (int i=0; i<6; i++) {
    int a = (hole+i+11) % 11;
    int b = (hole-i+11) % 11;
    paint(a, holeBoard[i] ? WHITE : OFF);
    paint(b, holeBoard[i] ? WHITE : OFF);
  }
  
  bool anyOn = false;
  for (int i=0; i<6; i++) {
    if (holeBoard[i]) {
      anyOn = true;
    }
  }  
}
