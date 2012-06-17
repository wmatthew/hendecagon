//==========================================================
// Game: Encoded Value
#define CODE_SHOW     0
#define CODE_SHOW_GAP 1
#define CODE_WAIT     2
#define CODE_OUTCOME  3

int codePattern[7];
int codeScore;
int codeSolution;
int codeIndex;

void setupGameCode() {
  Serial.println("Setup Game: Code");
  codeScore = 0;
  codePrepLevel();
}

void codePrepLevel() {
  //Serial.print("Score: ");
  //Serial.println(codeScore);
  
  gamePhase = CODE_SHOW_GAP;
  codeIndex = 0;
  snapTo(OFF);
  
  int afterGapIndex = random(1,7);
  codePattern[0] = random(11);
  for (int i=1; i<7; i++) {
    int prev = codePattern[i-1];
    if (i == afterGapIndex) {
      int dir = random(2)==0 ? 1 : 10;
      codeSolution = (prev + dir) % 11;
      codePattern[i] = (prev + 2*dir) % 11;
    } else {
      codePattern[i] = (prev + getCodeShift()) % 11;
    }    
  }
  
  /*
  Serial.print("Seq: ");  
  for (int i=0; i<7; i++) {
    Serial.print(codePattern[i]);
    Serial.print(", ");
  }
  Serial.print("..soln: ");
  Serial.println(codeSolution);
  */
}

// Random value that will be 3-8, or 10-12.
int getCodeShift() {
  int rand = 3 + random(9);
  return rand < 9 ? rand : rand + 1;
}

boolean tickGameCode() {
  if (gamePhase == CODE_OUTCOME) {
      if (timeSinceUserEvent() > OUTCOME_DELAY) {
        if (codeScore >= 5) {
          return true;
        } else {
          codePrepLevel();
        }
      }
  }
  
  if (gamePhase == CODE_WAIT) {
    if (wasExactlyOnePressed()) {
      userEvent();
      int pressed = getPressed();
      paintOnly(codeSolution, WHITE);
      if (pressed == codeSolution) {
        snapTo(GREEN);
        codeScore ++;
      } else {
        snapTo(RED);
        paint(pressed, RED);
        codeScore = 0;
      }
      gamePhase = CODE_OUTCOME;
    }  
  }

  if (gamePhase == CODE_SHOW_GAP) {
    if (timeSinceAnimEvent() > 200) {
      gamePhase = CODE_SHOW;
      animEvent();
      if (codeIndex == 7) {
        paintOff();
        snapTo(YELLOW);
        gamePhase = CODE_WAIT;
      } else {
        paintOnly(codePattern[codeIndex], WHITE);
      }
      codeIndex ++;
    }
  }
  
  if (gamePhase == CODE_SHOW) {
    if (timeSinceAnimEvent() > 1200) {
      animEvent();
      paintOff();
      gamePhase = CODE_SHOW_GAP;
    }
  }
  
  return false;
}

