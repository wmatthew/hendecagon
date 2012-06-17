// Main Menu
int animCell;
int nextGame = GAME_NONE;

int animDelay;
int multiNum;
long multiTime;
int flicker = 0;

void setupMenu() {
  paintOff();
  userEvent();
  animEvent();
  animCell = currentGame;
  currentGame = GAME_NONE;
  nextGame = GAME_NONE;
  snapTo(beatAllLevels() ? WHITE : PURPLE);
}

void tick() {
  // Press multiple keys = instant quit to menu or profile selection
  if (getDown() == MULTIPLE_INPUTS && timeSinceMultiJump() > 2000) {

    int numberPressed = getNumDown();
    if (numberPressed != multiNum) {
      Serial.print("multi-");
      Serial.println(numberPressed);
      multiNum = numberPressed;
      multiTime = millis();
    } else if ((millis() - multiTime) > 3000 && (multiNum == 2) && currentGame != GAME_NONE) {
      multiJump();
      Serial.println("Multi-Jump to Menu");
      multiNum = NO_INPUTS;
      setupMenu();
    } else if ((millis() - multiTime) > 3000 && (multiNum == 4) && activeProfile != NO_PROFILE) {
      multiJump();
      Serial.println("Multi-Jump to Profile Selection");
      multiNum = NO_INPUTS;
      storageSetup();
    }
    return;
  } else {
    multiNum = NO_INPUTS;
    // continue to stuff below.
  }

  if (activeProfile == NO_PROFILE) {
    storageTick();
    return;
  }

  bool completedGame = false;
  switch (currentGame) {
  case GAME_SKIP: completedGame = tickGameSkip(); break;  
  case GAME_SORT: completedGame = tickGameSort(); break;  
  case GAME_MEMO: completedGame = tickGameMemo(); break;
  case GAME_MOLE: completedGame = tickGameMole(); break;
  case GAME_LOUT: completedGame = tickGameLout(); break;
  case GAME_SPIN: completedGame = tickGameSpin(); break;
  case GAME_CODE: completedGame = tickGameCode(); break;
  case GAME_TICK: completedGame = tickGameTick(); break;
  case GAME_SYMM: completedGame = tickGameSymm(); break;
  case GAME_HOLE: completedGame = tickGameHole(); break;
  case GAME_DIFF: completedGame = tickGameDiff(); break;
  case GAME_NONE:
  default:
    tickMenu();
    break;
  }

  if (completedGame) {
    beatLevel(currentGame);
    setupMenu();
  }
}

void tickMenu() {

  if (nextGame == GAME_NONE) {
    if (wasExactlyOnePressed() && timeSinceUserEvent() > 1000) {
      userEvent();
      nextGame = getPressed();
      paintOnly(nextGame, WHITE);
      return;
    } else {
      if (timeSinceAnimEvent() > 1000) {
        animCell = (animCell+1) % 11;
        animEvent();  
      }
      paintOff();
      paint(animCell, WHITE);
      flicker = (flicker + 1) % 4;
      for (int i=0; i<11; i++) {
        if (storageSolved[i] && flicker == 0) {
          paint(i, WHITE);
        }
      }
    }
    return;
  }

  // User made a selection. Showing user steady light
  if (timeSinceUserEvent() > 1000) {
    currentGame = nextGame;
    nextGame = GAME_NONE;
    animEvent();
    snapTo(OFF);
    switch (currentGame) {
    case GAME_SKIP: setupGameSkip(); break;
    case GAME_SORT: setupGameSort(); break;
    case GAME_MEMO: setupGameMemo(); break;
    case GAME_MOLE: setupGameMole(); break;
    case GAME_LOUT: setupGameLout(); break;
    case GAME_SPIN: setupGameSpin(); break;
    case GAME_CODE: setupGameCode(); break;
    case GAME_TICK: setupGameTick(); break;
    case GAME_SYMM: setupGameSymm(); break;
    case GAME_HOLE: setupGameHole(); break;
    case GAME_DIFF: setupGameDiff(); break;
    default:
      snapTo(ORANGE); // Unrecognized game. Freeze for 1 second on 0 or 1 panel on.
      paintOnly(currentGame, WHITE);
      delay(1000);
      setupMenu();
    }
  }
}

