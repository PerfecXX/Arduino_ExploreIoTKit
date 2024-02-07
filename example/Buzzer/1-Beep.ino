/*
Author      : Teeraphat Kullanankanjana
Version     : 1.1
Date        : 07/02/2024
Description : Plays a beep sound on the buzzer.
Copyright (C) 2023 Teeraphat Kullanankanjana. All right reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Freqency and duration(ms)
int freqency = 800;
int duration_ms = 300;

void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();
  
  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600);
}


void loop() {
  carrier.Buzzer.beep(freqency, duration_ms);
  delay(1000);
}
