#include <SPI.h>
#include "GyverButton.h"

#define SSP 10
#define rssi_pin A2

GButton butt_r(2);
GButton butt_l(3);

// data for switchitg frequency
byte data0 = 0;
byte data1 = 0;
byte data2 = 0;
byte data3 = 0;

int RSSIs[32] = {};
int count_RSSIs = sizeof(RSSIs) / sizeof(RSSIs[0]);

int freq_min = 5700;
int freq_max = 6000;

int zoom = 300;
int position = 5850;

void setup() {
  // initialize SPI:
  pinMode(SSP, OUTPUT);
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);

  // butt_r.setDebounce(50);
  // butt_r.setTimeout(300);
  // butt_r.setClickTimeout(300);

  // butt_l.setDebounce(50);
  // butt_l.setTimeout(300);
  // butt_l.setClickTimeout(300);

  Serial.begin(9600);
}

// frequency switching function
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

int read_rssi_on_freq(int freq) {
  setFreq(freq);

  int sum = 0;
  for (int x = 0; x < 10; x++) {
    sum += analogRead(rssi_pin);
  }
  return sum / 10;
}

unsigned int millis_draw = 0;

void loop() {
  freq_max = position + (zoom / 2);
  freq_min = position - (zoom / 2);

  if (millis() >= millis_draw) {
    millis_draw += 100;

    int index_elem = 0;
    for (int x = freq_min; x < freq_max; x += (freq_max - freq_min) / count_RSSIs) {
      RSSIs[index_elem] = read_rssi_on_freq(x);
      index_elem++;
    }
    draw_graph(RSSIs, freq_min, freq_max);
  }
}
