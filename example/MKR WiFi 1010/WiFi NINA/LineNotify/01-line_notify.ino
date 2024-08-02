/*
Author      : Teeraphat Kullanankanjana
Version     : 1.0
Date        : 02/08/2567
Description : Connects an Arduino MKR WIFI 1010 to a Wi-Fi network and uses the LINE Notify API to send messages, stickers, and images from url. 
Copyright (C) 2024 Teeraphat Kullanankanjana. All rights reserved.
*/

#include <WiFiNINA.h>

// Wi-Fi credentials
const char* ssid = "your_ssid";
const char* password = "your_password";

// LINE Notify API details
const char* accessToken = ""; // Replace with your actual token
const char* host = "notify-api.line.me";
const int httpsPort = 443;

WiFiSSLClient client;

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  connectToWiFi();

  // Example usage of notifyMessage function
  notifyMessage("Hello from Arduino MKR WIFI1010");

  // Example usage of notifySticker function
  notifySticker("Hello with sticker!", 1, 1); // Example sticker package ID and sticker ID

  // Example usage of notifyImageURL function
  notifyImageURL("Hello with image!", "https://static.wikia.nocookie.net/chainsaw-man/images/1/1b/Pochita.PNG"); // Example image URL
}

void loop() {
  // Your code goes here
}

/*
* After this comment, there will be a Line Notify API function. 
* There is no need to make a change.
*/

// WIFI Connect function
void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");
}

// Text-Only Notification
void notifyMessage(const String &message) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected to Wi-Fi");
    return;
  }

  // Connect to LINE Notify API
  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection to LINE Notify failed!");
    return;
  }

  // URL encode the message
  String encodedMessage = urlEncode(message);

  // Prepare the POST request
  String url = "/api/notify";
  String payload = "message=" + encodedMessage;
  String request = String("POST ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Authorization: Bearer " + accessToken + "\r\n" +
                   "Content-Type: application/x-www-form-urlencoded\r\n" +
                   "Content-Length: " + payload.length() + "\r\n" +
                   "Connection: close\r\n\r\n" +
                   payload;

  // Send the request
  client.print(request);
  Serial.println("Request sent!");

  // Read and print the response
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break; // Headers ended
    Serial.println(line);
  }

  // Close the connection
  client.stop();
}

// Sticker Notification Function
// See sticker package ID and sticker ID here: https://developers.line.biz/en/docs/messaging-api/sticker-list/.
// Every notification message parameter is required.
void notifySticker(const String &message, int stickerPkgID, int stickerID) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected to Wi-Fi");
    return;
  }

  // Connect to LINE Notify API
  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection to LINE Notify failed!");
    return;
  }

  // URL encode the message
  String encodedMessage = urlEncode(message);

  // Prepare the POST request
  String url = "/api/notify";
  String payload = "message=" + encodedMessage + "&stickerPackageId=" + stickerPkgID + "&stickerId=" + stickerID;
  String request = String("POST ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Authorization: Bearer " + accessToken + "\r\n" +
                   "Content-Type: application/x-www-form-urlencoded\r\n" +
                   "Content-Length: " + payload.length() + "\r\n" +
                   "Connection: close\r\n\r\n" +
                   payload;

  // Send the request
  client.print(request);
  Serial.println("Request sent!");

  // Read and print the response
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break; // Headers ended
    Serial.println(line);
  }

  // Close the connection
  client.stop();
}

// Image from the URL Notification Function
// The image URL must be in HTTPS format and end with a.png or.jpeg file.
// Every notification message parameter is required.

void notifyImageURL(const String &message, const String &imageUrl) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected to Wi-Fi");
    return;
  }

  // Connect to LINE Notify API
  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection to LINE Notify failed!");
    return;
  }

  // URL encode the message
  String encodedMessage = urlEncode(message);
  String encodedImageUrl = urlEncode(imageUrl);

  // Prepare the POST request
  String url = "/api/notify";
  String payload = "message=" + encodedMessage + "&imageThumbnail=" + encodedImageUrl + "&imageFullsize=" + encodedImageUrl;
  String request = String("POST ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Authorization: Bearer " + accessToken + "\r\n" +
                   "Content-Type: application/x-www-form-urlencoded\r\n" +
                   "Content-Length: " + payload.length() + "\r\n" +
                   "Connection: close\r\n\r\n" +
                   payload;

  // Send the request
  client.print(request);
  Serial.println("Request sent!");

  // Read and print the response
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break; // Headers ended
    Serial.println(line);
  }

  // Close the connection
  client.stop();
}

String urlEncode(const String &msg) {
  String encodedMsg = "";
  char c;
  char code0;
  char code1;
  for (int i = 0; i < msg.length(); i++) {
    c = msg.charAt(i);
    if (c == ' ') {
      encodedMsg += '+';
    } else if (isalnum(c)) {
      encodedMsg += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      encodedMsg += '%';
      encodedMsg += code0;
      encodedMsg += code1;
    }
  }
  return encodedMsg;
}
