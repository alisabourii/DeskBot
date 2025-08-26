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
 
  eyelashs();

  drawMouth(2, 64, 50, 20, 5);  // mode=1 → gülümseme


  display.display();
  delay(random(500, 1500));
}

void eyelashs(){
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

void sad_lips(){
  for (int i = -mouthWidth/2; i <= mouthWidth/2; i++) {
    int y = mouthY + (i*i) / (mouthWidth/2) - mouthHeight; 
    display.drawPixel(mouthX + i, y, SSD1306_WHITE);
  }
}

void drawMouth(int mode, int mouthX, int mouthY, int mouthWidth, int mouthHeight) {
  switch(mode) {
    case 0: // Normal (düz çizgi)
      display.drawLine(mouthX - mouthWidth/2, mouthY, 
                       mouthX + mouthWidth/2, mouthY, SSD1306_WHITE);
      break;

    case 1: // Mutlu (gülümseme)
      for (int i = -mouthWidth/2; i <= mouthWidth/2; i++) {
        int y = mouthY + (i*i) / (mouthWidth/4) - mouthHeight; 
        display.drawPixel(mouthX + i, y, SSD1306_WHITE);
      }
      break;

    case 2: // Üzgün (somurtma)
      for (int i = -mouthWidth/2; i <= mouthWidth/2; i++) {
        int y = mouthY - (i*i) / (mouthWidth/4) + mouthHeight; 
        display.drawPixel(mouthX + i, y, SSD1306_WHITE);
      }
      break;

    case 3: // Şaşkın (açık ağız)
      display.drawCircle(mouthX, mouthY, mouthWidth/4, SSD1306_WHITE);
      break;

    case 4: // Kahkaha (yarım yay gibi)
      for (int i = -mouthWidth/2; i <= mouthWidth/2; i++) {
        int y = mouthY + (i*i) / (mouthWidth/4); 
        display.drawPixel(mouthX + i, y, SSD1306_WHITE);
      }
      break;
  }
}
