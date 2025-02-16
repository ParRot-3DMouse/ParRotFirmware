/*
このプログラムは、オープンソースハードウェア「Parrot」のファームウェアです。
Parrotは、MITOUプロジェクトの一環として開発された、3Dマウスとしての機能を持つマウスです。
ファームウェアの詳細については、以下のURLを参照してください。

ファームウェアの実行時には、以下のライブラリが必要です。
- Adafruit_TinyUSB
- PMW3360
- SSD1306
- Adafruit_NeoPixel
- Adafruit_GFX
使用時にはこのプログラムをArduino IDEでビルドし、Parrotに書き込んでください。
*/


#include "Adafruit_TinyUSB.h"
#include <PMW3360.h>
#include <SPI.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include "src\config.h"
#include "src\Parrot_Descriptor.h"
#include "src\user_eeprom.h"
#include "src\Sensers.h"
#include "src\matrix.h"
#include "src\KeyMode.h"
#include "src\HID_Reports.h"
#include "src\DISP_func.h"

volatile bool x_only = false; // X軸固定(trueで固定)
volatile bool y_only = false; // Y軸固定(trueで固定)
volatile bool z_only = false; // Z軸固定(trueで固定)
volatile bool x_only_hold = false; // X軸固定(trueで固定)
volatile bool y_only_hold = false; // Y軸固定(trueで固定)
volatile bool z_only_hold = false; // Z軸固定(trueで固定)
bool x_frag = false;
bool y_frag = false;
bool z_frag = false;

bool x_reverse[3] = {false, false, false};
bool y_reverse[3] = {false, false, false};
bool z_reverse[3] = {false, false, false};
bool x_parallel_reverse[3] = {false, false, false};
bool y_parallel_reverse[3] = {false, false, false};
bool z_parallel_reverse[3] = {false, false, false};

#define SS1 5 // Slave Select pin. Connect this to SS on the module.
#define SS2 6
const int MISO_PIN = 4;
const int SCK_PIN = 2;
const int MOSI_PIN = 3;

#define I2C_SDA 8
#define I2C_SCL 9

PMW3360 sensor1;
PMW3360 sensor2;

unsigned int dpi_pre[3][3] = {{400,800,1600},{400,800,1600},{400,800,1600}};
volatile int dpi_set = 1; // DPIの設定(0:0.5倍, 1:1倍, 2:2倍)
volatile int prev_dpi = 1;

uint8_t app_layer[3][3][2][15] = {0};

int current_layer = 0;
int prev_layer = 0;
int current_app = 0;
String app_name[3] = {"", "", ""};

const int M_row_p[] = {27, 26, 25};
const int M_col_p[] = {21, 28};
volatile int SW[M_COL + E_COL][M_ROW]; // スイッチの状態を保持
int prev_SW[M_COL + E_COL][M_ROW];

const int E_row_p[] = {17, 18, 19};
const int E_col_p[] = {12, 11};

#define KEY_INTERBAL 50
unsigned long Key_Time=0;

volatile bool mode = false;
bool pre_devmode=false;
uint16_t report[3] = {0, 0, 0};

bool isLED[3] = {true, true ,true};

// the setup function runs once when you press reset or power the board
void setup()
{
  HID_setup();
  SPI_setup();
  PIN_setup();
  EEPROM.begin(1024);
  Serial.begin(115200);
  senser_setup();
  Serial.println("Parrot Device NOW ON BEGING");
  eeprom_dataread(63, 3, 3, 1,1);
  //Key_Time=millis();
}

void loop()
{
#ifdef TINYUSB_NEED_POLLING_TASK
  // Manual call tud_task since it isn't called by Core's background
  TinyUSBDevice.task();
#endif
  pmw_main();
    if (matrix_scan())
    {
      matrix_disp();
      key_report();
    }
    else
    {
      usb_hid.keyboardRelease(RID_KEYBOARD);
      mode=pre_devmode;
      current_layer=prev_layer;
      x_frag = false;
      y_frag = false;
      z_frag = false;
      isx_only = x_frag;
      isy_only = y_frag;
      isz_only = z_frag;
      if (x_only == true)
      {
        isx_only = true;
      }
      if (y_only == true)
      {
        isy_only = true;
      }
      if (z_only == true)
      {
        isz_only = true;
      }
    }
    //Key_Time = millis();
  delay(5);
  if (!TinyUSBDevice.mounted())
  {
    return;
  }
  DPI_change();
  _3DReport_();
  delay(10);
  prev_SW_init();
}

void setup1()
{
  Wire.setSDA(I2C_SDA);
  Wire.setSCL(I2C_SCL);
  Wire.begin();
  displayLED_setup();
}

void loop1()
{
  OLED_update();
  RGBLED_update();
  delay(20);
}


void prev_SW_init()
{
  for (int i = 0; i < M_COL+E_COL; i++)
  {
    for (int j = 0; j < M_ROW; j++)
    {
      prev_SW[i][j] = SW[i][j];
    }
  }
  x_only_hold=false;
  y_only_hold=false;
  z_only_hold=false;
}
