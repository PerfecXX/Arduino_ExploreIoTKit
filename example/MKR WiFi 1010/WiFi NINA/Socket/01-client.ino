/*
Author      : Teeraphat Kullanankanjana
Version     : 1.1
Date        : 31/07/2024
Description : Connects to a specified WiFi network, establishes a TCP connection to a specified IP and port,
              and sends/receives data through the socket.
Copyright (C) 2024 Teeraphat Kullanankanjana. All rights reserved.
*/

#include <WiFiNINA.h>  // Include the WiFiNINA library for WiFi functionality

const char* ssid = "your_SSID";        // Replace with your network's SSID
const char* password = "your_PASSWORD"; // Replace with your network's password
IPAddress serverIP(192, 168, 31, 50);   // Replace with the IP address you want to connect to
const int port = 1102;                 // Replace with the port you want to connect to

WiFiClient client;  // Create a WiFiClient object

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

    // Attempt to connect to the server
    Serial.print("Connecting to server at ");
    Serial.print(serverIP);
    Serial.print(":");
    Serial.println(port);
    
    if (client.connect(serverIP, port)) {
      Serial.println("Connected to server!");
      
      // Send data to the server
      client.println("Hello from Arduino!");
      Serial.println("Data sent to server.");

      // Wait for a response from the server
      while (client.connected() || client.available()) {
        if (client.available()) {
          String response = client.readString();
          Serial.print("Received from server: ");
          Serial.println(response);
        }
      }
      
      // Close the connection
      client.stop();
      Serial.println("Connection closed.");
    } else {
      // Connection failed
      Serial.println("Failed to connect to server.");
    }
  } else {
    // Connection failed
    Serial.println("\nFailed to connect to the network.");
  }
}

void loop() {
  // The loop function is empty because no repeated actions are needed
}
