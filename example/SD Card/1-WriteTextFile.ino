/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 22/07/2023
  Description : Writing Data to a File on SD Card using Arduino MKR IoT Carrier
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
  if (!SD.exists("test.txt")) {
    // If the file doesn't exist, create it and write "Hello" to it
    myFile = SD.open("test.txt", FILE_WRITE);
    if (myFile) {
      myFile.println("Hello");
      myFile.close(); // Close the file after writing to it
      Serial.println("test.txt created and data saved");
    } else {
      // Unable to create the file
      Serial.println("Error creating test.txt");
    }
  } else {
    // File already exists
    Serial.println("test.txt exists");
  }
}

void loop() {
  // Open the "test.txt" file in write mode and write "Hello" to it
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    myFile.println("Hello");
    myFile.close(); // Close the file after writing to it
  } else {
    // Unable to open the file
    Serial.println("Error opening test.txt");
  }

  // Add a delay to control the frequency of writing to the file
  delay(5000); // Delay for 5 seconds before saving "Hello" again
}
