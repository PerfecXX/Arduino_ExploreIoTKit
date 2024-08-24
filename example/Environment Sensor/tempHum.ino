/*
  Author      : Teeraphat Kullanankanjana
  Version     : 1.1
  Date        : 24/08/2024
  Description : Read Temperature and Humidity
  Copyright (C) 2023 Teeraphat Kullanankanjana. All right reserved.
*/

// Include the Arduino MKR IoT Carrier header file (Library)
#include <Arduino_MKRIoTCarrier.h>

// Create an instance of the MKRIoTCarrier class
MKRIoTCarrier carrier;

// Variables to store temperature and humidity readings
float temperature;
float humidity;

void setup() {
  // Initialize the Arduino MKR IoT Carrier
  carrier.begin();

  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {
   
  // Read temperature and humidity from the environmental sensor
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();

  // Print the temperature and humidity readings to the serial monitor
  Serial.print("Temperature(C):");
  Serial.println(temperature);

  Serial.print("Humidity(%):");
  Serial.println(humidity);
}
