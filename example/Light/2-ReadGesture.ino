/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.0
  Date        : 22/07/2023
  Description : Detect Gestures using Light Sensor
  Copyright (C) 2023 Teeraphat Kullanankanjana. All rights reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Variable to store the detected gesture
uint8_t gesture;

void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();

  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {
  // Check if the Light sensor has gesture data available
  if (carrier.Light.gestureAvailable()) {
    // Read the detected gesture
    gesture = carrier.Light.readGesture();
    Serial.print("Gesture: ");

    // Check the detected gesture and print the corresponding label
    if (gesture == UP) {
      Serial.println("UP");
    } else if (gesture == DOWN) {
      Serial.println("DOWN");
    } else if (gesture == LEFT) {
      Serial.println("LEFT");
    } else if (gesture == RIGHT) {
      Serial.println("RIGHT");
    }
  }
}
