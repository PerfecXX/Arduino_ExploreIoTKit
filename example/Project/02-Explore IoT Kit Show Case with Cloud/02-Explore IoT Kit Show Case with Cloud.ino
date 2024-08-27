#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <Arduino_MKRIoTCarrier.h>
#include "thingProperties.h"

MKRIoTCarrier carrier;

#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define ORANGE 0xFC00
#define WHITE 0xFFFF
#define BLACK 0x0000
#define GREEN 0x07E0
#define BLUE 0x001F
#define CYAN 0x07FF
#define RED 0xF800

uint32_t red = carrier.leds.Color(255, 0, 0);
uint32_t green = carrier.leds.Color(0, 255, 0);
uint32_t blue = carrier.leds.Color(0, 0, 255);
uint32_t yellow = carrier.leds.Color(255, 255, 0);
uint32_t cyan = carrier.leds.Color(0, 255, 255);
uint32_t off = carrier.leds.Color(0, 0, 0);

float pressure;
int proximity;
int r, g, b;
uint8_t gesture;
float aX, aY, aZ;
float gX, gY, gZ;

int scheduleMode = 0;

void setup() {
  carrier.begin();
  Serial.begin(9600);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();

  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();
  pressure = carrier.Pressure.readPressure();

  if (carrier.Light.proximityAvailable()) {
    proximity = carrier.Light.readProximity();
  }
  if (carrier.Light.colorAvailable()) {
    carrier.Light.readColor(r, g, b);
  }
  if (carrier.Light.gestureAvailable()) {
    gesture = carrier.Light.readGesture();
  }
  if (carrier.IMUmodule.accelerationAvailable()) {
    carrier.IMUmodule.readAcceleration(aX, aY, aZ);
  }
  if (carrier.IMUmodule.gyroscopeAvailable()) {
    carrier.IMUmodule.readGyroscope(gX, gY, gZ);
  }
}

void onLedStateChange() {
  Serial.println("led_state changed!");

  if (led_state) {
    carrier.leds.setPixelColor(0, red);
    carrier.leds.setPixelColor(1, green);
    carrier.leds.setPixelColor(2, blue);
    carrier.leds.setPixelColor(3, yellow);
    carrier.leds.setPixelColor(4, cyan);
    carrier.leds.show();
  } else {
    carrier.leds.clear();
    carrier.leds.show();
  }
}

void onMessageChange() {
  Serial.print("Message from Arduino IoT Cloud: ");
  Serial.println(message);

  if (message == "help" || message == "help?" || message == "?") {
    message = "Enter this command in Messenger Widget!\n";
    message += "led on\n";
    message += "led off\n";
    message += "relay1 on\n";
    message += "relay2 on\n";
    message += "relay all on\n";
    message += "relay1 off\n";
    message += "relay2 off\n";
    message += "relay all off\n";
    message += "buzzer beep\n";
    message += "temperature?\n";
    message += "humidity?\n";
    message += "proximity?\n";
    message += "gesture?\n";
    message += "color?\n";
    message += "pressure?\n";
    message += "gyro?\n";
    message += "accel?\n";
    message += "relay?\n";
  } else if (message == "help2" || message == "help2?") {
    message = "Enter this command in Messenger Widget!\n";
    message += "schdule?\n";
    message += "schdule mode?\n";
    message += "schdule device led\n";
    message += "schdule device relay\n";
    message += "schdule device display\n";
  } else if (message == "led on") {
    message = "led on!";
    carrier.leds.setPixelColor(0, red);
    carrier.leds.setPixelColor(1, green);
    carrier.leds.setPixelColor(2, blue);
    carrier.leds.setPixelColor(3, yellow);
    carrier.leds.setPixelColor(4, cyan);
    carrier.leds.show();
  } else if (message == "led off") {
    message = "led off!";
    carrier.leds.clear();
    carrier.leds.show();
  } else if (message == "temperature?") {
    message = "Your temperature is: ";
    message += temperature;
    message += " C";
  } else if (message == "humidity?") {
    message = "Your humidity is: ";
    message += humidity;
    message += " %RH";
  } else if (message == "proximity?") {
    message = "Your proximity is: ";
    message += proximity;
  } else if (message == "gesture?") {
    message = "Your gesture is: ";
    message += gesture;
  } else if (message == "color?") {
    message = "Your color(R,G,B) is: (";
    message += r;
    message += ",";
    message += g;
    message += ",";
    message += b;
    message += ")";
  } else if (message == "gyro?") {
    message = "Your gyro(gX,gY,gZ) is: (";
    message += gX;
    message += ",";
    message += gY;
    message += ",";
    message += gZ;
    message += ")";
  } else if (message == "accel?") {
    message = "Your accel(aX,aY,aZ) is: (";
    message += aX;
    message += ",";
    message += aY;
    message += ",";
    message += aZ;
    message += ")";
  } else if (message == "pressure?") {
    message = "Your pressure is: ";
    message += pressure;
  } else if (message == "relay?") {
    message = "Relay1 status: ";
    message += carrier.Relay1.getStatus() ? "ON" : "OFF";
    message += "\n";
    message += "Relay2 status: ";
    message += carrier.Relay2.getStatus() ? "ON" : "OFF";
  } else if (message == "relay1 on") {
    carrier.Relay1.open();
  } else if (message == "relay1 off") {
    carrier.Relay1.close();
  } else if (message == "relay2 on") {
    carrier.Relay2.open();
  } else if (message == "relay2 off") {
    carrier.Relay2.close();
  } else if (message == "relay all on") {
    carrier.Relay1.open();
    carrier.Relay2.open();
  } else if (message == "relay all off") {
    carrier.Relay1.close();
    carrier.Relay2.close();
  } else if (message == "buzzer beep") {
    carrier.Buzzer.beep(800, 300);
  } else if (message == "schdule device led") {
    scheduleMode = 0;
  } else if (message == "schdule device relay") {
    scheduleMode = 1;
  } else if (message == "schdule device display") {
    scheduleMode = 2;
  } else if (message == "\x1b") {
  } else {
      message = "Command Not Found!\n";
      message += "Type \"help\" to see all commands!";
  }
  }

  void onSchedulerChange() {
    if (scheduler.isActive()) {

      Serial.println("scheduler Activated!");

      // RGB LED
      if (scheduleMode == 0) {
        carrier.leds.fill(green,0,5);
        carrier.leds.show();
      }
    }else{
      Serial.println("scheduler deactivated!");

      if (scheduleMode == 0) {
        carrier.leds.fill(off,0,5);
        carrier.leds.show();
      }
    }
  }

  void onTemperatureChange() {
    // Placeholder for temperature change functionality
  }

  void onHumidityChange() {
    // Placeholder for humidity change functionality
  }
