/*
Author      : Teeraphat Kullanankanjana
Version     : 1.0
Date        : 17/07/2023
Description : Fill all of the RGB LED pixels with the rainbow color, then reverse.
Copyright (C) 2023 Teeraphat Kullanankanjana. All right reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Define color values
uint32_t rainbowColors[] = {
  carrier.leds.Color(255, 0, 0),    // Red
  carrier.leds.Color(255, 165, 0),  // Orange
  carrier.leds.Color(255, 255, 0),  // Yellow
  carrier.leds.Color(0, 255, 0),    // Green
  carrier.leds.Color(0, 0, 255),    // Blue
  carrier.leds.Color(75, 0, 130),   // Indigo
  carrier.leds.Color(238, 130, 238) // Violet
};
int numColors = sizeof(rainbowColors) / sizeof(rainbowColors[0]);

// Initialize variables for LED counting
int firstLedToCount = 0; // Index of the first LED to count
int count = 5; // Number of LEDs to count

void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();
}

void loop() {
  // Run the rainbow animation forwards
  for (int i = 0; i < numColors; i++) {
    // Fill the specified LEDs with the current rainbow color
    carrier.leds.fill(rainbowColors[i], firstLedToCount, count);

    // Display the LED colors
    carrier.leds.show();

    // Delay for 500 milliseconds
    delay(500);
  }

  // Run the rainbow animation backwards
  for (int i = numColors - 1; i >= 0; i--) {
    // Fill the specified LEDs with the current rainbow color
    carrier.leds.fill(rainbowColors[i], firstLedToCount, count);

    // Display the LED colors
    carrier.leds.show();

    // Delay for 500 milliseconds
    delay(500);
  }
}
