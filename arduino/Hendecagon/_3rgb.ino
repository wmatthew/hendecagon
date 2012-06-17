int currentColors[3];

void outputSetup_RGB() {
  pinMode(RGB_RED_PIN, OUTPUT);
  pinMode(RGB_GREEN_PIN, OUTPUT);
  pinMode(RGB_BLUE_PIN, OUTPUT);
  snapTo(OFF);
}

void displayOutputs_RGB() {
  analogWrite(RGB_RED_PIN,   currentColors[0]);    
  analogWrite(RGB_GREEN_PIN, currentColors[1]);    
  analogWrite(RGB_BLUE_PIN,  currentColors[2]);
}

void snapTo(int color) {
  switch (color) {
    case RED:
      setColors(255,0,0);
      break;
    case ORANGE:
      setColors(255,127,0);
      break;
    case YELLOW:
      setColors(255,220,0);
      break;
    case GREEN:
      setColors(0,255,0);
      break;
    case BLUE:
      setColors(0,0,255);
      break;
    case PURPLE:
      setColors(255,0,255);
      break;
    case WHITE:
      setColors(210,255,90);
      break;
    case OFF:
    default:
      setColors(0,0,0);
      break;
  }
}

void setColors(int r, int g, int b) {
  currentColors[0] = r;
  currentColors[1] = g;
  currentColors[2] = b;
}

