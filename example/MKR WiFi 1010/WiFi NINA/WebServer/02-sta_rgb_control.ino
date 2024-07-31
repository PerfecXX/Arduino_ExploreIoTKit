/*
Author      : Teeraphat Kullanankanjana
Version     : 1.0
Date        : 31/07/2024
Description : Configures an Arduino board to function as a TCP server using the WiFiNINA library. 
              The server listens for incoming client connections on a specified port (80) and processes 
              client requests to control an RGB LED. The server provides a simple web interface to 
              adjust the LED's color through HTTP requests. It includes functionalities to connect 
              to an existing WiFi network, handle client connections, parse HTTP GET requests, and 
              update the LED's color based on client input.
Copyright (C) 2024 Teeraphat Kullanankanjana. All rights reserved.
*/

#include <SPI.h>               // Include the SPI library for SPI communication
#include <WiFiNINA.h>         // Include the WiFiNINA library for WiFi functionality

// Network credentials
const char *ssid = "YourNetworkSSID";   // SSID for the WiFi network
const char *password = "YourNetworkPassword"; // Password for the WiFi network

// Web server port
WiFiServer server(80); // Create a WiFiServer object listening on port 80

// Define the pins for the RGB LED
#define RED_PIN   25   // Pin connected to the red LED
#define GREEN_PIN 26   // Pin connected to the green LED
#define BLUE_PIN  27   // Pin connected to the blue LED

// Variables for LED control
int red = 0, green = 0, blue = 0; // Variables to hold RGB values

void setup() {
  // Initialize serial communication
  Serial.begin(9600); // Start serial communication at 115200 baud rate

  // Set up the LED pins as output
  WiFiDrv::pinMode(RED_PIN, OUTPUT); 
  WiFiDrv::pinMode(GREEN_PIN, OUTPUT); 
  WiFiDrv::pinMode(BLUE_PIN, OUTPUT);

  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println("...");
  
  WiFi.begin(ssid, password); // Start the connection to the WiFi network

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Print the IP address assigned to the Arduino
  Serial.println("\nConnected to WiFi network");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print the IP address to the serial monitor

  // Start the web server
  server.begin(); // Begin listening for incoming client connections on port 80
  Serial.println("Web server started"); // Notify that the web server has started
}

void loop() {
  // Listen for incoming clients
  WiFiClient client = server.available(); // Check if a client has connected to the server

  if (client) {
    Serial.println("New Client Connected"); // Notify that a new client has connected
    String request = ""; // String to hold the client's request
    String query = "";   // String to hold the query string from the request

    // Read the client's request
    while (client.available()) { // Loop while there are bytes available to read
      char c = client.read(); // Read a character from the client
      request += c; // Append the character to the request string
    }

    // Print the request for debugging
    Serial.print("Received Request: ");
    Serial.println(request);

    // Extract the query string from the request
    int queryStartIndex = request.indexOf("GET /control?"); // Adjusted for the correct path
    if (queryStartIndex != -1) {
      query = request.substring(queryStartIndex + 13); // Extract the query string after '?'

      // Print the query string for debugging
      Serial.print("Query String: ");
      Serial.println(query);

      // Parse the query string to extract RGB values
      int redIndex = query.indexOf("RED=");     
      int greenIndex = query.indexOf("GREEN="); 
      int blueIndex = query.indexOf("BLUE=");
      int resetIndex = query.indexOf("RESET");

      if (resetIndex != -1) {
        // Reset RGB values to default (e.g., 0, 0, 0)
        red = 0;
        green = 0;
        blue = 0;
      } else {
        if (redIndex != -1) {
          int nextIndex = query.indexOf('&', redIndex);
          if (nextIndex == -1) nextIndex = query.length();
          red = query.substring(redIndex + 4, nextIndex).toInt();
        }

        if (greenIndex != -1) {
          int nextIndex = query.indexOf('&', greenIndex);
          if (nextIndex == -1) nextIndex = query.length();
          green = query.substring(greenIndex + 6, nextIndex).toInt();
        }

        if (blueIndex != -1) {
          blue = query.substring(blueIndex + 5).toInt();
        }
      }

      // Print the RGB values for debugging
      Serial.print("Red: "); Serial.println(red);
      Serial.print("Green: "); Serial.println(green);
      Serial.print("Blue: "); Serial.println(blue);

      // Set the RGB values
      WiFiDrv::analogWrite(RED_PIN, red);   
      WiFiDrv::analogWrite(GREEN_PIN, green);
      WiFiDrv::analogWrite(BLUE_PIN, blue);
    }

    // Send HTTP response to the client
    client.println("HTTP/1.1 200 OK");               // Send HTTP 200 OK response
    client.println("Content-Type: text/html");      // Set the content type to HTML
    client.println("Connection: close");            // Indicate that the connection will be closed after the response
    client.println();                              // Blank line to separate headers from content
    client.println("<!DOCTYPE HTML>");             // HTML document start
    client.println("<html>");
    client.println("<body>");
    client.println("<h1>RGB LED Control</h1>");     // Page header
    client.println("<form action='/control' method='GET'>"); // Form for RGB control
    client.println("Red: <input type='text' name='RED' value='" + String(red) + "'><br>");  // Input for red value
    client.println("Green: <input type='text' name='GREEN' value='" + String(green) + "'><br>"); // Input for green value
    client.println("Blue: <input type='text' name='BLUE' value='" + String(blue) + "'><br>");  // Input for blue value
    client.println("<input type='submit' value='Set Color'>"); // Submit button for setting color
    client.println("<input type='submit' name='RESET' value='Reset Color'>"); // Submit button for resetting color
    client.println("</form>");
    client.println("</body>");
    client.println("</html>");

    delay(1);    // Short delay to ensure client receives response
    client.stop(); // Close the client connection
    Serial.println("Client Disconnected"); // Notify that the client has disconnected
  }
}
