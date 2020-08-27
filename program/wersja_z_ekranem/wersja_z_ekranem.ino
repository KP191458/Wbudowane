/*************************************************** 
  This is an example for the SHT31-D Humidity & Temp Sensor

  Designed specifically to work with the SHT31-D sensor from Adafruit
  ----> https://www.adafruit.com/products/2857

  These sensors use I2C to communicate, 2 pins are required to  
  interface
 ****************************************************/
 
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

bool enableHeater = false;
uint8_t loopCnt = 0;
int czerwona = 7;
int zielona = 6;


#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

Adafruit_SHT31 sht31 = Adafruit_SHT31();  
U8G2_ST7567_ENH_DG128064_F_4W_SW_SPI u8g2(U8G2_R2, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8); 


void setup() {
  u8g2.begin();
  Serial.begin(9600);
  pinMode(czerwona, OUTPUT); //Konfiguracja wyprowadzeń jako wyjścia
  pinMode(zielona, OUTPUT);

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
  }
  else
  {
    digitalWrite(czerwona, LOW);
    digitalWrite(zielona, HIGH);
  }

  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

  if (! isnan(t)) {  // check if 'is not a number'
    Serial.print("Temp *C = "); Serial.print(t); Serial.print("\t\t");
    u8g2.drawStr(10,10,"Temp *C = ");  // write something to the internal memory
    u8g2.setCursor(80, 10);
    u8g2.print(t);
  } else { 
    Serial.println("Failed to read temperature");
  }
  
  if (! isnan(h)) {  // check if 'is not a number'
    Serial.print("Hum. % = "); Serial.println(h);
    u8g2.drawStr(10,20,"Hum.  % = ");  // write something to the internal memory
    u8g2.setCursor(80, 20);
    u8g2.print(h);
  } else { 
    Serial.println("Failed to read humidity");
  }

  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000);
}
