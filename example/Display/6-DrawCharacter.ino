/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 18/07/2023
  Description : Draw a character
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

  // Draw the character 'H' on the display at position (80, 80) with BLACK outline, RED fill color, and font size 10
  carrier.display.drawChar(80, 80, 'H', BLACK, RED, 10);
}

void loop() {
  // Your code goes here
}
