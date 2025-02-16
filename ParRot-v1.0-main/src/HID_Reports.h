#ifndef HID_REPORTS_H
#define HID_REPORTS_H

#include <Adafruit_TinyUSB.h>

void HID_setup();
void _3DReport_();
void key_report();
void set_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const *in_data, uint16_t bufsize);
#endif