/*
Author      : Teeraphat Kullanankanjana
Version     : 1.0
Date        : 31/07/2024
Description : Scans for available WiFi networks and prints their SSIDs and signal strengths.
Copyright (C) 2024 Teeraphat Kullanankanjana. All rights reserved.
*/

#include <WiFiNINA.h>  // Include the WiFiNINA library for WiFi functionality

int numNetworks;  // Variable to store the number of WiFi networks found

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

  // Notify that network scanning is starting
  Serial.println("Scanning for networks...");
  
  numNetworks = WiFi.scanNetworks();  // Scan for available WiFi networks and store the count in numNetworks
  Serial.println("Scan complete.");  // Notify that the scan is complete
  Serial.print("Number of networks found: ");  // Print the number of networks found
  Serial.println(numNetworks);

  // Loop through each found network and print details
  for (int i = 0; i < numNetworks; i++) {
    Serial.print("Network name: ");  // Print the name of the network
    Serial.println(WiFi.SSID(i));  // Print the SSID (network name) of the i-th network
    Serial.print("Signal strength (dBm): ");  // Print the signal strength of the network
    Serial.println(WiFi.RSSI(i));  // Print the RSSI (signal strength) of the i-th network
    Serial.println("-----------------------");  // Print a separator for readability
    delay(10);  // Small delay to avoid overwhelming the serial output
  }
}

void loop() {
  // The loop function is empty because no repeated actions are needed
}
