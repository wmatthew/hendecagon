/**
//==========================================================
// Game: Clouds vs Computer
#define CLOD_PHASE_TURN    1
#define CLOD_PHASE_ANIMATE 2 // Result of a turn being taken
#define CLOD_PHASE_OUTCOME 3

// save some unsigned ints
PROGMEM prog_uint16_t clodWins[2048]  = { 
false,false,false,true,false,false,true,false,false,false,false,true,true,true,false,true,false,false,false,true,false,true,true,false,true,true,true,false,false,false,true,false,false,false,false,true,false,false,true,false,false,false,true,true,true,true,false,true,true,true,true,false,true,true,false,true,false,false,false,true,true,true,false,true,false,false,false,true,false,false,true,false,false,true,false,true,true,true,false,true,false,false,false,true,true,true,true,true,true,true,true,false,false,false,true,false,true,true,true,false,true,true,false,true,true,true,true,true,false,false,true,false,false,false,false,true,false,true,true,false,true,true,true,false,false,false,true,false,false,false,false,true,false,false,true,false,false,true,false,true,true,true,false,true,false,true,true,true,false,true,true,false,true,true,true,false,false,false,true,false,false,false,false,true,false,false,true,false,true,true,true,false,true,true,true,true,true,true,true,false,true,true,false,true,false,false,false,true,true,true,false,true,true,true,true,false,true,true,false,true,true,true,true,false,false,false,true,false,true,true,true,false,true,false,true,true,false,false,false,true,true,true,false,true,false,false,false,true,false,false,true,false,false,false,true,true,true,true,false,true,true,true,true,false,true,true,false,true,false,false,false,true,true,true,false,true,
false,false,false,true,false,false,true,false,false,true,false,true,true,true,false,true,false,true,true,true,false,true,true,false,true,true,true,false,false,false,true,false,false,true,true,true,true,true,true,true,false,true,true,true,true,true,false,true,true,true,true,true,true,true,false,true,false,true,false,true,true,true,false,true,false,false,false,true,false,false,true,false,false,true,false,true,true,true,false,true,true,true,true,true,true,true,false,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,false,true,true,true,true,true,false,false,true,false,false,false,false,true,false,true,true,false,true,true,true,false,false,false,true,false,true,true,true,false,true,true,false,true,true,true,true,false,false,false,true,false,true,true,true,true,true,true,false,true,false,true,false,true,true,true,false,true,true,true,true,false,true,true,false,true,true,true,false,true,true,true,true,true,false,false,false,true,false,true,true,false,true,true,true,false,false,false,true,false,false,false,false,true,false,false,true,false,false,true,false,true,true,true,false,true,false,false,false,true,true,true,true,true,true,true,true,false,false,false,true,false,true,true,true,false,true,true,false,true,true,true,true,true,false,false,true,false,false,false,false,true,false,true,true,false,true,true,true,false,false,false,true,false,
false,false,false,true,false,true,true,false,false,false,false,true,true,true,false,true,false,false,true,true,false,true,true,false,true,true,true,false,false,true,true,false,false,false,true,true,true,true,true,false,false,false,true,true,true,true,false,true,true,true,true,false,true,false,false,true,false,false,false,true,true,true,false,true,false,false,true,true,true,true,true,false,true,true,true,true,true,true,true,true,false,false,true,true,true,true,true,true,true,true,true,false,false,true,true,false,true,true,true,false,true,true,true,true,true,true,true,true,false,true,true,false,false,false,true,true,false,true,true,false,true,true,true,false,false,true,true,false,false,true,false,true,false,true,true,true,false,true,false,true,true,false,false,true,false,true,true,true,false,true,true,true,true,true,true,true,false,true,true,true,true,true,true,false,true,true,true,true,true,true,true,true,false,true,true,false,true,false,true,true,true,true,true,false,true,true,true,false,true,false,true,false,true,true,true,true,true,false,false,true,true,true,true,true,false,true,true,true,true,true,true,true,true,true,true,false,false,true,false,true,true,false,false,true,false,true,false,true,false,true,true,true,false,true,true,false,true,false,false,true,true,true,true,true,true,false,false,true,false,true,false,true,true,false,false,true,
true,true,true,false,true,true,false,true,true,true,true,false,false,true,true,false,true,true,true,false,true,false,false,true,false,false,false,true,true,true,false,true,true,true,true,false,true,true,true,true,true,true,true,true,false,true,true,false,false,false,true,true,false,true,true,false,true,true,true,false,false,true,true,false,true,true,true,false,true,true,false,true,true,true,true,false,false,true,true,false,true,true,true,true,false,true,true,false,true,true,true,true,true,false,true,true,false,false,false,true,false,true,true,false,false,false,true,true,true,true,false,true,true,true,true,false,true,false,false,true,false,false,false,true,true,true,false,true,false,false,false,true,false,true,true,false,false,false,false,true,true,true,false,true,false,false,true,true,false,true,true,false,true,true,true,false,false,true,true,false,false,false,false,true,false,true,true,false,true,true,true,false,true,false,true,true,true,true,true,false,true,false,false,true,false,false,false,true,true,true,false,true,true,true,true,false,true,true,false,true,true,true,true,false,false,true,true,false,true,true,true,false,true,false,true,true,false,false,false,true,true,true,false,true,false,false,false,true,false,true,true,false,false,false,true,true,true,true,false,true,true,true,true,false,true,false,false,true,false,false,false,true,true,true,false,true,
false,true,false,false,false,true,true,true,false,true,true,false,true,false,false,false,false,true,false,false,false,true,true,true,true,false,true,true,false,true,true,true,false,true,false,false,true,true,true,true,false,true,true,true,true,false,false,false,true,false,true,true,true,true,false,false,false,true,true,false,true,false,false,false,false,true,false,false,true,true,true,true,true,true,true,false,true,false,false,false,false,true,false,false,true,false,true,true,true,false,true,true,false,true,true,true,true,false,true,true,true,false,false,false,true,false,false,true,false,true,true,true,false,true,false,false,false,true,true,true,true,false,true,true,false,true,true,true,false,true,false,false,true,true,true,true,true,true,true,false,true,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,true,true,false,false,false,true,true,false,true,false,false,false,true,false,true,true,true,false,false,false,true,true,true,true,true,true,true,true,true,false,true,true,true,true,true,true,false,true,true,false,true,false,false,false,false,true,false,false,true,true,true,true,false,true,true,true,true,false,false,false,true,false,true,true,true,true,false,false,false,true,true,false,true,false,false,false,
false,true,true,false,false,true,true,true,false,true,true,false,true,false,true,false,false,true,true,false,false,true,true,true,true,false,false,true,false,true,true,true,false,true,true,false,true,true,true,true,false,true,true,true,true,false,true,false,true,false,true,true,true,true,true,false,false,true,true,false,true,false,true,false,true,true,true,true,true,true,false,true,true,true,true,true,true,true,true,true,true,false,true,true,true,true,true,false,false,true,true,false,true,false,false,false,true,true,false,true,true,true,true,true,true,true,true,false,true,true,false,true,true,true,true,true,true,false,false,true,true,true,false,true,true,true,false,true,true,false,true,true,true,false,true,false,true,false,false,true,false,true,true,true,true,false,true,true,true,true,true,false,false,true,true,false,true,false,true,false,true,false,true,true,true,false,true,false,true,true,true,false,true,true,false,true,false,true,true,false,false,true,true,true,true,false,false,true,false,true,true,true,false,true,true,false,false,true,true,true,false,true,true,false,true,false,true,false,false,true,true,false,true,false,false,true,true,false,false,true,false,true,true,true,true,false,true,true,true,false,true,false,true,false,false,true,false,true,true,true,false,true,true,false,false,true,true,true,true,false,false,true,false,true,true,true,
true,false,true,true,true,false,false,false,true,false,true,true,false,true,true,true,true,false,true,true,true,true,false,false,false,true,true,false,true,false,false,false,true,false,true,true,true,false,false,false,true,false,false,true,false,true,true,true,false,true,false,false,false,true,true,true,true,false,true,true,false,true,true,true,true,false,true,true,true,false,false,false,true,true,true,true,true,true,true,true,true,false,true,true,true,true,true,true,false,true,true,false,true,false,false,false,false,true,false,false,true,true,true,true,false,true,true,true,true,false,false,false,true,false,true,true,true,true,false,false,false,true,true,false,true,false,false,false,true,false,true,true,true,false,false,false,true,false,true,true,false,true,true,true,true,false,true,true,true,true,false,false,false,true,true,false,true,false,false,false,true,true,true,true,true,true,true,true,false,true,true,false,true,false,false,false,true,true,true,true,true,false,true,true,true,true,false,true,true,true,true,true,false,true,false,false,false,true,true,true,false,true,true,false,true,false,false,false,false,true,false,false,true,false,true,true,true,false,true,true,false,true,true,true,true,false,true,true,true,false,false,false,true,false,false,true,false,true,true,true,false,true,false,false,false,true,true,true,true,false,true,true,false,true,true,true,
false,true,false,false,false,true,true,true,false,true,true,false,true,false,false,false,false,true,false,false,false,true,true,true,true,false,true,true,false,true,true,true,false,true,false,false,true,true,true,true,false,true,true,true,true,false,false,false,true,false,true,true,true,true,false,false,false,true,true,false,true,false,false,false,false,true,false,false,false,true,true,true,false,true,true,false,true,false,false,false,true,true,true,true,true,false,false,false,true,true,false,true,true,true,true,true,true,false,true,true,true,false,false,false,true,false,false,true,false,true,true,true,false,true,false,false,false,true,true,true,true,false,true,true,false,true,true,true,true,false,true,true,true,false,false,false,true,false,true,true,false,true,true,true,true,false,true,true,true,true,false,false,false,true,true,false,true,false,false,false,true,false,true,true,true,false,false,false,true,true,false,false,true,true,true,true,false,true,false,false,false,true,true,true,true,false,true,true,false,true,true,true,false,true,false,false,false,true,true,true,false,true,true,false,true,false,false,false,false,true,false,false,true,false,true,true,true,false,true,true,false,true,true,true,true,false,true,true,true,false,false,false,true,false,false,true,false,true,true,true,false,true,false,false,false,true,true,true,true,false,true,true,false,true,true,true,
};

#define CLOD_NUM_STARTS 14
int clodStarts[CLOD_NUM_STARTS]  = {
  339, 751, 299, 887,
  731, 301, 879, 735,
  331, 215, 173, 341,
  411, 311};
int recentMove;

bool isComputerTurn;
bool clodPattern[NUM_INPUTS];

void setupGameClod() {
  Serial.println("Setup Game: Clod");
  userEvent();
  gamePhase = CLOD_PHASE_TURN;
  isComputerTurn = false;
  snapTo(YELLOW);

  int startPattern = clodStarts[random(CLOD_NUM_STARTS)];
  startPattern = clodReverse(startPattern, random(2));
  startPattern = clodRotate(startPattern, random(11));
  clodSetPattern(startPattern);
}

bool tickGameClod() {
  if (gamePhase == CLOD_PHASE_TURN) {
    recentMove = NO_INPUTS;
    
    if (!isComputerTurn && wasExactlyOnePressed() && timeSinceUserEvent() > 500) {
      recentMove = getPressed();
    }
  
    if (isComputerTurn && timeSinceAnimEvent() > 1000) {
      recentMove = clodComputerMove();
    }
    
    if (recentMove != NO_INPUTS) {
      snapTo(OFF);
      gamePhase = CLOD_PHASE_ANIMATE;
    }
  }

  if (gamePhase == CLOD_PHASE_ANIMATE) {
    if (clodPattern[recentMove] == false) {
        Serial.println("Loss");
        paint(recentMove, RED);
        snapTo(isComputerTurn ? GREEN : RED);
        animEvent();
        gamePhase = CLOD_PHASE_OUTCOME;
        return false;
    }

    clodSetPattern(clodGetResult(clodGetPattern(), recentMove));
    gamePhase = CLOD_PHASE_TURN;
    animEvent();
    isComputerTurn = !isComputerTurn;
    snapTo(isComputerTurn ? BLUE : YELLOW);
  }

  if (gamePhase == CLOD_PHASE_OUTCOME) {
    if (timeSinceAnimEvent() > OUTCOME_DELAY) {
      if (isComputerTurn) {
        return true;
      }      
      setupGameClod();    
    }
  }
  
  return false;
}

//==========================================
// Utility Functions
int clodReverse(int input, int times) {
  if (times %2 == 0) {
    return input;
  }
  int output = 0;
  for (int i=0; i<11; i++) {
    output += (((input >> i) & 1) << (10-i));
  }
  clodCheck(output);
  return output;
}

int clodRotate(int input, int times) {
  for (int i=1; i<=times; i++) {
    input = (input/2) | ((input%2) * 1024);
  }
  clodCheck(input);
  return input;
}

void clodRefresh() {
  for (int i=0; i<11; i++) {
    paint(i, clodPattern[i] ? WHITE : OFF);
  }
}

int clodComputerMove() {
  int pattern = clodGetPattern();
  
  // Simulate clicks until you find one that matches; return it.
  int offset = random(11);
  for (int i=0; i<11; i++) {
    int click = (i+offset)%11;

    if (clodPattern[click] == false) {
      continue;
    }    

    int result = clodGetResult(pattern, click);
    if (result == -1) {
      Serial.println("Warn-0");      
      continue;
    }
    boolean win = pgm_read_word_near(clodWins + result);
    if (!win) {
      // Try to hand opponent losing config
      Serial.print("CLOD: cwins");
      Serial.print(pattern, BIN);
      Serial.print(" -> ");
      Serial.print(click);
      Serial.print(" -> ");
      Serial.println(result, BIN);
      return click;
    }
  }
  
  Serial.println("CLOD: comp losin'");
  // We're losing. Hit a random light.
  for (int i=0; i<11; i++) {
    int click = (i+offset)%11;
    if (clodPattern[click]) {
      return click;
    }    
  }
  
  // No lights. Hit anything. We dead.
  return random(11);
  Serial.println("CLOD: comp lost");
}

int clodGetResult(int config, int move) {
  clodCheck(config);

  // Instant Loss
  if ((config&(1<<move)) == 0) {
    return -1;
  }

  // Clearing
  if (config == 2047) {
    return 0;
  }

  int a = (move+1)%11;
  int b = (move+10)%11;

  // Expand Single    
  if (!(config&(1<<a)) && !(config&(1<<b))) {
    for (int i=1; i<=5; i++) {
      int x = (11 + move + i) % 11;
      int y = (11 + move - i) % 11;
      if (!(config&(1<<x)) && !(config&(1<<y))) {
        config |= (1<<x);
        config |= (1<<y);
      } else {
        break;
      }
    }
    return config;
  }
    
  // Move to an edge of this cloud
  if ((config&(1<<a)) && (config&(1<<b))) {
    boolean fwd = random(2) == 0;
    int furthestOn = move;
    for (int i=1; i<10; i++) {
      int j = fwd ? (move + i) : (move - i);
      j = (j+11) % 11;
      if ((config&(1<<j))) {
        furthestOn = j;
      } else {
        move = furthestOn;
        break;
      }
    }
    // recalculate these
    a = (move+1)%11;
    b = (move+10)%11;
  }
    
  // Contract Edge
  if ((config&(1<<a)) != (config&(1<<b))) {
    config &= ~(1<<move); // set just this one bit to 0
    return config;
  }
  
  Serial.println("WARN no move was made.");
  return config;
}

int clodGetPattern() {
  int sum = 0;
  for (int i=0; i<11; i++) {
    if (clodPattern[i]) {
      sum |= (1 << i);
    }
  }
  clodCheck(sum);
  return sum;
}

void clodSetPattern(int pattern) {
  clodCheck(pattern);
  for (int i=0; i<11; i++) {
    int mask = (1 << i);
    clodPattern[i] = ((pattern & mask) > 0);
  }
  clodRefresh();
}

void clodCheck(int pattern) {
  if (pattern < 0) {
    Serial.println("Warn- pattern out of bounds (low)");
  }
  if (pattern > 2047) {
    Serial.println("Warn- pattern out of bounds (high)");  
  }
}
**/
