/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.2
  Date        : 18/07/2023
  Description : Get the status when capacitive touch buttons have been touched and display counters on the screen.
  Copyright (C) 2023 Teeraphat Kullanankanjana. All right reserved.
*/

// Include the necessary library for the Arduino MKR IoT Carrier board
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Array to store counters for each button
int counter[5] = {0};

// Setup function: This runs once when the device is powered on or reset
void setup() {
  carrier.noCase(); // Enable case-insensitive touch detection
  carrier.begin(); // Initialize the Arduino MKR IoT Carrier
  Serial.begin(9600); // Initialize serial communication for debugging
  
  // Clear the screen by filling it with black
  carrier.display.fillScreen(0x0000);
  
  // Set the text size for the display
  carrier.display.setTextSize(2);
  
  // Display initial counters on the screen
  updateDisplay();
}

// Loop function: This runs repeatedly as long as the device is on
void loop() {
  // Update buttons status
  carrier.Buttons.update();
  
  // Check if button 0 is touched
  if (carrier.Buttons.onTouchDown(TOUCH0)) {
    counter[0]++; // Increment the counter for Button 0
    updateDisplay(); // Update the display to reflect the new counter value
  }
  // Check if button 1 is touched
  if (carrier.Buttons.onTouchDown(TOUCH1)) {
    counter[1]++; // Increment the counter for Button 1
    updateDisplay(); // Update the display to reflect the new counter value
  }
  // Check if button 2 is touched
  if (carrier.Buttons.onTouchDown(TOUCH2)) {
    counter[2]++; // Increment the counter for Button 2
    updateDisplay(); // Update the display to reflect the new counter value
  }
  // Check if button 3 is touched
  if (carrier.Buttons.onTouchDown(TOUCH3)) {
    counter[3]++; // Increment the counter for Button 3
    updateDisplay(); // Update the display to reflect the new counter value
  }
  // Check if button 4 is touched
  if (carrier.Buttons.onTouchDown(TOUCH4)) {
    counter[4]++; // Increment the counter for Button 4
    updateDisplay(); // Update the display to reflect the new counter value
  }
}

// Function to update the display with the current counters for each button
void updateDisplay() {
  carrier.display.fillScreen(0x0000); // Fill the screen with black
  for (int i = 0; i < 5; i++) {
    // Set the cursor position on the display
    carrier.display.setCursor(10, i * 20);
    
    // Print the button number
    carrier.display.print("Button ");
    carrier.display.print(i);
    carrier.display.print(": ");
    
    // Print the counter value for each button
    carrier.display.println(counter[i]);
  }
}
