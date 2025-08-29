#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int viberPin = 4-2;

void setup() {
  pinMode(viberPin, INPUT);

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

void drawEye(int x, int y, int w, int h) {
  display.fillRect(x, y, w, h, SSD1306_WHITE);
}

void blinkEyes() {
  int sizeW = 40;   // Göz genişliği
  int sizeH = 40;   // Normal yükseklik

  int leftX = (SCREEN_WIDTH/2 - sizeW) / 2;
  int rightX = (SCREEN_WIDTH+60 - sizeW) / 2;
  int eyeY = (SCREEN_HEIGHT - sizeH) / 2;

  // Göz kapatma (yükseklik küçülüyor)
  for (int h = sizeH; h > 5; h -= 5) {
    display.clearDisplay();
    drawEye(leftX, eyeY, sizeW, h);
    drawEye(rightX, eyeY, sizeW, h);
    display.display();
    delay(10);
  }  

  delay(75); // Tam kapalı kalma süresi

  // Göz açma (yükseklik geri büyüyor)
  for (int h = 5; h <= sizeH; h += 5) {
    display.clearDisplay();
    drawEye(leftX, eyeY, sizeW, h);
    drawEye(rightX, eyeY, sizeW, h);
    display.display();
    delay(10);
  }
}

void loop() {
  int viberConteol = digitalRead(viberPin);
  Serial.println(viberConteol);
  if(viberConteol == 0){
    // Normal göz açık
    display.clearDisplay();
    drawEye((SCREEN_WIDTH/2 - 50) / 2, (SCREEN_HEIGHT - 50) / 2, 50, 50);
    drawEye((SCREEN_WIDTH+60 - 50) / 2, (SCREEN_HEIGHT - 50) / 2, 50, 50);
    display.display();
  }
  else{
    blinkEyes();
  }
}
