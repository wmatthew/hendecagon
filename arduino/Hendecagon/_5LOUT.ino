//==========================================================
// Game: Lights Out
#define LOUT_MASK    1
#define LOUT_OUTCOME 2

#define NO_MASK -999
#define LOUT_TOTAL_MASKS 6

int loutIndex;
int loutRandomPick[NUM_INPUTS];
int loutRandomSort[NUM_INPUTS];
int loutMask[][4] = {
  {-1,0,1,NO_MASK},
  {-1,1,NO_MASK,NO_MASK},
  {4,5,6,7},
  {-2,-1,1,2},
  {0,1,NO_MASK, NO_MASK},
  {-1,0,1,NO_MASK},
};
bool loutShuffle[] = {
  false,
  false,
  false,
  false,
  true,
  true,
};

void setupGameLout() {
  Serial.println("Setup Game: Lout");
  loutIndex = 0;
  startGame();
}

void startGame() {
  //Serial.print("LOUT start game ");
  //Serial.println(loutIndex);
  gamePhase = LOUT_MASK;
  paintOff();
  snapTo(YELLOW);
  
  if (loutShuffle[loutIndex]) {
    getShuffledArray(loutRandomSort, NUM_INPUTS);
  } else {
    getNormalArray(loutRandomSort, NUM_INPUTS);
  }
  
  getShuffledArray(loutRandomPick, NUM_INPUTS);
  for (int i=0; i<6; i++) {
    loutToggle(loutRandomPick[i]);
  }
}

void loutToggle(int input) {
  Serial.print("Toggle ");
  Serial.println(input);
  int baseIndex;
  for (int j=0; j<NUM_INPUTS; j++) {
    if (loutRandomSort[j] == input) {
      baseIndex = j;      
    }
  }

  for (int i=0; i<4; i++) {
    if (loutMask[loutIndex][i] == NO_MASK) {
      continue;
    }
    int idx = loutRandomSort[(11 + baseIndex + loutMask[loutIndex][i]) % 11];
    flipPaint(idx);
  }
}

void loutTestWin() {
  // Detect win
  bool anyOn = false;
  for (int i=0; i<11; i++) {
    if (getPaint(i) != OFF) {
      anyOn = true;
    }
  }
  if (anyOn == false) {
    loutIndex ++;
    userEvent();
    snapTo(GREEN);
    gamePhase = LOUT_OUTCOME;
  }
}

boolean tickGameLout() {
  if (gamePhase == LOUT_OUTCOME) {
    if (loutIndex < LOUT_TOTAL_MASKS) {
      if (timeSinceUserEvent() > 2000) {
        startGame();
      }
    } else {
      return (timeSinceUserEvent() > OUTCOME_DELAY);  
    }
  } else if (wasExactlyOnePressed() && timeSinceUserEvent() > 100) {
    userEvent();
    loutToggle(getPressed());  
    loutTestWin();
  }   
  return false;
}
