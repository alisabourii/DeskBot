#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Göz parametreleri
int eyeRadius = 10;
int pupilRadius = 4;
int leftEyeX = 40;
int rightEyeX = 88;
int eyeY = 25;  // Gözleri biraz yukarı aldık, dudak için yer kalsın

// Dudak parametreleri
int mouthX = 64;  // Ortada
int mouthY = 50;  // Gözlerin altında
int mouthWidth = 20;
int mouthHeight = 5;

void setup() {
  Serial.begin(115200);
  Wire.begin(5, 4);  // SDA=5, SCL=4

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 bulunamadi, baglantilari kontrol et!"));
    for(;;);
  }

  display.clearDisplay();
  display.display();
  randomSeed(analogRead(0));
}

void loop() {
 
  goz_hareketleri();

  uzgun_dudak();

  display.display();
  delay(random(500, 1500));
}

void goz_hareketleri(){
   int offsetX = random(-4, 5);
  int offsetY = random(-3, 4);

  display.clearDisplay();

  // Sol göz
  display.drawCircle(leftEyeX, eyeY, eyeRadius, SSD1306_WHITE);
  display.fillCircle(leftEyeX + offsetX, eyeY + offsetY, pupilRadius, SSD1306_WHITE);

  // Sağ göz
  display.drawCircle(rightEyeX, eyeY, eyeRadius, SSD1306_WHITE);
  display.fillCircle(rightEyeX + offsetX, eyeY + offsetY, pupilRadius, SSD1306_WHITE);
}

void uzgun_dudak(){
  // Dudak (basit yay/arc şeklinde gülümseme)
  for (int i = -mouthWidth/2; i <= mouthWidth/2; i++) {
    int y = mouthY + (i*i) / (mouthWidth/2) - mouthHeight; 
    display.drawPixel(mouthX + i, y, SSD1306_WHITE);
  }
}
