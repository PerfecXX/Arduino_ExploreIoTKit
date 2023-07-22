/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 22/07/2023
  Description : Reading Data from a File on SD Card using Arduino MKR IoT Carrier
  Copyright (C) 2023 Teeraphat Kullanankanjana. All rights reserved.
*/

// Include the necessary libraries
#include <Arduino_MKRIoTCarrier.h>
#include <SD.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Declare a file object to interact with the SD card
File myFile;

void setup() {
  // Initialize the MKR IoT Carrier board
  carrier.begin();

  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600);

  // Check if the "test.txt" file exists
  if (SD.exists("test.txt")) {
    // If the file exists, open it and print its contents
    myFile = SD.open("test.txt", FILE_READ);
    if (myFile) {
      // Read and print the file contents
      Serial.println("test.txt contents:");
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      myFile.close(); // Close the file after reading it
    } else {
      // Unable to open the file
      Serial.println("Error opening test.txt");
    }
  } else {
    // File does not exist
    Serial.println("test.txt does not exist");
  }
}

void loop() {
  // Open the "test.txt" file in each iteration of the loop
  myFile = SD.open("test.txt", FILE_READ);
  if (myFile) {
    // Read and print the file contents
    Serial.println("test.txt contents:");
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close(); // Close the file after reading it
  } else {
    // Unable to open the file
    Serial.println("Error opening test.txt");
  }

  // Delay for a short time (e.g., 5 seconds) before reading the file again
  delay(5000);
}
