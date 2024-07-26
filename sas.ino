#include <SPI.h>

#define SSP 10

// data for switchitg frequency
byte data0 = 0;
byte data1 = 0;
byte data2 = 0;
byte data3 = 0;

int freq_min = 5700;
int freq_max = 6000;

int zoom = 300;
int position = 5850;

int RSSIs[30] = {};
int freqs[30] = {};
int count_RSSIs = zoom / 10;

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
  delay(15);

  int sum = 0;
  for (int x = 0; x < 10; x++) {
    sum += analogRead(rssi_pin);
  }
  return sum / 10;
}

void setup () {
	pinMode(SSP, OUTPUT);
	SPI.begin();
	SPI.setBitOrder(LSBFIRST);

	Serial.begin(9600);
}

void loop () {
	if (millis() - millis_draw >= 300) {
	millis_draw = millis();

	freq_max = position + (zoom / 2);
	freq_min = position - (zoom / 2);

	int index_elem = 0;
	for (int x = freq_min; x < freq_max; x += 10) {
	  int max_rssi = 0;
	  for (int y = x - 3; y <= x + 3; y += 3) {
	    int rssi = read_rssi_on_freq(y);
	    if (rssi > max_rssi) max_rssi = rssi; 
	  }
	  RSSIs[index_elem] = max_rssi;
	  freqs[index_elem] = x;
	  index_elem++;
	}
}


