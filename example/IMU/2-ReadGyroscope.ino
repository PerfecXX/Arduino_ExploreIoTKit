/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.1
  Date        : 04/02/2024
  Description : Read Gyroscope Data from IMU Module (Compatible with Serial Plotter)
  Copyright (C) 2023 Teeraphat Kullanankanjana. All rights reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Variables to store gyroscope data along the x, y, and z axes
float gX,gY,gZ;

void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();

  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {
  // Check if the IMU module has gyroscope data available
  if (carrier.IMUmodule.gyroscopeAvailable()) {
    // Read the gyroscope data along the x, y, and z axes
    carrier.IMUmodule.readGyroscope(gX, gY, gZ);
  }

  // Print the acceleration values to the serial monitor/serial plotter
  Serial.print("gX:");
  Serial.print(gX);
  Serial.print(",");
  Serial.print("gY:");
  Serial.print(gY);
  Serial.print(",");
  Serial.print("gZ:");
  Serial.println(gZ);
  
  delay(500);
}
