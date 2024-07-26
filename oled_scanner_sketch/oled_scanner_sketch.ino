#include <SPI.h>

// Визначення пінів для SPI та RSSI
#define SSP 10
#define rssi_pin A2

// Визначення кнопок
#define button_right 2
#define button_left 3

// Дані для перемикання частоти
byte data0 = 0;
byte data1 = 0;
byte data2 = 0;
byte data3 = 0;

// Мінімальна та максимальна частоти
int freq_min = 5700;
int freq_max = 6000;

// Масштаб і позиція
int zoom = 300;
int position = 5850;

// Масиви для зберігання значень RSSI і частот
int RSSIs[30] = {};
int freqs[30] = {};
int count_RSSIs = zoom / 10;
// int count_RSSIs = sizeof(RSSIs) / sizeof(RSSIs[0]);

void setup() {
  // Ініціалізація SPI:
  pinMode(SSP, OUTPUT);
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);  // Встановлення порядку передачі бітів

  // Налаштування кнопок
  pinMode(button_right, INPUT_PULLUP);
  pinMode(button_left, INPUT_PULLUP);

  // Ініціалізація серійного порту для виводу
  Serial.begin(9600);
}

// Функція перемикання частоти
void setFreq(uint32_t freq) {
  uint32_t Delitel = (freq - 479) / 2;

  byte DelitelH = Delitel >> 5;
  byte DelitelL = Delitel & 0x1F;

  data0 = DelitelL * 32 + 17;
  data1 = DelitelH * 16 + DelitelL / 8;
  data2 = DelitelH / 16;
  data3 = 0;

  digitalWrite(SSP, LOW);  // Вимкнення SSP для передачі даних
  SPI.transfer(data0);
  SPI.transfer(data1);
  SPI.transfer(data2);
  SPI.transfer(data3);
  digitalWrite(SSP, HIGH);  // Увімкнення SSP після передачі даних
}

// Функція зчитування RSSI на заданій частоті
int read_rssi_on_freq(int freq) {
  setFreq(freq);
  delay(15);  // Затримка для стабілізації частоти

  int sum = 0;
  for (int x = 0; x < 10; x++) {
    sum += analogRead(rssi_pin);  // Зчитування значення RSSI
  }
  return sum / 10;  // Середнє значення RSSI
}

// Змінні для вимірювання часу
unsigned long millis_draw = 0;
unsigned long millis_button = 0;

void loop() {
  // Обробка натискань кнопок
  if (millis() - millis_button >= 100) {
    millis_button = millis();

    if (digitalRead(button_right) == 0) position += 10;  // Збільшення позиції
    if (digitalRead(button_left) == 0) position -= 10;   // Зменшення позиції
  }

  // Обробка малювання графіка
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

    draw_graph(RSSIs, freq_min, freq_max);  // Малювання графіка

    // Альтернативний спосіб обробки RSSI
    // int index_elem = 0;
    // for (int x = freq_min; x < freq_max; x += (freq_max - freq_min) / count_RSSIs) {
    //   RSSIs[index_elem] = read_rssi_on_freq(x);
    //   index_elem++;
    // }
    // draw_graph(RSSIs, freq_min, freq_max);
  }
}
