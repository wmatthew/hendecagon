//==========================================================
// Game: sort the blinking lights
#define SORT_PHASE_NONE    1 // None selected 
#define SORT_PHASE_ONE     2 // One selected
#define SORT_PHASE_TWO     3 // Swap animation
#define SORT_PHASE_OUTCOME 4 // Win or Lose

int sortPermutation[NUM_INPUTS];
int sortPick1;
int sortPick2;
int sortOffset;

void setupGameSort() {
  Serial.println("Setup Game: Sort");
  gamePhase = SORT_PHASE_NONE;
  sortPick1 = NO_INPUTS;
  sortPick2 = NO_INPUTS;
  sortOffset = 0;
  getShuffledArray(sortPermutation, NUM_INPUTS);
  paintOnly(GAME_SORT, WHITE);
}

bool tickGameSort() {
  if (gamePhase == SORT_PHASE_NONE || gamePhase == SORT_PHASE_OUTCOME) {
    if (timeSinceAnimEvent() > 600) {
      animEvent();
      sortOffset = (sortOffset + 1) % 11;
      paintOff();
      paint(sortPermutation[(sortOffset+1)%11], WHITE);    
      paint(sortPermutation[(sortOffset+2)%11], WHITE);    
      paint(sortPermutation[(sortOffset+3)%11], WHITE);    
      paint(sortPermutation[(sortOffset+4)%11], WHITE);    
      paint(sortPermutation[(sortOffset+8)%11], WHITE);
      paint(sortPick1, WHITE);    
      paint(sortPick2, WHITE);    
      if (gamePhase != SORT_PHASE_OUTCOME) {
        snapTo(YELLOW);
      }
    }
  }
  
  if (wasExactlyOnePressed() && timeSinceUserEvent() > 50) {
    int pressed = getPressed();
    if (gamePhase == SORT_PHASE_NONE) {
      userEvent();
      sortPick1 = pressed;
      paintOnly(pressed, WHITE);
      gamePhase = SORT_PHASE_ONE;
    } else if (gamePhase == SORT_PHASE_ONE) {
      userEvent();
      sortPick2 = pressed;    
      paint(pressed, WHITE);
      gamePhase = SORT_PHASE_TWO;
      snapTo(OFF);
    }
  } else if (gamePhase == SORT_PHASE_TWO) {
    if (timeSinceUserEvent() > 1000 || (sortPick1 == sortPick2)) {
      sortSwap(sortPick1, sortPick2);
    }
  } else if (gamePhase == SORT_PHASE_OUTCOME) {
    return timeSinceUserEvent() > 15 * 1000;
  }
  
  return false;
}

void sortSwap(int a, int b) {
  for (int i=0; i<NUM_INPUTS; i++) {
    if (sortPermutation[i] == a) {
      sortPermutation[i] = b;
    } else if (sortPermutation[i] == b) {
      sortPermutation[i] = a;
    }
  }
  sortPick1 = NO_INPUTS;
  sortPick2 = NO_INPUTS;
  gamePhase = SORT_PHASE_NONE;
  sortCheckWin();
}

void sortCheckWin() {
  bool ascending = true;
  bool descending = true;
  for (int i=0; i<NUM_INPUTS; i++) {
    int diff = sortPermutation[i] - sortPermutation[(i+1)%11];
    ascending = ascending && ((diff + 11) % 11 == 1);
    descending = descending && ((diff + 11) % 11 == 10);
  }
  
  if (ascending || descending) {
    userEvent();
    gamePhase = SORT_PHASE_OUTCOME;
    snapTo(GREEN);    
    beatLevel(currentGame);
  } else {
    snapTo(YELLOW);
  }
}
