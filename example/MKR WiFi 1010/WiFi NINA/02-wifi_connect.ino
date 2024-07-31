/*
Author      : Teeraphat Kullanankanjana
Version     : 1.0
Date        : 31/07/2024
Description : Connects to a specified WiFi network using SSID and password, and prints connection details.
Copyright (C) 2024 Teeraphat Kullanankanjana. All rights reserved.
*/

#include <WiFiNINA.h>  // Include the WiFiNINA library for WiFi functionality

const char* ssid = "your_SSID";        // Replace with your network's SSID
const char* password = "your_PASSWORD"; // Replace with your network's password

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud rate
  
  while (!Serial) {
    ; // Wait for the serial port to connect (needed for some boards)
  }

  // Check for the presence of the WiFi shield
  if (WiFi.status() == WL_NO_MODULE) {
    // If the WiFi module is not detected, print an error message
    Serial.println("WiFi module not detected");
    while (true) {
      // Enter an infinite loop to halt further execution
    }
  }

  // Attempt to connect to the specified network
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println("...");
  
  WiFi.begin(ssid, password);  // Start the connection process

  // Wait for the connection to be established
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);  // Wait for 500 milliseconds before retrying
    Serial.print(".");  // Print a dot to indicate the connection attempt
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    // Connection successful, print connection details
    Serial.println("\nConnected successfully!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());  // Print the local IP address
    Serial.print("Signal Strength (dBm): ");
    Serial.println(WiFi.RSSI());  // Print the signal strength of the connected network
  } else {
    // Connection failed
    Serial.println("\nFailed to connect to the network.");
  }
}

void loop() {
  // The loop function is empty because no repeated actions are needed
}
