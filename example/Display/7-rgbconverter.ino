/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 30/07/2024
  Description : Convert the RGB color format into a 16-bit 565RGB value.
  Copyright (C) 2024 Teeraphat Kullanankanjana. All rights reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Function to convert RGB to RGB565 format
uint16_t RGBtoRGB565(uint8_t r, uint8_t g, uint8_t b) {
    // Scale RGB components to 5, 6, and 5 bits respectively
    uint16_t r5 = (r * 31) / 255;
    uint16_t g6 = (g * 63) / 255;
    uint16_t b5 = (b * 31) / 255;
    
    // Combine the components into a single 16-bit value
    uint16_t rgb565 = (r5 << 11) | (g6 << 5) | b5;
    
    return rgb565;
}

void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();

  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600);

  // Set the background color of the display to white
  carrier.display.fillScreen(RGBtoRGB565(255,255,255));
  
  // Set the text color to red
  carrier.display.setTextColor(RGBtoRGB565(255,0,0));
  
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
