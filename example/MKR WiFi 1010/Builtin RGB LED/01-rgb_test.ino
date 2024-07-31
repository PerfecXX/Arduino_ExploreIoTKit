/*
Author      : Teeraphat Kullanankanjana
Version     : 1.0
Date        : 31/07/2024
Description : Controls the RGB LED on the Arduino MKR WiFi 1010 using the WiFiNINA library.
Copyright (C) 2024 Teeraphat Kullanankanjana. All rights reserved.
*/

// Include the WiFiNINA library
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

// Define the pins for the RGB LED
#define RED_PIN   25
#define GREEN_PIN 26
#define BLUE_PIN  27

void setup() {
  // Set the RGB LED pins as outputs
  WiFiDrv::pinMode(RED_PIN, OUTPUT); 
  WiFiDrv::pinMode(GREEN_PIN, OUTPUT); 
  WiFiDrv::pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // Set the RGB LED to red
  WiFiDrv::analogWrite(RED_PIN, 255);
  WiFiDrv::analogWrite(GREEN_PIN, 0);
  WiFiDrv::analogWrite(BLUE_PIN, 0);
  delay(500);

  // Set the RGB LED to green
  WiFiDrv::analogWrite(RED_PIN, 0);
  WiFiDrv::analogWrite(GREEN_PIN, 255);
  WiFiDrv::analogWrite(BLUE_PIN, 0);
  delay(500);

  // Set the RGB LED to blue
  WiFiDrv::analogWrite(RED_PIN, 0);
  WiFiDrv::analogWrite(GREEN_PIN, 0);
  WiFiDrv::analogWrite(BLUE_PIN, 255);
  delay(500);

  // Turn off the RGB LED
  WiFiDrv::analogWrite(RED_PIN, 0);
  WiFiDrv::analogWrite(GREEN_PIN, 0);
  WiFiDrv::analogWrite(BLUE_PIN, 0);
  delay(500);
}
