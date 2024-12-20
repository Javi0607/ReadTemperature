#include <Wire.h>

#define SCLK 10
#define CS   11
#define MISO 12

byte spiRead(void){
   int i;
   byte d = 0;
   for(i = 7; i >= 0; i--) {
      digitalWrite(SCLK, LOW);
      delayMicroseconds(10);
      if(digitalRead(MISO)){
         d |= (1 << i);
      }
      digitalWrite(SCLK, HIGH);
      delayMicroseconds(10);
   }
   return d;
}

float MAX6675_read(void){
   uint16_t v;
   digitalWrite(CS, LOW);
   delayMicroseconds(10);
   v = spiRead();
   v <<= 8;
   v |= spiRead();
   digitalWrite(CS, HIGH);
   v >>= 3;
   return v * 0.25;
}

void setup(void){
   Serial.begin(9600);
   pinMode(CS, OUTPUT);
   pinMode(SCLK, OUTPUT);
   pinMode(MISO, INPUT);
   digitalWrite(CS, HIGH);
   Serial.println("  Medidor ");
   Serial.println("Termo. T-K");

}

void loop(void){
   Serial.println(MAX6675_read());
   delay(1000);
}
