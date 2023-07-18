/*
Author      : Teeraphat Kullanankanjana
Version     : 1.0
Date        : 18/07/2023
Description : Get the status when capacitive touch buttons have been touched
Copyright (C) 2023 Teeraphat Kullanankanjana. All right reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

void setup() {
  // Enable case-insensitive touch detection
  // Use carrier.noCase() if you want to detect both upper and lower case letters for touch buttons
  // Use carrier.withCase() if you want to detect touch events with exact casing (case-sensitive)
  carrier.noCase();
  
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();
  
  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop(){
  // Updates buttons status
  carrier.Buttons.update();

  // Checks if button 0 is touched
  if (carrier.Buttons.onTouchDown(TOUCH0))
  {
    Serial.println("Button 0 pressed down");
  }
  // Checks if button 1 is touched
  if (carrier.Buttons.onTouchDown(TOUCH1))
  {
    Serial.println("Button 1 pressed down");
  }
  // Checks if button 2 is touched
  if (carrier.Buttons.onTouchDown(TOUCH2))
  {
    Serial.println("Button 2 pressed down");
  }
  // Checks if button 3 is touched
  if (carrier.Buttons.onTouchDown(TOUCH3))
  {
    Serial.println("Button 3 pressed down");
  }
  // Checks if button 4 is touched
  if (carrier.Buttons.onTouchDown(TOUCH4))
  {
    Serial.println("Button 4 pressed down");
  }
}
