#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 dis(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void draw_lines(int rssi_array[], int min_rssi, int max_rssi) {
  for (int x = 0; x < count_RSSIs; x++) {
    dis.writeLine(28 + (x * 3), 48, 
                  28 + (x * 3), 48 - map(rssi_array[x], min_rssi - 2, max_rssi + 2, 5, 45), 
                  WHITE);
  }
}

void draw_graph(int rssi_array[], int freq_min, int freq_max) {
  dis.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  dis.clearDisplay();
  int max_rssi = 0;
  int min_rssi = 1024;

  for (int x = 0; x < count_RSSIs; x++) {
    if (rssi_array[x] > max_rssi) max_rssi = rssi_array[x];
    if (rssi_array[x] < min_rssi) min_rssi = rssi_array[x];
  }

  // draw coordinate area
  dis.drawFastVLine(25, 2, 52, WHITE);
  dis.drawFastHLine(23, 50, 100, WHITE);

  dis.setTextSize(1);
  dis.setTextColor(WHITE);

  dis.setCursor(0, 0);
  dis.print(max_rssi);

  dis.setCursor(0, 40);
  dis.print(min_rssi);

  dis.setCursor(20, 55);
  dis.print(freq_min);

  dis.setCursor(94, 55);
  dis.print(freq_max);

  draw_lines(rssi_array, min_rssi, max_rssi);

  dis.display();
}