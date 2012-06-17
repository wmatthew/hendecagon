#define DIFF_PHASE_A       1
#define DIFF_PHASE_B       2
#define DIFF_PHASE_DRAW    3
#define DIFF_PHASE_OUTCOME 4

boolean diffA[11];
boolean diffB[11];
boolean diffGuess[11];
boolean diffFailed;

void setupGameDiff() {
  snapTo(OFF);
  int diffSol[11];
  getShuffledArray(diffSol, NUM_INPUTS);

  for (int i=0; i<11; i++) {
    diffA[i] = random(2) == 0;
    diffB[i] = diffA[i] != (diffSol[i] >= 5);
    diffGuess[i] = false;
    paint(i, diffA[i] ? WHITE : OFF);
  }
  gamePhase = DIFF_PHASE_A;
  animEvent();
}

boolean tickGameDiff() {
  if (gamePhase == DIFF_PHASE_A && timeSinceAnimEvent() > 2000) {
    animEvent();
    for (int i=0; i<11; i++) {
      paint(i, diffB[i] ? WHITE : OFF);
    }
    gamePhase = DIFF_PHASE_B;
  }
  
  if (gamePhase == DIFF_PHASE_B && timeSinceAnimEvent() > 2000) {
    paintOff();
    snapTo(YELLOW);
    gamePhase = DIFF_PHASE_DRAW;
  }
  
  if (gamePhase == DIFF_PHASE_DRAW) {
    if (wasExactlyOnePressed()) {
      int press = getPressed();
      diffGuess[press] = !diffGuess[press];
      paint(press, diffGuess[press] ? WHITE : OFF);    
    }
    if (timeSinceAnimEvent() > 8000) {
      snapTo((timeSinceAnimEvent() % 100) < 50 ? OFF : YELLOW);
    }
    if (timeSinceAnimEvent() > 10000) {
      animEvent();
      diffFailed = false;
      for (int i=0; i<11; i++) {
        if (diffGuess[i] == (diffA[i] == diffB[i]) ) {
          diffFailed = true;
          paint(i, RED);
        }
      }
      
      snapTo(diffFailed ? RED : GREEN);
      gamePhase = DIFF_PHASE_OUTCOME;
    }
  }

  if (gamePhase == DIFF_PHASE_OUTCOME && timeSinceAnimEvent() > OUTCOME_DELAY) {
    if (diffFailed) {
      setupGameDiff();
    } else {
      return true;
    }
  }
  
  return false;
}
