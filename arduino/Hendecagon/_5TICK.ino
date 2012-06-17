//==========================================================
// Game: Ticker Tape
#define TICK_SHOW_PATTERN   1
#define TICK_PHASE_SPIN     2
#define TICK_PHASE_OUTCOME  3

int tickLevel;
int tickRot = 0;
bool tickPattern[NUM_INPUTS];
bool tickProgress[NUM_INPUTS];

int tickComplexPatterns[16] = {
347, 303, 429, 343,
423, 317, 311, 469,
413, 359, 349, 315,
437, 363, 373, 371,
};

void setupGameTick() {
  Serial.println("Setup Game: Tick");
  userEvent();
  tickLevel = 1;
  tickInit();
}

void tickInit() {
  userEvent();
  snapTo(BLUE);
  gamePhase = TICK_SHOW_PATTERN;
  paintOff();
  int patt = tickComplexPatterns[random(16)];
  int hints = 6-tickLevel;
  int opportunities = 6;
  for (int i=0; i<11; i++) {
    tickPattern[i] = (patt >> i)&1 == 1;
    tickProgress[i] = false;
    if (tickPattern[i]) {
      paint(i, WHITE);
      if (random(opportunities) < hints) {
        hints --;
        tickProgress[i] = true;
      }
      opportunities --;
    }
  }
  // Serial.print("Tick Solution: ");
  // for (int i=0; i<11; i++) {
  //   Serial.print(tickPattern[i] ? "1" : "0");
  // }  
  // Serial.println();
}

void tickFlip(int index) {
  userEvent();
  tickProgress[(index + tickRot) % 11] = true;
  int sum = 0;
  for (int i=0; i<11; i++) {
    if (tickProgress[i]) {
      sum ++;
    }
  }
  if (sum >= 6) {
    // detect win or lose condition
    gamePhase = TICK_PHASE_OUTCOME;
    for (int i=0; i<11; i++) {
      boolean accurate = true;
      for (int j=0; j<11; j++) {
        if (tickPattern[j] != tickProgress[(i+j)%11]) {
          accurate = false;
          break;
        }
      }
      if (accurate) {
        snapTo(GREEN);
        tickLevel ++;
        return;
      }
    }  
    snapTo(RED);
    tickLevel = 1;
  }
}

void tickRefresh() {
      paintOff();
      for (int i=0; i<11; i++) {
        if (tickProgress[(i+tickRot)%11]) {
          paint(i, WHITE);
        }
      }  
}

bool tickGameTick() {
  if (gamePhase == TICK_SHOW_PATTERN) {
    if (timeSinceUserEvent() > 5000) {
      gamePhase = TICK_PHASE_SPIN;
      snapTo(YELLOW);
    }
  }
  
  if (gamePhase == TICK_PHASE_SPIN) {
    if (wasExactlyOnePressed()) {
      tickFlip(getPressed());
      tickRefresh();
    }
  }
  
  if (gamePhase == TICK_PHASE_OUTCOME || gamePhase == TICK_PHASE_SPIN) {
    if (timeSinceAnimEvent() > 800) {
      animEvent();
      tickRot = (tickRot + 1) % 11;
      tickRefresh();
    }  
  }

  if (gamePhase == TICK_PHASE_OUTCOME) {
    if (timeSinceUserEvent() > 2000) {
      // Serial.print("Tick Score: ");
      // Serial.println(tickLevel);
      if (tickLevel == 7) {
        return true;
      }
      tickInit();
    }
  }
  return false;
}

