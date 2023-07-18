/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 18/07/2023
  Description : Control relays with capacitive touch buttons and display relay status on the screen.
  Copyright (C) 2023 Teeraphat Kullanankanjana. All right reserved.
*/

// Include the necessary library for the Arduino MKR IoT Carrier board
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

void setup() {
  carrier.noCase(); // Enable case-insensitive touch detection
  carrier.begin(); // Initialize the Arduino MKR IoT Carrier
  Serial.begin(9600); // Initialize serial communication for debugging

  // Clear the screen by filling it with black
  carrier.display.fillScreen(0x0000);

  // Set the text size for the display
  carrier.display.setTextSize(2);

  // Display initial status on the screen
  updateDisplay();
}


void loop() {
  // Update buttons status
  carrier.Buttons.update();

  // Check if button 1 is touched
  if (carrier.Buttons.onTouchDown(TOUCH1)) {
    // Control relay1: Turn it ON if it's OFF, or turn it OFF if it's ON
    if (carrier.Relay1.getStatus())
      carrier.Relay1.close();
    else
      carrier.Relay1.open();

    updateDisplay(); // Update the display to reflect the new relay status
  }

  // Check if button 2 is touched
  if (carrier.Buttons.onTouchDown(TOUCH2)) {
    // Control relay2: Turn it ON if it's OFF, or turn it OFF if it's ON
    if (carrier.Relay2.getStatus())
      carrier.Relay2.close();
    else
      carrier.Relay2.open();

    updateDisplay(); // Update the display to reflect the new relay status
  }
}

// Function to update the display with the current relay status
void updateDisplay() {
  carrier.display.fillScreen(0x0000); // Fill the screen with black

  // Set the cursor position on the display for relay1 status
  carrier.display.setCursor(10, 20);
  carrier.display.print("Relay1: ");
  carrier.display.println(carrier.Relay1.getStatus() ? "ON" : "OFF");

  // Set the cursor position on the display for relay2 status
  carrier.display.setCursor(10, 40);
  carrier.display.print("Relay2: ");
  carrier.display.println(carrier.Relay2.getStatus() ? "ON" : "OFF");
}
