//==========================================================
// Game: Spinner
#define SPIN_PHASE_ANIM 1
#define SPIN_PHASE_OUTCOME 2

#define SPIN_LAST_ROUND 8
int spinRound;
int spinA;
int spinB;
long spinAWait;
long spinBWait;
long spinAMove;
long spinBMove;
long spinRevTime;
long spinSpeedTime;
int spinADir;
int spinBDir;
// 1-3: 1 still 1 moving
// 4-6: 1 still, 1 speeds up / slows down / reverses
// 7-9: 2 moving lights

void setupGameSpin() {
  Serial.println("Setup Game: Spin");
  spinRound = 1;
  spinStartRound();
}

void spinWaits(long a, long b, int aDir, int bDir) {
  spinAWait = a;
  spinBWait = b;
  spinADir = aDir;
  spinBDir = bDir;
}

void spinStartRound() {    
  gamePhase = SPIN_PHASE_ANIM;
  snapTo(YELLOW);
  paintOff();
  switch (spinRound) {
    case 1: spinWaits(1000, 400, 0, 1); break;
    case 2: spinWaits(1000, 200, 0, -1); break;
    case 3: spinWaits(1000, 100, 0, 1); break;
    case 4: spinWaits(357, 457,  1, 1); break;
    default:
      spinWaits(657, 300, -1, 1); break;
  }
  Serial.print("Spin Round: ");
  Serial.println(spinRound);
  spinAMove = millis();
  spinBMove = millis();
  spinRevTime = millis();
  spinSpeedTime = millis();
  spinA = spinRound;
  spinB = (spinA + 5 ) % 11;
}

boolean tickGameSpin() {
  if (gamePhase == SPIN_PHASE_OUTCOME) {
    if (timeSinceUserEvent() > OUTCOME_DELAY) {
      if (spinRound > SPIN_LAST_ROUND) {
        return true; // level complete
      }
      spinStartRound();
    }
    return false;
  }
  
  if (wasExactlyOnePressed() && timeSinceUserEvent() > 300) {
    userEvent();
    int pressed = getPressed();
    gamePhase = SPIN_PHASE_OUTCOME;
    if (pressed == spinA && pressed == spinB) {
      paintOnly(pressed, WHITE);
      snapTo(GREEN);
      spinRound++;
    } else {
      spinRound = max(1, spinRound - 1);
      paintOff();
      paint(spinA, RED);
      paint(spinB, RED);
      paint(pressed, WHITE);
      snapTo(RED);
    }
    return false;
  }  
  
  if (millis() - spinAMove > spinAWait) {
    spinAMove = millis();  
    spinA = (spinA + 11 + spinADir) % 11;
  }  
  if (millis() - spinBMove > spinBWait) {
    spinBMove = millis();  
    spinB = (spinB + 11 + spinBDir) % 11;
  }

  if ((spinRound == 7 || spinRound == 8) && millis() - spinRevTime > 1000) {
    if (random(100) == 0) {
      spinADir = -spinADir;
    }
    if (random(100) == 0) {
      spinBDir = -spinBDir;
    }
  }

  if ((spinRound == 6 || spinRound == 8) && millis() - spinSpeedTime > 1000) {
    if (random(100) == 0) {
      spinAWait = 1000 - spinAWait;
    }
    if (random(100) == 0) {
      spinBWait = 1000 - spinBWait;
    }  
  }

  paintOff();
  paint(spinA, WHITE);
  paint(spinB, WHITE);  
  return false;
}

