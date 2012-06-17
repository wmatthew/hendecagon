//==========================================================
// Game: Memory
// Learn a sequence of lights
#define MEMO_PHASE_WAIT 1
#define MEMO_PHASE_CONFIRM 2
#define MEMO_PHASE_WON 3 
#define MEMO_PHASE_LOST 4

#define MEMO_SEQ_LENGTH 11

int sequence[MEMO_SEQ_LENGTH];
int currentIndex;
int highestShown;
unsigned long memoLastEvent;

void setupGameMemo() {
  Serial.println("Setup Game: Memorize");
  currentIndex = 0;
  highestShown = 0;
  gamePhase = MEMO_PHASE_WAIT;
  getShuffledArray(sequence, MEMO_SEQ_LENGTH);
  paintOnly(sequence[currentIndex], WHITE);
  snapTo(YELLOW);
}

boolean tickGameMemo() {
  if (gamePhase == MEMO_PHASE_WON) {
    return (timeSinceUserEvent() > OUTCOME_DELAY);
  }
  
  if (gamePhase == MEMO_PHASE_LOST) {
    if (timeSinceUserEvent() > OUTCOME_DELAY) {
      setupGameMemo();      
      return false;
    }
  }

  if (gamePhase == MEMO_PHASE_CONFIRM) {
    if (timeSinceUserEvent() > 300) {
      if (currentIndex == MEMO_SEQ_LENGTH - 1) {
        // Win!
        snapTo(GREEN);
        gamePhase = MEMO_PHASE_WON;
      } else {
        snapTo(YELLOW);
        currentIndex ++;
        gamePhase = MEMO_PHASE_WAIT;
        if (currentIndex == highestShown) {
          paint(sequence[currentIndex], WHITE);
        } else if (currentIndex > highestShown) {
          highestShown ++;
          currentIndex = 0;
          paintOff();
        }
      }
    }
  }

  if (gamePhase == MEMO_PHASE_WAIT) {
    if (wasExactlyOnePressed()) {
      userEvent();
      if (getPressed() == sequence[currentIndex]) {
        snapTo(GREEN);
        gamePhase = MEMO_PHASE_CONFIRM;
        if (currentIndex < MEMO_SEQ_LENGTH-1) {
          paint(getPressed(), WHITE);
        }
      } else {
        snapTo(RED);
        paintOnly(getDown(), RED);
        paint(sequence[currentIndex], WHITE);
        gamePhase = MEMO_PHASE_LOST;
      }
    }
  }
  return false;  
}
