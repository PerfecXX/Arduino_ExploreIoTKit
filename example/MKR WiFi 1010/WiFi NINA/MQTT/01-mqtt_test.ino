/*
Author      : Teeraphat Kullanankanjana
Version     : 1.0
Date        : 31/07/2024
Description : Connects to a specified WiFi network, publishes user-entered text to a specified MQTT topic,
              and subscribes to the same topic to listen for incoming messages. The MQTT connection is maintained
              and messages are processed via serial input and MQTT callbacks. The code handles WiFi connection,
              MQTT connection, publishing messages, and receiving messages using the Arduino MKR WiFi 1010.
Copyright (C) 2024 Teeraphat Kullanankanjana. All rights reserved.
*/

// Include necessary libraries
#include <WiFiNINA.h>
#include <PubSubClient.h>

// Replace with your network credentials
const char* ssid = "your_ssid";
const char* password = "your_password";

// MQTT broker address
const char* mqtt_server = "test.mosquitto.org";

// MQTT topic
const char* mqtt_topic = "test/test";

// Create instances for WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

// Function to handle incoming messages
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Function to connect to MQTT broker
void connectMQTT() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    // Generate a random client ID
    String clientId = "ArduinoClient-";
    clientId += String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Subscribe to the topic
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Connect to WiFi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.print("...");
    WiFi.begin(ssid, password);
    delay(5000);
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());  // Print the local IP address
  Serial.print("Signal Strength (dBm): ");
  Serial.println(WiFi.RSSI());  // Print the signal strength of the connected network

  // Set up MQTT server and callback
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // Connect to MQTT broker
  connectMQTT();
}

void loop() {
  // Ensure the client is connected
  if (!client.connected()) {
    connectMQTT();
  }
  client.loop();

  // Check if serial data is available
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    message.trim();  // Remove any leading or trailing whitespace

    // Publish the message to the MQTT topic
    client.publish(mqtt_topic, message.c_str());
    Serial.print("Published: ");
    Serial.println(message);
  }
}
