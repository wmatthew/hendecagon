//==========================================
// Menu: Mapping of games to buttons
#define GAME_NONE -1 // Main Menu / No game selected
#define GAME_SKIP 0  // Who was skipped?
#define GAME_MEMO 1  // Memory
#define GAME_MOLE 2  // Whack-A-Mole
#define GAME_SPIN 3  // Spinner
#define GAME_TICK 4  // Ticker Tape
#define GAME_LOUT 5  // Lights Out
#define GAME_SORT 6  // Sort the Blinking Lights
#define GAME_CODE 7  // Encoding
#define GAME_SYMM 8  // Symmetry (vs)
#define GAME_HOLE 9  // Black Hole (vs)
#define GAME_DIFF 10 // Diff

//==========================================
// Inputs
#define NUM_INPUTS 11

//==========================================
// Shared Game State
#define OUTCOME_DELAY 3000
int currentGame = GAME_NONE;
int gamePhase;
unsigned long lastAnimEvent=0;
unsigned long lastUserEvent=0;
unsigned long lastMultiJump=0;

void multiJump() {
  lastMultiJump = millis();
}

void userEvent() {
  lastUserEvent = millis();
}

void animEvent() {
  lastAnimEvent = millis();
}

long timeSinceMultiJump() {
  return millis() - lastMultiJump;
}

long timeSinceUserEvent() {
  return millis() - lastUserEvent;
}

long timeSinceAnimEvent() {
  return millis() - lastAnimEvent;
}

//==========================================
// Colors: used by both RGB and white/red LEDs
#define OFF 0
#define RED 1
#define ORANGE 2 // a little blinky
#define YELLOW 3
#define GREEN 4
#define BLUE 5
#define PURPLE 6
#define WHITE 7 // not quite white

//==========================================
// Arduino Pins
// White LEDs
int W_SRCLK_Pin = 2; //pin 11 on the 75HC595
int W_RCLK_Pin = 3;  //pin 12 on the 75HC595
int W_SER_Pin = 4;   //pin 14 on the 75HC595
// Red LEDs
int R_SRCLK_Pin = 5; //pin 11 on the 75HC595
int R_RCLK_Pin = 6;  //pin 12 on the 75HC595
int R_SER_Pin = 7;   //pin 14 on the 75HC595
// RGB
int RGB_RED_PIN = 11;
int RGB_GREEN_PIN = 9;
int RGB_BLUE_PIN = 10;

//==========================================
// Utility Functions

void getNormalArray(int shuffled[], int length) {
  for (int i=0; i<length; i++) {
    shuffled[i] = i;
  }
}

// Returns an array of [0..length-1], shuffled 
void getShuffledArray(int shuffled[], int length) {

  getNormalArray(shuffled, length);

  for (int i=0; i<length; i++) {
    int j = random(i, length);
    int temp = shuffled[i];
    shuffled[i] = shuffled[j];
    shuffled[j] = temp;
  }
}

