#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <ESP32Encoder.h>

#define ENCODER_CLK_PIN 25
#define ENCODER_DT_PIN  26
#define ENCODER_SW_PIN  27

#define LCD_RST_PIN   16
#define LCD_CE_PIN    17
#define LCD_DC_PIN    5
#define LCD_DIN_PIN   23
#define LCD_CLK_PIN   18
#define LCD_BL_PIN    22

ESP32Encoder encoder;
Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_CLK_PIN, LCD_DIN_PIN, LCD_DC_PIN, LCD_CE_PIN, LCD_RST_PIN);

long encoderValue = 0;
long lastEncoderValue = -1;
bool botonPresionadoAnteriormente = false;

void setup() {
  Serial.begin(115200);

  pinMode(ENCODER_SW_PIN, INPUT);
  pinMode(ENCODER_CLK_PIN, INPUT);
  pinMode(ENCODER_DT_PIN, INPUT);
  encoder.attachHalfQuad(ENCODER_DT_PIN, ENCODER_CLK_PIN);
  encoder.setCount(0);

  pinMode(LCD_BL_PIN, OUTPUT);
  analogWrite(LCD_BL_PIN, 10);

  display.begin();
  display.setContrast(55);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(10, 10);
  display.println("Encoder OK");
  display.display();
  delay(1000);
  encoder.setFilter(1023);
  lastEncoderValue = -1;
}

void loop() {
  long newPosition = encoder.getCount();
  Serial.println(newPosition);


  if (newPosition != lastEncoderValue) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Posicion:");
    
    display.setTextSize(2); 
    display.setCursor(20, 15);
    display.print(newPosition);
    
    display.display();

    lastEncoderValue = newPosition;
  }
  delay(100);
}
