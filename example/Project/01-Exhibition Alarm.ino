#define IR1_PIN 21
#define IR2_PIN 20
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define ORANGE 0xFC00
#define WHITE 0xFFFF
#define BLACK 0x0000
#define GREEN 0x07E0
#define BLUE 0x001F
#define CYAN 0x07FF
#define RED 0xF800

#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

int countIn = 0;
int countOut = 0;
int r, g, b = 0;
bool alarm = false;
int sensor1State = HIGH;  
int sensor2State = HIGH;
int peopleCount = 0;
unsigned long lastCountTime = 0;
unsigned long countDelay = 1000;
uint32_t colorGreen = carrier.leds.Color(0, 10, 0);
uint32_t colorRed = carrier.leds.Color(10, 0, 0);
uint32_t colorYellow = carrier.leds.Color(10, 10, 0);

void setup() {
  pinMode(IR1_PIN, INPUT);
  pinMode(IR2_PIN, INPUT);
  carrier.withCase();
  carrier.begin();
  Serial.begin(9600);
  carrier.leds.fill(colorYellow, 0, 5);
  carrier.leds.show();
  carrier.display.fillScreen(WHITE);
  carrier.display.setTextColor(YELLOW);
  carrier.display.setRotation(0);
  carrier.display.setTextSize(4);
  carrier.display.setCursor(0, 80);
  carrier.display.print("STAND BY!");
}

void loop() {
  unsigned long currentTime = millis();
  
  sensor1State = digitalRead(IR1_PIN);
  sensor2State = digitalRead(IR2_PIN);

  if (carrier.Light.colorAvailable()) {
    carrier.Light.readColor(r, g, b);
  }

  Serial.print("Red: ");
  Serial.print(r);
  Serial.print(" Green: ");
  Serial.print(g);
  Serial.print(" Blue: ");
  Serial.println(b);

  if (r > 10 && b > 10 && g > 10) {
    alarm = true;
  } else {
    alarm = false;
  }

  if (alarm) {
    carrier.leds.fill(colorRed, 0, 5);
    carrier.leds.show();
    Serial.println("The Item has been stolen");
    carrier.Buzzer.beep(800, 200);

    carrier.display.fillScreen(RED);
    carrier.display.setTextColor(WHITE);
    carrier.display.setCursor(50, 50);
    carrier.display.print("ALARM!");
  } else {
    carrier.leds.fill(colorGreen, 0, 5);
    carrier.leds.show();
    Serial.println("Your Item are fine!");
    carrier.Buzzer.beep(0, 1);

    carrier.display.fillScreen(GREEN);
    carrier.display.setTextColor(WHITE);
    carrier.display.setCursor(50, 50);
    carrier.display.print("NORMAL");
  }

  if (sensor1State == LOW && currentTime - lastCountTime >= countDelay) {
    countIn++;
    lastCountTime = currentTime;
    Serial.println("Person entered.");
    peopleCount++;
  }

  if (sensor2State == LOW && currentTime - lastCountTime >= countDelay) {
    countOut++;
    lastCountTime = currentTime;
    Serial.println("Person exited.");
    peopleCount--;

    if (peopleCount < 0) {
      peopleCount = 0;
    }
  }
  
  carrier.display.setTextColor(WHITE);
  carrier.display.setCursor(0, 120);
  carrier.display.print("IN ROOM:");
  carrier.display.setCursor(200, 120);
  carrier.display.print(peopleCount);

  Serial.print("People in the room: ");
  Serial.println(peopleCount);

  delay(100);  // Add a small delay to stabilize sensor readings
}
