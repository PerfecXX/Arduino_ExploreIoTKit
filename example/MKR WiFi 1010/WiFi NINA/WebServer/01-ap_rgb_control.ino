/*
Author      : Teeraphat Kullanankanjana
Version     : 1.0
Date        : 31/07/2024
Description : Configures an Arduino board to function as a TCP server using the WiFiNINA library. 
              The server listens for incoming client connections on a specified port (80) and processes 
              client requests to control an RGB LED. The server provides a simple web interface to 
              adjust the LED's color through HTTP requests. It includes functionalities to start an 
              Access Point, handle client connections, parse HTTP GET requests, and update the LED's 
              color based on client input.
Copyright (C) 2024 Teeraphat Kullanankanjana. All rights reserved.
*/

#include <SPI.h>               // Include the SPI library for SPI communication
#include <WiFiNINA.h>         // Include the WiFiNINA library for WiFi functionality
#include <utility/wifi_drv.h> // Include the WiFi driver utility for pin management

// Network credentials
const char *ssid = "MKRWiFi1010-Server";   // SSID for the Access Point
const char *password = "123456789";        // Password for the Access Point

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
  Serial.begin(115200); // Start serial communication at 115200 baud rate
  
  // Set up the LED pins as output
  WiFiDrv::pinMode(RED_PIN, OUTPUT); 
  WiFiDrv::pinMode(GREEN_PIN, OUTPUT); 
  WiFiDrv::pinMode(BLUE_PIN, OUTPUT);

  // Start Access Point mode
  WiFi.beginAP(ssid, password); // Initialize the WiFi access point with the specified SSID and password
  Serial.println("Access Point started"); // Notify that the Access Point has started

  // Start the web server
  server.begin(); // Begin listening for incoming client connections on port 80
  Serial.println("Web server started"); // Notify that the web server has started

  // Print the IP address assigned to the Access Point
  IPAddress ip = WiFi.localIP(); // Get the IP address assigned to the Access Point
  Serial.print("Server IP Address: ");
  Serial.println(ip); // Print the IP address to the serial monitor
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
    Serial.println(request); // Print the request to the serial monitor

    // Extract the query string from the request
    int queryStartIndex = request.indexOf('?'); // Find the index of '?' in the request
    if (queryStartIndex != -1) { // If '?' is found
      query = request.substring(queryStartIndex + 1); // Extract the query string after '?'

      // Print the query string for debugging
      Serial.print("Query String: ");
      Serial.println(query);

      // Parse the query string to extract RGB values
      int redIndex = query.indexOf("RED=");     // Find the index of "RED="
      int greenIndex = query.indexOf("GREEN="); // Find the index of "GREEN="
      int blueIndex = query.indexOf("BLUE=");   // Find the index of "BLUE="
      int resetIndex = query.indexOf("RESET");  // Find the index of "RESET"

      if (resetIndex != -1) {
        // Reset RGB values to default (e.g., 0, 0, 0)
        red = 0;
        green = 0;
        blue = 0;
      } else {
        if (redIndex != -1) {
          int nextIndex = query.indexOf('&', redIndex); // Find the next '&' after "RED="
          if (nextIndex == -1) nextIndex = query.length(); // If no '&', use the end of the query string
          red = query.substring(redIndex + 4, nextIndex).toInt(); // Extract and convert the red value
        }

        if (greenIndex != -1) {
          int nextIndex = query.indexOf('&', greenIndex); // Find the next '&' after "GREEN="
          if (nextIndex == -1) nextIndex = query.length(); // If no '&', use the end of the query string
          green = query.substring(greenIndex + 6, nextIndex).toInt(); // Extract and convert the green value
        }

        if (blueIndex != -1) {
          blue = query.substring(blueIndex + 5).toInt(); // Extract and convert the blue value
        }
      }

      // Set the RGB values
      WiFiDrv::analogWrite(RED_PIN, red);    // Set the red LED intensity
      WiFiDrv::analogWrite(GREEN_PIN, green); // Set the green LED intensity
      WiFiDrv::analogWrite(BLUE_PIN, blue);  // Set the blue LED intensity
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
