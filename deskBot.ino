#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Wire.begin(5, 4); // SDA=5, SCL=4

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 bulunamadi"));
    for (;;) ;
  }
  display.clearDisplay();
  display.display();
  delay(200);
}


void drawSquare(int x, int y, int size, bool filled) {
  if (filled) {
    display.fillRect(x, y, size, size, SSD1306_WHITE);
  } else {
    display.drawRect(x, y, size, size, SSD1306_WHITE);
  }
}

void loop() {
  display.clearDisplay();

  int size1 = 50;

  //Left Eyes
  int x1 = (SCREEN_WIDTH/2 - size1) / 2;
  int y1 = (SCREEN_HEIGHT - size1) / 2;
  drawSquare(x1, y1, size1, true);

  //Right Eyes
  int x2 = (SCREEN_WIDTH+60 - size1) / 2;
  int y2 = (SCREEN_HEIGHT - size1) / 2;
  drawSquare(x2, y2, size1, true);


  display.display();
  delay(2000); // 2 saniye bekle, sonra tekrar çiz (demo amaçlı)
}
