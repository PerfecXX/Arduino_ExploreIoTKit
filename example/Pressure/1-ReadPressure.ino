/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 22/07/2023
  Description : Read Pressure
  Copyright (C) 2023 Teeraphat Kullanankanjana. All right reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Variables to store pressure value
float pressure;

void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();

  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {
  // Read the pressure value from a sensor
  pressure = carrier.Pressure.readPressure();

  // Print the pressure value to the serial monitor
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" kPa");
}
