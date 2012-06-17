//==========================================================
// Game: Whack-A-Mole
#define MOLE_PHASE_WHACK 1
#define MOLE_PHASE_WAIT 2
#define MOLE_PHASE_SCOREBOARD 3
#define MOLE_PHASE_WON 4
#define MOLE_PHASE_LOST 5

#define TOTAL_MOLES 33 // must be a multiple of 11.
int molesWhacked;
long moleTimeRemaining;
long moleAppearanceTime;
int moleWaitTime;
int moleLocation;
boolean moleFlash;
int moleScoreboardIndex;

void setupGameMole() {
  Serial.println("Setup Game: Whack-A-Mole");
  molesWhacked = 0;
  moleTimeRemaining = 15 * 1000; // 10 seconds for 22 moles = hard but doable for 1 player.
  gamePhase = MOLE_PHASE_WAIT;
  userEvent();
}

boolean tickGameMole() {
  switch (gamePhase) {
    case MOLE_PHASE_WAIT:
      if (wasExactlyOnePressed() && timeSinceUserEvent() > 200) {
        //Serial.println("No Mole To Hit.");
        //paintOnly(getPressed(), RED);
        //userEvent();
        moleTimeRemaining -= 2000;
      } else if (timeSinceUserEvent() > moleWaitTime) {
        moleAppearanceTime = millis();
        moleLocation = (moleLocation + random(1,11)) % 11;
        paintOnly(moleLocation, WHITE);
        gamePhase = MOLE_PHASE_WHACK;
      } else if (timeSinceUserEvent() > 1000) {
        snapTo(OFF);
        paintOff();
      }
      break;
    case MOLE_PHASE_WHACK:
      if (timeSinceAnimEvent() > 100) {
        // Blink
        animEvent();
        moleFlash = !moleFlash;
        snapTo(moleFlash ? YELLOW : OFF);
      }
      if (wasExactlyOnePressed()) {
        userEvent();
        moleTimeRemaining -= (millis() - moleAppearanceTime);
        if (getPressed() == moleLocation) {
          //Serial.println("Hit Mole.");
          molesWhacked ++;
          snapTo(GREEN);
        } else {
          //Serial.println("Missed Mole.");
          moleTimeRemaining -= 2000;
          snapTo(RED);
          paint(getPressed(), RED);
        }

        if (molesWhacked >= TOTAL_MOLES || moleTimeRemaining <= 0) {
          gamePhase = MOLE_PHASE_SCOREBOARD;
          moleScoreboardIndex = 0;
          paintOff();
          snapTo(OFF);
          animEvent();
        } else {
          gamePhase = MOLE_PHASE_WAIT;
          moleWaitTime = random(400, 3000);
        }
      }
      break;
    case MOLE_PHASE_SCOREBOARD:
      if (timeSinceAnimEvent() > 600) {
        //Serial.println("Scoreboard cell.");
        animEvent();
        if (moleScoreboardIndex >= NUM_INPUTS) {
          bool justWon = molesWhacked >= 0;
          gamePhase = justWon ? MOLE_PHASE_WON : MOLE_PHASE_LOST;
          snapTo(justWon ? GREEN : RED);
        } else {        
          molesWhacked -= TOTAL_MOLES / 11;
          int loc = (moleScoreboardIndex + moleLocation)%11; 
          paint(loc, (molesWhacked < 0) ? RED : WHITE);
          moleScoreboardIndex ++;
        }
      }
      break;
    case MOLE_PHASE_WON:
      if (timeSinceAnimEvent() > OUTCOME_DELAY) {
        return true;
      }
      break;
    case MOLE_PHASE_LOST:
      if (timeSinceAnimEvent() > OUTCOME_DELAY) {
        setupGameMole();
      }
      break;
  } 
  return false;
}

