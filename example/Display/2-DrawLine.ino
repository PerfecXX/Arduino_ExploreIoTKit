/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 18/07/2023
  Description : Line Drawing
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

// Setup function: runs once when the board is powered on or reset
void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();

  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600);

  // Set the background color of the display to white
  carrier.display.fillScreen(WHITE);

  // Draw the first line (from point (0, 20) to point (100, 100)) in red color
  carrier.display.drawLine(0, 20, 100, 100, RED);

  // Draw the second line (from point (20, 100) to point (100, 20)) in blue color
  carrier.display.drawLine(20, 100, 100, 20, BLUE);
}

// Loop function: runs repeatedly after setup() has finished
void loop() {
  // Your code goes here (if you want to create dynamic animations or interact with the display)
}
