/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 18/07/2023
  Description : 1. Draw a rectangle
                2. Draw a filled rectangle
                3. Draw a rounded rectangle
                4. Draw a filled and rounded rectangle
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

  // Draw a rectangle on the display at position (80, 80) with dimensions 40x40, using the BLACK color
  carrier.display.drawRect(80, 80, 40, 40, BLACK);

  // Draw a filled rectangle on the display at position (80, 140) with dimensions 40x40, using the MAGENTA color
  carrier.display.fillRect(80, 140, 40, 40, MAGENTA);

  // Draw a rounded rectangle on the display at position (80, 190) with dimensions 80x40, using the BLUE color and a corner radius of 3
  carrier.display.drawRoundRect(80, 190, 80, 40, 3, BLUE);

  // Draw a filled rounded rectangle on the display at position (160, 120) with dimensions 20x60, using the RED color and a corner radius of 3
  carrier.display.fillRoundRect(160, 120, 20, 60, 3, RED);
}

void loop() {
  // Your code goes here
}
