/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 18/07/2023
  Description : LED control with Capacitive Touch Buttons
  Copyright (C) 2023 Teeraphat Kullanankanjana. All rights reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Define color values
uint32_t red = carrier.leds.Color(255, 0, 0);
uint32_t off = carrier.leds.Color(0, 0, 0);

void setup() {
  // Enable case-insensitive touch detection
  // Use carrier.noCase() if you want to detect both upper and lower case letters for touch buttons
  // Use carrier.withCase() if you want to detect touch events with exact casing (case-sensitive)
  carrier.noCase();

  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();

  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {
  // Updates buttons status
  carrier.Buttons.update();

  // Checks if button 0 is touched
  if (carrier.Buttons.onTouchDown(TOUCH0))
  {
    // Turns on the LED with a red color
    carrier.leds.fill(red, 0, 5);
    carrier.leds.show();
  }
  // Checks if button 1 is touched
  if (carrier.Buttons.onTouchDown(TOUCH1))
  {
    // Turns off the LED
    carrier.leds.fill(off, 0, 5);
    carrier.leds.show();
  }
}
