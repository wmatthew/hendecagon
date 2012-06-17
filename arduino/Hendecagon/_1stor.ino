// Long-Term Storage (EEPROM)
// Memory Allocated as follows:
// Addr  Use
// 0,1    Profile 0
// 2,3    Profile 1
// ...    ...
// 14,15  Profile 7
// 16     Active Profile
// 17+    Unused

#include <EEPROM.h>

#define STORAGE_ACTIVE_PROFILE_ADDRESS 16
#define NUM_PROFILES 8
#define NO_PROFILE 255

#define UNSOLVED 255
#define SOLVED 33

int activeProfile = NO_PROFILE;
int storageHighlight;
bool storageSolved[NUM_INPUTS];

void storageBoot() {
  int ss = EEPROM.read(STORAGE_ACTIVE_PROFILE_ADDRESS);
  if (ss == NO_PROFILE || ss < 0 || ss >= NUM_PROFILES) {
    // No active profile. Force user to pick one in storage menu.
    activeProfile = NO_PROFILE;
    storageSetup();
    return;
  } else {
    // Have active profile. Skip storage menu; go to main menu.
    loadProfile(ss);
    setupMenu(); // Launch into main menu screen first.
  }
}

void storageSetup() {
  snapTo(YELLOW);
  paintOff();
  paint(8, WHITE);
  paint(9, RED);
  paint(10, WHITE);
  storageHighlight = activeProfile == NO_PROFILE ? 3 : activeProfile;
  paint(storageHighlight, WHITE);
  activeProfile = NO_PROFILE;
  userEvent();
}

void storageTick() {
  if (wasExactlyOnePressed() && isExactlyOneDown() && timeSinceUserEvent() > 100) {
    userEvent();
    int press = getPressed();
    if (press == 10) {
      // left
      paint(storageHighlight, OFF);
      storageHighlight = max(0, storageHighlight - 1);
      paint(storageHighlight, WHITE);
    } else if (press == 8) {
      // right
      paint(storageHighlight, OFF);
      storageHighlight = min(7, storageHighlight + 1);
      paint(storageHighlight, WHITE);
    } else if (press == 9) {
      clearProfile(storageHighlight);
    } else if (press == storageHighlight) {
      EEPROM.write(STORAGE_ACTIVE_PROFILE_ADDRESS, press);  
      loadProfile(press);
      setupMenu();
    }
  }
}

void clearProfile(int profile) {
  Serial.print("Clearing Profile #");
  Serial.println(profile);
  for (int i=0; i<11; i++) {
    storageSolved[i] = false;
  }
  saveProfile(profile);
}

boolean beatAllLevels() {
  for (int i=0; i<11; i++) {
    if (storageSolved[i] == false) {
      return false;
    }
  }  
  return true;
}

void beatLevel(int level) {
  if (storageSolved[level] == false) {
    storageSolved[level] = true;
    saveProfile(activeProfile);  
  }
}

void loadProfile(int profile) {
  activeProfile = profile;
  Serial.print("Load Profile ");
  Serial.print(profile);
  Serial.print(": ");
  int low = EEPROM.read(profile*2);
  int high = EEPROM.read(profile*2 + 1);
  for (int i=0; i<8; i++) {
    storageSolved[i] = ((low >> i) & 1) == 0;    
  }
  for (int i=8; i<11; i++) {
    storageSolved[i] = ((high >> (i-8)) & 1) == 0;
  }
  for (int i=0; i<11; i++) {
    Serial.print(storageSolved[i] ? "T" : "F");    
  }
  Serial.println();
}

void saveProfile(int profile) {
  Serial.print("Save Profile ");
  Serial.print(profile);
  Serial.print(": ");
  for (int i=0; i<11; i++) {
    Serial.print(storageSolved[i] ? "T" : "F");    
  }
  Serial.println();

  int low = 0;
  for (int i=0; i<=7; i++) {
    low *= 2;
    if (storageSolved[7-i] == false) {
      low++;
    }
  }
  Serial.print("Writing to ");
  Serial.print(profile * 2);
  Serial.print(" value: ");
  Serial.println(low & 255);
  EEPROM.write(profile * 2,     low & 255);
  
  int high = 0;
  for (int i=0; i<=2; i++) {
    high *= 2;
    if (storageSolved[10-i] == false) {
      high++;
    }
  }
  Serial.print("Writing to ");
  Serial.print(profile * 2 + 1);
  Serial.print(" value: ");
  Serial.println(high & 255);
  EEPROM.write(profile * 2 + 1, high & 255);  
}

