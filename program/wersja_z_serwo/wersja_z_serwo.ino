/*************************************************** 
  This is an example for the SHT31-D Humidity & Temp Sensor

  Designed specifically to work with the SHT31-D sensor from Adafruit
  ----> https://www.adafruit.com/products/2857

  These sensors use I2C to communicate, 2 pins are required to  
  interface
 ****************************************************/
 
#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include "Adafruit_SHT31.h"

bool enableHeater = false;
uint8_t loopCnt = 0;
int czerwona = 7;
int zielona = 6;

Servo servo;
Adafruit_SHT31 sht31 = Adafruit_SHT31();  


void setup() {
  Serial.begin(9600);
  pinMode(czerwona, OUTPUT); //Konfiguracja wyprowadzeń jako wyjścia
  pinMode(zielona, OUTPUT);
  servo.attach(5);

  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("SHT31 test");
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
 }
}


void loop() {
  int angle = 0;
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  if(h>70.0)
  {
    digitalWrite(czerwona, HIGH);
    digitalWrite(zielona, LOW);
    servo.write(0);
    delay(1000);
  }
  else
  {
    digitalWrite(czerwona, LOW);
    digitalWrite(zielona, HIGH);
    servo.write(90);
    delay(1000);
  }

  if (! isnan(t)) {  // check if 'is not a number'
    Serial.print("Temp *C = "); Serial.print(t); Serial.print("\t\t");
  } else { 
    Serial.println("Failed to read temperature");
  }
  
  if (! isnan(h)) {  // check if 'is not a number'
    Serial.print("Hum. % = "); Serial.println(h);
  } else { 
    Serial.println("Failed to read humidity");
  }

  delay(1000);
}
