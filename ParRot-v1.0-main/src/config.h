#ifndef CONFIG_H
#define CONFIG_H

#include "Adafruit_TinyUSB.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <PMW3360.h>
#include <SPI.h>
#include <EEPROM.h>

#define M_COL 2
#define M_ROW 3

#define E_COL 2
#define E_ROW 3

enum
{
  RID_INOUT = 31,
  RID_KEYBOARD = 30,
};

extern uint8_t const desc_hid_report[]; // Descriptor for Parrot Device

extern Adafruit_USBD_HID usb_hid;

extern uint8_t app_layer[3][3][2][15];

extern unsigned int dpi_pre[3][3];
extern volatile int dpi_set;
extern volatile int prev_dpi;

extern Adafruit_SSD1306 display;
extern int current_layer;
extern int prev_layer;
extern int current_app;
extern String app_name[];

extern const int M_row_p[];
extern const int M_col_p[];
extern volatile int SW[M_COL + E_COL][M_ROW]; // スイッチの状態を保持
extern int prev_SW[M_COL + E_COL][M_ROW];

extern const int E_row_p[];
extern const int E_col_p[];

extern volatile bool x_only;
extern volatile bool y_only;
extern volatile bool z_only;
extern volatile bool x_only_hold;
extern volatile bool y_only_hold;
extern volatile bool z_only_hold;

extern bool x_frag;
extern bool y_frag;
extern bool z_frag;

extern volatile bool isx_only;
extern volatile bool isy_only;
extern volatile bool isz_only;

extern bool x_reverse[];
extern bool y_reverse[];
extern bool z_reverse[];
extern bool x_parallel_reverse[];
extern bool y_parallel_reverse[];
extern bool z_parallel_reverse[];

extern volatile bool mode;
extern bool pre_devmode;

extern volatile char OLED_state;

#define THUMB_LED 10
#define THUMB_LED_NUMBERS 2
#define SIDE_LED 24
#define SIDE_LED_NUMBERS 3

extern Adafruit_NeoPixel THUMB_LEDs;
extern Adafruit_NeoPixel SIDE_LEDs;

extern int THUMB_LED_hue[];
extern int THUMB_LED_hue_Obj[];
extern int THUMB_LED_sat[];
extern int THUMB_LED_sat_Obj[];
extern int THUMB_LED_val[];
extern int THUMB_LED_val_Obj[];

extern int SIDE_LED_hue[];
extern int SIDE_LED_hue_Obj[];
extern int SIDE_LED_sat[];
extern int SIDE_LED_sat_Obj[];
extern int SIDE_LED_val[];
extern int SIDE_LED_val_Obj[];

extern int hue_diff;
extern int sat_diff;
extern int val_diff;

extern unsigned long last_LED_time;

extern char LED_state;
extern volatile char OLED_state;


extern uint32_t LED_color[];

extern bool isLED[];

extern uint16_t report[3];

extern PMW3360 sensor1;
extern PMW3360 sensor2;

#endif