/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 22/07/2023
  Description : Read Proximity Data from Light Sensor
  Copyright (C) 2023 Teeraphat Kullanankanjana. All rights reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Variable to store proximity data
int proximity;

void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();

  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {
  // Check if proximity data is available from the light sensor
  if (carrier.Light.proximityAvailable()) {
    // Read the proximity data
    proximity = carrier.Light.readProximity();
  }

  // Print the proximity data to the serial monitor
  Serial.println(proximity);
}
