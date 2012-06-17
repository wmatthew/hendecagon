//=====================
// Hendecagon
// Matthew Webber 2012
// Controller Class

void setup(){
  randomSeed(analogRead(A5));
  delay(200); // Delay setup. If a buggy program jams the serial connection this gives a chance to replace it.
  Serial.begin(9600);
  Serial.println("Launching.");
  printMemTest();
  inputSetup();
  outputSetup();
  storageBoot(); // Load profile from storage; from there setup menu.
}     

void loop() {
  refreshInputs();
  tick();
  displayOutputs();
}

