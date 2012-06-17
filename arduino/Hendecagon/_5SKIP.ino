//==========================================================
// Game: who got skipped?
// 10 lights flash on, one at a time.
// you need to press the one that was skipped.
#define SKIP_PHASE_ANIMATION 1 // show animation
#define SKIP_PHASE_PAUSE 4     // brief gap in animation
#define SKIP_PHASE_WAIT 2      // waiting for user input
#define SKIP_PHASE_OUTCOME 3   // user guessed; holding the pattern

int skipPattern[33];
int skipPatternLength;
int skipIndex;

void setupGameSkip() {
  Serial.println("Setup Game: Skip");
  skipPatternLength = 11;
  skipStart();
}

void skipStart() {
  Serial.print("Starting skip: ");
  Serial.println(skipPatternLength);
  snapTo(OFF);
  skipIndex = -1;
  getShuffledArray(skipPattern, skipPatternLength);

  // Force first value to be GAME_SKIP, force values to be mod 11.
  int sOffset = skipPattern[0];
  for (int i=0; i<skipPatternLength; i++) {
    skipPattern[i] = (skipPattern[i] - sOffset + 99) % 11;
  }
  advanceLight();
}

bool tickGameSkip() {
  if (gamePhase == SKIP_PHASE_OUTCOME) {
    if (timeSinceUserEvent() > OUTCOME_DELAY) {
      if (skipPatternLength >= 33) {
        return true; // Win!
      } else {
        skipPatternLength += 11; // Advance!
        skipStart();
      }
    }
    return false;
  }
  
  if (wasExactlyOnePressed()) {
    userEvent();
    int down = getPressed();

    //Serial.print("User Guessed: ");
    //Serial.println(down);

    if (gamePhase == SKIP_PHASE_ANIMATION) {
      //Serial.println("Wrong, pattern underway");
      // incorrect: pattern was underway.
      paintOnly(down, RED);
      snapTo(RED);
      skipPatternLength = 0; // will be bumped to 11
    } else if (down == skipPattern[skipIndex]) {
      //Serial.println("Right!");
      paintOnly(skipPattern[skipIndex], WHITE);
      snapTo(GREEN);      
    } else {
      Serial.print("Wrong. Actual answer: ");
      Serial.println(skipPattern[skipIndex]);
      paintOnly(skipPattern[skipIndex], WHITE);
      paint(down, RED);
      snapTo(RED);
      skipPatternLength = 0; // will be bumped to 11
    }
    gamePhase = SKIP_PHASE_OUTCOME;
    return false;        
  }
  
  if (gamePhase == SKIP_PHASE_ANIMATION && timeSinceAnimEvent() > 400) {
    advanceLight();
  }
  
  if (gamePhase == SKIP_PHASE_PAUSE && timeSinceAnimEvent() > 200) {
    animEvent();
    paintOff();
    gamePhase = SKIP_PHASE_ANIMATION;
  }
  
  return false;
}

void advanceLight() {
  animEvent();
  skipIndex ++;
  if (skipIndex == skipPatternLength-1) {
    gamePhase = SKIP_PHASE_WAIT;
    snapTo(YELLOW);
    paintOff();
  } else {
    paintOnly(skipPattern[skipIndex], WHITE);
    gamePhase = SKIP_PHASE_PAUSE;
  }
}

