#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Визначення параметрів екрану
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// Ініціалізація об'єкту для дисплея
Adafruit_SSD1306 dis(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Функція для малювання ліній графіка
void draw_lines(int rssi_array[], int min_rssi, int max_rssi, int freq_max_rssi) {
  for (int x = 0; x < count_RSSIs; x++) {
    dis.writeLine(30 + (x * 3), 48, 
                  30 + (x * 3), 48 - map(rssi_array[x], min_rssi - 10, max_rssi + 10, 0, 45), 
                  WHITE);
  }

  // Відображення частоти з максимальним значенням RSSI
  dis.setCursor(64, 10);
  dis.print(freq_max_rssi);
}

// Функція для малювання графіка
void draw_graph(int rssi_array[], int freq_min, int freq_max) {
  // Ініціалізація дисплея
  dis.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  dis.clearDisplay();

  // Знаходження максимального та мінімального значень RSSI
  int max_rssi = 0;
  int min_rssi = 1024;
  int freq_max_rssi;

  for (int x = 0; x < count_RSSIs; x++) {
    if (rssi_array[x] > max_rssi){
      max_rssi = rssi_array[x];
      freq_max_rssi = freqs[x];
    }
    if (rssi_array[x] < min_rssi) min_rssi = rssi_array[x];
  }

  // Малювання координатних осей
  dis.drawFastVLine(25, 2, 52, WHITE);
  dis.drawFastHLine(23, 50, 100, WHITE);

  // Встановлення розміру і кольору тексту
  dis.setTextSize(1);
  dis.setTextColor(WHITE);

  // Відображення максимального і мінімального значень RSSI
  dis.setCursor(0, 0);
  dis.print(max_rssi);

  dis.setCursor(0, 40);
  dis.print(min_rssi);

  // Відображення мінімальної і максимальної частот
  dis.setCursor(20, 55);
  dis.print(freq_min);

  dis.setCursor(94, 55);
  dis.print(freq_max);

  // Малювання ліній графіка
  draw_lines(rssi_array, min_rssi, max_rssi, freq_max_rssi);

  // Оновлення дисплея
  dis.display();
}
