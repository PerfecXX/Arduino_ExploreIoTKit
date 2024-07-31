/*
Author      : Teeraphat Kullanankanjana
Version     : 1.0
Date        : 31/07/2024
Description : Sets up an Arduino board as a TCP server, listens for incoming connections, and sends/receives data.
Copyright (C) 2024 Teeraphat Kullanankanjana. All rights reserved.
*/

#include <WiFiNINA.h>  // Include the WiFiNINA library for WiFi functionality

const char* ssid = "your_SSID";        // Replace with your network's SSID
const char* password = "your_PASSWORD"; // Replace with your network's password
const int port = 1102;                 // Port number to listen for incoming connections

WiFiServer server(port);  // Create a WiFiServer object listening on the specified port

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

    // Start the server
    server.begin();
    Serial.print("Server started on port ");
    Serial.println(port);
  } else {
    // Connection failed
    Serial.println("\nFailed to connect to the network.");
  }
}

void loop() {
  WiFiClient client = server.available();  // Check if a client has connected

  if (client) {
    Serial.println("New client connected!");

    while (client.connected()) {
      if (client.available()) {
        String message = client.readString();  // Read the message from the client
        Serial.print("Received: ");
        Serial.println(message);

        // Echo the message back to the client
        client.println("Message received: " + message);
      }
    }

    // Client disconnected
    Serial.println("Client disconnected.");
    client.stop();
  }
}
