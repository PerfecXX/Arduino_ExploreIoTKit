/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 22/07/2023
  Description : Read Acceleration from IMU Module
  Copyright (C) 2023 Teeraphat Kullanankanjana. All rights reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Variables to store acceleration values along the x, y, and z axes
float aX, aY, aZ;

void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();

  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {
  // Check if the IMU module has acceleration data available
  if (carrier.IMUmodule.accelerationAvailable()) {
    // Read the acceleration values along the x, y, and z axes
    carrier.IMUmodule.readAcceleration(aX, aY, aZ);
  }

  // Print the acceleration values to the serial monitor
  Serial.print("aX: ");
  Serial.print(aX);
  Serial.print(" aY: ");
  Serial.print(aY);
  Serial.print(" aZ: ");
  Serial.println(aZ);
}
