#define number_of_74hc595s 2 // Number of shift register chips
#define numOfRegisterPins number_of_74hc595s * 8

boolean redRegisters[numOfRegisterPins];
boolean whiteRegisters[numOfRegisterPins];

void outputSetup(){
  pinMode(R_SER_Pin, OUTPUT);
  pinMode(R_RCLK_Pin, OUTPUT);
  pinMode(R_SRCLK_Pin, OUTPUT);

  pinMode(W_SER_Pin, OUTPUT);
  pinMode(W_RCLK_Pin, OUTPUT);
  pinMode(W_SRCLK_Pin, OUTPUT);

  paintOff();
  outputSetup_RGB();
}

void displayOutputs() {
  // TODO: only write registers if something changed!
  writeWhiteRegisters();
  writeRedRegisters();
  displayOutputs_RGB();
}

void paintOff() {
  clearWhiteRegisters();
  clearRedRegisters();
}

void paintOnly(int input, int mode) {
  paintOff();
  paint(input, mode);
}

// mode can be: RED, WHITE, OFF
void paint(int input, int mode) {
  if (input < 0 || input >= 11) {
    return;
  }
  int output = convertInputToOutput(input);
  setRedRegisterPin(  output, mode==RED   ? HIGH : LOW);
  setWhiteRegisterPin(output, mode==WHITE ? HIGH : LOW);
}

void flipPaint(int input) {
  int output = convertInputToOutput(input);
  redRegisters[output] = LOW;
  whiteRegisters[output] = (whiteRegisters[output] == LOW) ? HIGH : LOW;
}

int getPaint(int input) {
  int output = convertInputToOutput(input);
  if (redRegisters[output] == HIGH && whiteRegisters[output] == LOW) {
    return RED;
  } else if (redRegisters[output] == LOW && whiteRegisters[output] == HIGH) {
    return WHITE;
  } else if (redRegisters[output] == LOW && whiteRegisters[output] == LOW) {
    return OFF;
  } else {
    // TODO: ERROR
    return -1;
  }
}

//==============================================
// Internal

// Inputs:    0 1 2 3 4 5 6   7  8  9 10          11
// Outputs: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
int convertInputToOutput(int input) {
  if (input < 7) {
    return input+1;
  } else {
    return input+2;
  }
}

void clearRedRegisters(){
  for (int i = numOfRegisterPins - 1; i >=  0; i--){
     redRegisters[i] = LOW;
  }
} 
void clearWhiteRegisters(){
  for (int i = numOfRegisterPins - 1; i >=  0; i--){
     whiteRegisters[i] = LOW;
  }
} 

// This function is slow; only run when needed.
void writeRedRegisters(){
  digitalWrite(R_RCLK_Pin, LOW);
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(R_SRCLK_Pin, LOW);
    int val = redRegisters[i];
    digitalWrite(R_SER_Pin, val);
    digitalWrite(R_SRCLK_Pin, HIGH);
  }
  digitalWrite(R_RCLK_Pin, HIGH);
}

// This function is slow; only run when needed.
void writeWhiteRegisters(){
  digitalWrite(W_RCLK_Pin, LOW);
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(W_SRCLK_Pin, LOW);
    int val = whiteRegisters[i];
    digitalWrite(W_SER_Pin, val);
    digitalWrite(W_SRCLK_Pin, HIGH);
  }
  digitalWrite(W_RCLK_Pin, HIGH);
}

void setRedRegisterPin(int index, int value){
  redRegisters[index] = value;
}

void setWhiteRegisterPin(int index, int value){
  whiteRegisters[index] = value;
}

