/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 22/07/2023
  Description : Calculate Shake Value Percentage from Gyroscope Data
  Copyright (C) 2023 Teeraphat Kullanankanjana. All rights reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Variables to store gyroscope data along the x, y, and z axes
float gX, gY, gZ;

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

    // Calculate the magnitude of the gyroscope vector (motion intensity)
    float gyroMagnitude = sqrt(gX * gX + gY * gY + gZ * gZ);

    // Calculate the percentage of motion relative to the maximum possible motion range (e.g., 2000 deg/s for gyroscope)
    int shakePercentage = map(gyroMagnitude, 0, 2000, 0, 100);

    // Print the shake value percentage to the serial monitor
    Serial.print("Shake Percentage: ");
    Serial.print(shakePercentage);
    Serial.println("%");
  }
}
