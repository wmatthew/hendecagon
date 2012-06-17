/*
  Multiple Inputs
 */
 // TODO: rename "INPUT_BOUNCING", etc maybe?
#define PIN_BOUNCING 1
#define PIN_WEIRD 2 // TODO: use this
#define PIN_NORMAL 3

#define NORMAL_DRIFT_DISTANCE 2      // If readings are changing more than this, it's erratic and should be disregarded.
#define MININUM_CONFIDENCE 3         // Number of times in a row we need to read an input before believing it

#define MULTIPLE_INPUTS -1
#define NO_INPUTS -2

boolean wasPressed[NUM_INPUTS];
boolean wasReleased[NUM_INPUTS];
boolean isDown[NUM_INPUTS];

#define NUM_INPUT_PINS 3
int pinReadings[NUM_INPUT_PINS];
int pinStatuses[NUM_INPUT_PINS];
int pinInterpretations[NUM_INPUT_PINS]; // 0..15
int pinConfidence[NUM_INPUT_PINS];      // number of repeats at this reading

String previousReport;

void inputSetup() {
  for (int i=0; i<NUM_INPUTS; i++) {
    isDown[i] = false;
    wasPressed[i] = false;
    wasReleased[i] = false;
  }
  for (int i=0; i<NUM_INPUT_PINS; i++) {
    pinReadings[i] = 0;
    pinStatuses[i] = PIN_NORMAL;
    pinInterpretations[i] = -1;
    pinConfidence[i] = 0;
  }
}

int getNumDown() {
  int sum = 0;
  for (int i=0; i<NUM_INPUTS; i++) {
    if (isDown[i]) {
      sum = sum + 1;
    }
  } 
  return sum; 
}

// Returns NO_INPUTS, MULTIPLE_INPUTS, or 0...10
int getDown() {
  int result = NO_INPUTS;
  for (int i=0; i<NUM_INPUTS; i++) {
    if (isDown[i]) {
      if (result == NO_INPUTS) {
        result = i;
      } else {
        return MULTIPLE_INPUTS;
      }   
    }
  } 
  return result; 
}

bool isExactlyOneDown() {
  int down = getDown();
  return (down !=NO_INPUTS) && (down != MULTIPLE_INPUTS);  
}

// Returns NO_INPUTS, MULTIPLE_INPUTS, or 0...10
int getPressed() {
  int result = NO_INPUTS;
  for (int i=0; i<NUM_INPUTS; i++) {
    if (wasPressed[i]) {
      if (result == NO_INPUTS) {
        result = i;
      } else {
        return MULTIPLE_INPUTS;
      }   
    }
  } 
  return result; 
}

bool wasExactlyOnePressed() {
  int pressed = getPressed();
  return (pressed !=NO_INPUTS) && (pressed != MULTIPLE_INPUTS);  
}

void refreshInputs() {

  // These are momentary.  
  for (int i=0; i<NUM_INPUTS; i++) {
    wasPressed[i] = false;
    wasReleased[i] = false;
  }
  
  // Inputs 0..3
  // Top left of perf board
  int thresholdsC[] = {
    -1, 566, 582, 600,
    622, 646, 667, 689,
    724, 762, 792, 824,
    866, 912, 955, 1001      };
  refreshInputs(thresholdsC, analogRead(A0), 0, 0);

  // Inputs 4..7
  // Bottom of round perf board.
  int thresholdsA[] = {
    -1,  561, 577, 593,
    616, 640, 661, 683,
    719, 759, 788, 819,
    864, 912, 954, 1000      };
  refreshInputs(thresholdsA, analogRead(A1), 4, 1);

  // Inputs 8..10
  // Top right of perf board
  int thresholdsB[] = {
    -1, 566, 582, 599,
    621, 645, 666, 688,
    724, 763, 792, 825,
    867, 913, 955, 1001      };
  refreshInputs(thresholdsB, analogRead(A2), 8, 2);
}

void printInputs() {
  //Serial.print("A0: ");  
  //Serial.println(pinReadings[0]);
  
  // Pin Statuses
  boolean isAnyPinBouncing = false;
  for (int i=0; i<NUM_INPUT_PINS; i++) {
    if (pinStatuses[i] != PIN_NORMAL) {
      isAnyPinBouncing = true;  
    }
  }
  if (isAnyPinBouncing) {
    Serial.print(".");
  }

  // Press/Release Events
  for (int i=0; i<NUM_INPUTS; i++) {
    if (wasPressed[i]) {
      Serial.print("Pressed ");
      Serial.println(i);
    }
    if (wasReleased[i]) {
      Serial.print("Released ");
      Serial.println(i);
    }
  }
}

//======================================================
// Private

// Only print if it's something new.
void printReport (String report) {
  if (report != previousReport) {
    Serial.println(report);
    previousReport = report;
  }
}

void refreshInputs(int thresholds[], int newSensorValue, int inputMinIndex, int pinIndex) {

  int oldSensorValue = pinReadings[pinIndex];
  pinReadings[pinIndex] = newSensorValue;
  if (abs(newSensorValue - oldSensorValue) > NORMAL_DRIFT_DISTANCE) {
    // Value is changing too rapidly! Don't read it yet.
    pinStatuses[pinIndex] = PIN_BOUNCING;
    return;   
  } else {
    pinStatuses[pinIndex] = PIN_NORMAL;
  }

  int parsed = 0;
  for (int i=0; i<16; i++) {
    if (newSensorValue > thresholds[i]) {
      parsed = i;
    } else {
      break;
    }
  }

  if (parsed != pinInterpretations[pinIndex]) {
    pinInterpretations[pinIndex] = parsed;
    pinConfidence[pinIndex] = 1;
  } else {
    pinConfidence[pinIndex] ++;
  }

  if (pinConfidence[pinIndex] > MININUM_CONFIDENCE) {
    updateInput(inputMinIndex + 0, parsed & 1);
    updateInput(inputMinIndex + 1, parsed & 2);
    updateInput(inputMinIndex + 2, parsed & 4);
    updateInput(inputMinIndex + 3, parsed & 8);
  }
}

void updateInput(int inputNum, bool newValue) {
  if (inputNum >= NUM_INPUTS) {
    return; // out of bounds
  }
  wasReleased[inputNum] =  isDown[inputNum] && !newValue; 
   wasPressed[inputNum] = !isDown[inputNum] &&  newValue;
       isDown[inputNum] =  newValue;
}

