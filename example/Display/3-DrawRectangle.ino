/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 18/07/2023
  Description : 1. Draw a Circle from the center Vector with the selected radius and color
                2. Draw a filled circle from the center Vector, with the selected radius and color
  Copyright (C) 2023 Teeraphat Kullanankanjana. All rights reserved.
*/

// Include the Arduino MKR IoT Carrier library
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Define color constants using the RGB565 format
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define ORANGE  0xFC00
#define WHITE   0xFFFF
#define BLACK   0x0000
#define GREEN   0x07E0
#define BLUE    0x001F
#define CYAN    0x07FF
#define RED     0xF800

void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();

  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600);

  // Set the background color of the display to white
  carrier.display.fillScreen(WHITE);

  // Draw a circle on the display at position (120, 120) with a radius of 30, using the GREEN color
  carrier.display.drawCircle(120, 120, 30, GREEN);

  // Draw a filled circle on the display at position (120, 180) with a radius of 30, using the YELLOW color
  carrier.display.fillCircle(120, 180, 30, YELLOW);
}

void loop() {
  // Your code goes here
}
