#include <Arduino.h>

#define LED_BUILTIN 2

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello World");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  tone(17, 1000, 100); // (pin, frequency, duration)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}