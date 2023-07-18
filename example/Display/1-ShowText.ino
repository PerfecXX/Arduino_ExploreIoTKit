/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 18/07/2023
  Description : Show simple text to display.
  Copyright (C) 2023 Teeraphat Kullanankanjana. All rights reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Color definitions
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define ORANGE 0xFC00
#define WHITE 0xFFFF
#define BLACK 0x0000
#define GREEN 0x07E0
#define BLUE 0x001F
#define CYAN 0x07FF
#define RED 0xF800

void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();

  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600);

  // Set the background color of the display to white
  carrier.display.fillScreen(WHITE);
  
  // Set the text color to red
  carrier.display.setTextColor(RED);
  
  // Set the text size to 4 (large)
  carrier.display.setTextSize(4);

  // Set the cursor position on the display
  carrier.display.setCursor(60, 80);

  // Display the text "Hello" at the specified position
  carrier.display.print("Hello");
}

void loop() {
  // Your code goes here
}
