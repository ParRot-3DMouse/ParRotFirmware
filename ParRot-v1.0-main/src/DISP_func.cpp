#include "DISP_func.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include "config.h"
#include "RGB_func.h"

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define I2C_SDA 8
#define I2C_SCL 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_NeoPixel THUMB_LEDs(THUMB_LED_NUMBERS, THUMB_LED, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel SIDE_LEDs(SIDE_LED_NUMBERS, SIDE_LED, NEO_GRB + NEO_KHZ800);

uint32_t LED_color[3] = {THUMB_LEDs.Color(255, 0, 0), THUMB_LEDs.Color(0, 255, 0), THUMB_LEDs.Color(0, 0, 255)};

int Attenuation = 5; // LEDの明るさの一周期での減衰率

int display_time = 2000; // OLEDの表示時間
// 表示開始した時間
unsigned long last_display_time = 0;

// LEDのモードを管理する変数
char LED_state = 0;
/*
  LEDオフ: 0
  LEDの押したボタンが光る:1
  ゲーミング
  x軸固定: x
  y軸固定: y
  z軸固定: z

*/

// OLEDのモードを管理する変数
volatile char OLED_state = 0;
/*
  通常: 0
  書き込み成功: w
*/

// 一つ前のOLEDの状態を管理する変数
char previous_OLED_state = 0;

volatile bool isx_only = false;
volatile bool isy_only = false;
volatile bool isz_only = false;

void OLED_state_update()
{
  if (OLED_state != 0)
  {
    if (previous_OLED_state != OLED_state)
    {
      last_display_time = millis();
    }
  }
  if (millis() - last_display_time > display_time)
  {
    OLED_state = 0;
  }
  previous_OLED_state = OLED_state;
}
void OLED_update()
{
  /*
    テキストサイズについて
     テキストサイズにnを設定すると文字サイズは"8*n[pixel] x 8*n[pixel]"となる

    OLEDのサイズについて
      現在使用しているものは128x32ドットのOLEDである
  */
  OLED_state_update();
  switch (OLED_state)
  {
  case 'w':
    OLED_writed();
    break;
  default:
    OLED_default();
    break;
  }
}

void RGBLED_update()
{
  if (!isLED[current_app])
  {
    THUMB_LEDs.clear();
    SIDE_LEDs.clear();
    return;
  }

  LED_state_update();
  LED_HS_update();
  LED_val_update();

  THUMB_LEDs.clear();
  SIDE_LEDs.clear();

  for (int i = 0; i < THUMB_LED_NUMBERS; i++)
  {
    THUMB_LEDs.setPixelColor(i, hsv2rgb(THUMB_LED_hue[i], THUMB_LED_sat[i], THUMB_LED_val[i]));
  }
  for (int i = 0; i < SIDE_LED_NUMBERS; i++)
  {
    SIDE_LEDs.setPixelColor(i, hsv2rgb(SIDE_LED_hue[i], SIDE_LED_sat[i], SIDE_LED_val[i]));
  }
  last_LED_time = millis();

  THUMB_LEDs.show();
  SIDE_LEDs.show();
}

void displayLED_setup()
{
  Wire.setSDA(I2C_SDA);
  Wire.setSCL(I2C_SCL);
  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306:0 allocation failed"));
  }
  display.setTextColor(SSD1306_WHITE);
  display.setRotation(2);
  THUMB_LEDs.begin();
  SIDE_LEDs.begin();
}

// hue: 0-360, sat: 0-100, val: 0-100

void OLED_writed()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("Writed\n  successful");
  display.display();
}
void OLED_default()
{
  display.clearDisplay();

  display.setCursor(0, 0);
  display.setTextSize(2);               // 文字サイズ（1）
  display.print(app_name[current_app]); // 表示内容

  display.setCursor(8, 16); // 表示開始位置左上角（X,Y）
  display.setTextSize(1);
  display.print("LAYER");           // 表示内容
  display.print(current_layer + 1); // 表示内容

  display.setCursor(8, 24);
  display.setTextSize(1);
  display.print("DPI:");
  display.print(dpi_pre[current_app][dpi_set]);

  display.setCursor(64, 16);
  display.setTextSize(1);
  display.print("Lock:");
  isx_only ? display.print("X") : isy_only ? display.print("Y")
                              : isz_only   ? display.print("Z")
                                           : display.print("OFF");

  display.setCursor(64, 24);
  display.setTextSize(1);
  display.print("Mode:");
  mode ? display.print("T") : display.print("R");
  display.display(); // 表示実行
}