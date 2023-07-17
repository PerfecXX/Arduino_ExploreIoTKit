/*
Author      : Teeraphat Kullanankanjana
Version     : 1.0
Date        : 17/07/2023
Description : Set the color and turn on the 5 RGB LEDs with rainbow colors moving from left to right on the Arduino MKR IoT Carrier.
Copyright (C) 2023 Teeraphat Kullanankanjana. All right reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Define the rainbow colors
uint32_t colors[] = {
  carrier.leds.Color(255, 0, 0),     // Red
  carrier.leds.Color(255, 165, 0),   // Orange
  carrier.leds.Color(255, 255, 0),   // Yellow
  carrier.leds.Color(0, 255, 0),     // Green
  carrier.leds.Color(0, 0, 255),     // Blue
  carrier.leds.Color(75, 0, 130),    // Indigo
  carrier.leds.Color(238, 130, 238)  // Violet
};

// Define the number of rainbow colors
int numColors = sizeof(colors) / sizeof(colors[0]);

int currentPixel = 0; // Variable to track the current pixel
bool movingRight = true; // Variable to indicate the direction of movement

void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();
}

void loop() {
  // Clear the LED colors from the previous frame
  carrier.leds.clear();

  // Set the color of each LED based on the rainbow
  for (int i = 0; i < 5; i++) {
    int colorIndex = (currentPixel + i) % numColors;
    carrier.leds.setPixelColor(i, colors[colorIndex]);
  }

  // Update the LEDs to display the set colors
  carrier.leds.show();

  // Move the pixel position
  if (movingRight) {
    currentPixel++;
    if (currentPixel == numColors - 1) {
      currentPixel = 3; // Reverse direction when reaching the end
      movingRight = false;
    }
  } else {
    currentPixel--;
    if (currentPixel == 0) {
      currentPixel = 2; // Reverse direction when reaching the beginning
      movingRight = true;
    }
  }

  delay(100); // Adjust the delay time as needed for the desired animation speed
}
