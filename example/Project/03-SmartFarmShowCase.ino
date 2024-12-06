#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

#define SOIL1_PIN A5
#define SOIL2_PIN A6

#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define ORANGE 0xFC00
#define WHITE 0xFFFF
#define BLACK 0x0000
#define GREEN 0x07E0
#define BLUE 0x001F
#define CYAN 0x07FF
#define RED 0xF800

uint16_t RGBtoRGB565(uint8_t r, uint8_t g, uint8_t b) {
  uint16_t r5 = (r * 31) / 255;
  uint16_t g6 = (g * 63) / 255;
  uint16_t b5 = (b * 31) / 255;
  uint16_t rgb565 = (r5 << 11) | (g6 << 5) | b5;
  return rgb565;
}

float temperature;
float humidity;
int r, g, b;

int soil1_val;
int soil1_percentage;
int soil2_val;
int soil2_percentage;

void setup() {
  carrier.begin();
  Serial.begin(9600);
  carrier.display.fillScreen(WHITE);
  carrier.display.setTextColor(BLACK);
  carrier.display.setTextSize(2);
  carrier.display.setCursor(20, 10);
  carrier.display.print("MKR IOT Carrier");

  carrier.display.setTextSize(3);
  carrier.display.setTextColor(RGBtoRGB565(255,153,51));
  carrier.display.setCursor(10, 50);
  carrier.display.print("TEMP:");
  carrier.display.setTextColor(CYAN);
  carrier.display.setCursor(10, 80);
  carrier.display.print("HUMID:");
  carrier.display.setTextColor(RGBtoRGB565(255,215,0));
  carrier.display.setCursor(10, 110);
  carrier.display.print("LIGHT:");

  carrier.display.setTextColor(RGBtoRGB565(255,102,255));
  carrier.display.setCursor(10, 150);
  carrier.display.print("R1:");
  carrier.display.setCursor(10, 180);
  carrier.display.print("R2:");

  carrier.display.drawLine(130, 240, 130, 140, BLACK);

  carrier.display.setTextColor(RGBtoRGB565(255,153,204));
  carrier.display.setCursor(140, 150);
  carrier.display.print("SOIL1");
  carrier.display.setCursor(140, 200);
  carrier.display.print("SOIL2");
}

void loop() {

  carrier.Buttons.update();

  soil1_val = analogRead(SOIL1_PIN);
  soil1_percentage = map(soil1_val, 0, 1023, 100, 0);

  soil2_val = analogRead(SOIL2_PIN);
  soil2_percentage = map(soil2_val, 0, 1023, 100, 0);
  
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();

  if (carrier.Buttons.onTouchDown(TOUCH1)) {
    if (carrier.Relay1.getStatus())
      carrier.Relay1.close();
    else
      carrier.Relay1.open();
  }

  if (carrier.Buttons.onTouchDown(TOUCH2)) {
    if (carrier.Relay2.getStatus())
      carrier.Relay2.close();
    else
      carrier.Relay2.open();
  }

  if (carrier.Light.colorAvailable()) {
    carrier.Light.readColor(r, g, b);
  }
  Serial.print("Temperature(C):");
  Serial.println(temperature);

  Serial.print("Humidity(%):");
  Serial.println(humidity);
  Serial.print("Red: ");
  Serial.print(r);
  Serial.print(" Green: ");
  Serial.print(g);
  Serial.print(" Blue: ");
  Serial.println(b);

  Serial.print("Soil1SensorValue:");
  Serial.println(soil1_val);

  Serial.print("Soil1Percentage:");
  Serial.println(soil1_percentage);

  Serial.print("Soil2SensorValue:");
  Serial.println(soil2_val);

  Serial.print("Soil2Percentage:");
  Serial.println(soil2_percentage);

  // Update the text
  carrier.display.setTextSize(3);
  carrier.display.setTextColor(RGBtoRGB565(255,153,51));
  carrier.display.setCursor(120, 50);
  carrier.display.print(temperature);
  carrier.display.setTextColor(CYAN);
  carrier.display.setCursor(120, 80);
  carrier.display.print(humidity);
  carrier.display.setTextSize(2);
  carrier.display.setTextColor(RED);
  carrier.display.setCursor(120, 120);
  carrier.display.print(r);
  carrier.display.setTextColor(GREEN);
  carrier.display.setCursor(160, 120);
  carrier.display.print(g);
  carrier.display.setTextColor(BLUE);
  carrier.display.setCursor(200, 120);
  carrier.display.print(b);
  carrier.display.setTextSize(3);
  carrier.display.setTextColor(RGBtoRGB565(255,102,255));
  carrier.display.setCursor(70, 150);
  carrier.display.print(carrier.Relay1.getStatus() ? "ON" : "OFF");
  carrier.display.setCursor(70, 180);
  carrier.display.print(carrier.Relay2.getStatus() ? "ON" : "OFF");

  carrier.display.setTextColor(RGBtoRGB565(255,153,204));
  carrier.display.setTextSize(2);
  carrier.display.setCursor(170, 175);
  carrier.display.print(soil1_percentage);
  carrier.display.setCursor(170, 225);
  carrier.display.print(soil2_percentage);

  delay(100);

  // Clear The Text
  carrier.display.setTextSize(3);
  carrier.display.setTextColor(WHITE);
  carrier.display.setCursor(120, 50);
  carrier.display.print(temperature);
  carrier.display.setCursor(120, 80);
  carrier.display.print(humidity);
  carrier.display.setTextSize(2);
  carrier.display.setCursor(120, 120);
  carrier.display.print(r);
  carrier.display.setCursor(160, 120);
  carrier.display.print(g);
  carrier.display.setCursor(200, 120);
  carrier.display.print(b);
  carrier.display.setTextSize(3);
  carrier.display.setCursor(70, 150);
  carrier.display.print(carrier.Relay1.getStatus() ? "ON" : "OFF");
  carrier.display.setCursor(70, 180);
  carrier.display.print(carrier.Relay2.getStatus() ? "ON" : "OFF");
  carrier.display.setTextSize(2);
  carrier.display.setCursor(170, 175);
  carrier.display.print(soil1_percentage);
  carrier.display.setCursor(170, 225);
  carrier.display.print(soil2_percentage);
}
