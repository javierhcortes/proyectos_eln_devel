#include <Arduino.h>
#include <ESP32Encoder.h>

#define ENCODER_CLK_PIN 18
#define ENCODER_DT_PIN  19

#define ENCODER_SW_PIN  5

ESP32Encoder encoder;

long ultimoValorContador = 0;
bool botonPresionadoAnteriormente = false;

void setup() {
  Serial.begin(115200);

  pinMode(ENCODER_SW_PIN, INPUT_PULLUP);

  encoder.attachHalfQuad(ENCODER_CLK_PIN, ENCODER_DT_PIN);

  encoder.setCount(0);

  Serial.println("Encoder listo con la librería ESP32Encoder.");
}

void loop() {
  long valorContador = encoder.getCount();

  if (valorContador != ultimoValorContador) {
    ultimoValorContador = valorContador;
    Serial.print("Valor del encoder: ");
    Serial.println(valorContador);
  }

  bool botonPresionado = (digitalRead(ENCODER_SW_PIN) == LOW);

  if (botonPresionado && !botonPresionadoAnteriormente) {
    Serial.println("¡Botón presionado!");
    delay(50); 
  }
  
  botonPresionadoAnteriormente = botonPresionado;
}