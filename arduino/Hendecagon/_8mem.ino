void printMemTest() {  
  // run the memory test function and print the results to the serial port
  int result = memoryTest();
  Serial.print("[");
  Serial.print(result,DEC);
  Serial.println("/2048 bytes free] ");
}

// From http://www.faludi.com/2007/04/18/arduino-available-memory-test/
// this function will return the number of bytes currently free in RAM
int memoryTest() {
  int byteCounter = 0; // initialize a counter
  byte *byteArray; // create a pointer to a byte array
  // More on pointers here: http://en.wikipedia.org/wiki/Pointer#C_pointers

  // use the malloc function to repeatedly attempt allocating a certain number of bytes to memory
  // More on malloc here: http://en.wikipedia.org/wiki/Malloc
  while ( (byteArray = (byte*) malloc (byteCounter * sizeof(byte))) != NULL ) {
    byteCounter++; // if allocation was successful, then up the count for the next try
    free(byteArray); // free memory after allocating it
  }
  
  free(byteArray); // also free memory after the function finishes
  return byteCounter; // send back the highest number of bytes successfully allocated
}

