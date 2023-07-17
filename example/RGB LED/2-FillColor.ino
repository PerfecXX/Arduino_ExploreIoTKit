/*
Author      : Teeraphat Kullanankanjana
Version     : 1.0
Date        : 17/07/2023
Description : Template file for using MKR IoT Carrier
Copyright (C) 2023 Teeraphat Kullanankanjana. All right reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Define color values
uint32_t red = carrier.leds.Color(255, 0, 0);

// Initialize variables for LED counting
int firstLedToCount = 0;
int count = 5;

void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();
}

void loop() {
  // Fill the specified LEDs with red color
  carrier.leds.fill(red, firstLedToCount, count);
  
  // Display the LED colors
  carrier.leds.show();
}
