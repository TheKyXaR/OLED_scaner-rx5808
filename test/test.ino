#include <SPI.h>

#define SSP 10
#define rssi_pin A2

byte data0 = 0;
byte data1 = 0;
byte data2 = 0;
byte data3 = 0;

void setFreq(uint32_t freq) {
  uint32_t Delitel = (freq - 479) / 2;

  byte DelitelH = Delitel >> 5;
  byte DelitelL = Delitel & 0x1F;

  data0 = DelitelL * 32 + 17;
  data1 = DelitelH * 16 + DelitelL / 8;
  data2 = DelitelH / 16;
  data3 = 0;

  digitalWrite(SSP, LOW);
  SPI.transfer(data0);
  SPI.transfer(data1);
  SPI.transfer(data2);
  SPI.transfer(data3);
  digitalWrite(SSP, HIGH);
}

int read_rssi_on_freq(int freq, int __delay__) {
  setFreq(freq);

  delay(__delay__);

  int sum = 0;
  for (int x = 0; x < 5; x++) {
    sum += analogRead(rssi_pin);
    delay(5);
  }
  return sum / 10;
}

void setup() {
  pinMode(SSP, OUTPUT);
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);

  Serial.begin(9600);

  Serial.println("Wait 3 secs");
  delay(3000);

  for (int __delay__ = 50; __delay__ >= 0; __delay__--) {
    Serial.print("Delay - ");
    Serial.println(__delay__);

    Serial.println();

    for (int x = 0; x < 10; x++) {
      Serial.print("5500 - ");
      Serial.print(read_rssi_on_freq(5500, __delay__));
      Serial.print(", ");
      Serial.print("5917 - ");
      Serial.println(read_rssi_on_freq(5917, __delay__));
    }
  }

  Serial.print("Done");
}

void loop() {}

Delay - 50

5500 - 176, 5917 - 274
5500 - 175, 5917 - 279
5500 - 175, 5917 - 280
5500 - 175, 5917 - 286
5500 - 175, 5917 - 291
5500 - 175, 5917 - 294
5500 - 175, 5917 - 296
5500 - 177, 5917 - 296
5500 - 174, 5917 - 280
5500 - 176, 5917 - 252

Delay - 15

5500 - 176, 5917 - 280
5500 - 175, 5917 - 284
5500 - 175, 5917 - 286
5500 - 175, 5917 - 286
5500 - 175, 5917 - 288
5500 - 175, 5917 - 299
5500 - 175, 5917 - 284
5500 - 177, 5917 - 295
5500 - 174, 5917 - 291
5500 - 176, 5917 - 280

Delay - 0

5500 - 176, 5917 - 180
5500 - 175, 5917 - 185
5500 - 175, 5917 - 182
5500 - 175, 5917 - 181
5500 - 175, 5917 - 174
5500 - 175, 5917 - 123
5500 - 175, 5917 - 153
5500 - 177, 5917 - 113
5500 - 174, 5917 - 174
5500 - 176, 5917 - 106

