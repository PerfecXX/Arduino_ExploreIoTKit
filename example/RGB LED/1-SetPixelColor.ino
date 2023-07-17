/*
Author      : Teeraphat Kullanankanjana
Version     : 1.0
Date        : 17/07/2023
Description : Set the color and turn on the 5 RGB LEDs with 5 colors on the Arduino MKR IoT Carrier.
Copyright (C) 2023 Teeraphat Kullanankanjana. All right reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Define color values
uint32_t red = carrier.leds.Color(255, 0, 0);
uint32_t green = carrier.leds.Color(0, 255, 0);
uint32_t blue = carrier.leds.Color(0, 0, 255);
uint32_t yellow = carrier.leds.Color(255, 255, 0);
uint32_t cyan = carrier.leds.Color(0, 255, 255);

void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();
}

void loop() {
  // Set the color of each LED
  carrier.leds.setPixelColor(0, red);     // Set LED 0 to red
  carrier.leds.setPixelColor(1, green);   // Set LED 1 to green
  carrier.leds.setPixelColor(2, blue);    // Set LED 2 to blue
  carrier.leds.setPixelColor(3, yellow);  // Set LED 3 to yellow
  carrier.leds.setPixelColor(4, cyan);    // Set LED 4 to cyan

  // Update the LEDs to display the set colors
  carrier.leds.show();
}
