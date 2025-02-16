#include "HID_Reports.h"
#include <Adafruit_TinyUSB.h>
#include "Parrot_Descriptor.h"
#include "config.h"
#include "user_eeprom.h"
#include "KeyMode.h"
#include "HID_Reports.h"

uint8_t const desc_hid_report[] = {
    // TUD_HID_REPORT_DESC_GENERIC_INOUT(32,HID_REPORT_ID(RID_INOUT)),
    TUD_HID_REPORT_DESC_3DMOUSE(),                              // Descriptor for 3D mouse
    TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(RID_KEYBOARD))}; // Descriptor for keyboard
// USB HID object.
Adafruit_USBD_HID usb_hid;

void HID_setup()
{
  // Manual begin() is required on core without built-in support e.g. mbed rp2040
  if (!TinyUSBDevice.isInitialized())
  {
    TinyUSBDevice.begin(0);
  }

  // Set up HID
  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.setStringDescriptor("Parrot Device");
  usb_hid.setReportCallback(0, set_report_callback);

  usb_hid.begin();
}

void _3DReport_()
{
  if (x_only || x_only_hold)
  {
    report[1] = 0;
    report[2] = 0;
  }
  else if (y_only || y_only_hold)
  {
    report[0] = 0;
    report[2] = 0;
  }
  else if (z_only || z_only_hold)
  {
    report[0] = 0;
    report[1] = 0;
  }

  if (report[0] != 0 || report[1] != 0 || report[2] != 0)
  {
    if (mode)
    {
      report[0] = x_parallel_reverse[current_app] ? -report[0] : report[0];
      report[1] = y_parallel_reverse[current_app] ? -report[1] : report[1];
      report[2] = z_parallel_reverse[current_app] ? -report[2] : report[2];
      uint16_t comp = report[0];
      report[0] = report[2];
      report[2] = comp;
      usb_hid.sendReport(1, report, 6);
    }
    else
    {
      report[0] = x_reverse[current_app] ? -report[0] : report[0];
      report[1] = y_reverse[current_app] ? -report[1] : report[1];
      report[2] = z_reverse[current_app] ? -report[2] : report[2];
      usb_hid.sendReport(2, report, 6);
    }
    for (int i = 0; i < 3; i++)
    {
      Serial.print(report[i]);
      Serial.print("\t");
    }
    Serial.println("");
  }
}

void key_report()
{
  uint8_t pre_mod = 0;
  bool disable[M_COL + E_COL][M_ROW] = {false};
  for (int j = 0; j < M_COL + E_COL; j++)
  {
    for (int i = 0; i < M_ROW; i++)
    {
      if (SW[j][i])
      {
        pre_mod = app_layer[current_app][prev_layer][0][j * M_ROW + i];
        Serial.print(pre_mod);
        switch (pre_mod)
        {
        case LAYER1:
          if (prev_SW[j][i] == 0)
          {
            prev_layer = current_layer;
            current_layer = 0;
          }
          disable[j][i] = true;
          Serial.println("Disable");
          break;
        case LAYER2:
          if (prev_SW[j][i] == 0)
          {
            prev_layer = current_layer;
            current_layer = 1;
          }
          disable[j][i] = true;
          Serial.println("Disable");
          break;
        case LAYER3:
          if (prev_SW[j][i] == 0)
          {
            prev_layer = current_layer;
            current_layer = 2;
          }
          disable[j][i] = true;
          Serial.println("Disable");
          break;
        }
      }
    }
  }
  int k = 0;
  uint8_t mod = 0;
  uint8_t keycode[12] = {0};
  x_frag = false;
  y_frag = false;
  z_frag = false;
  for (int j = 0; j < M_COL + E_COL; j++)
  {
    for (int i = 0; i < M_ROW; i++)
    {
      mod = app_layer[current_app][current_layer][0][k];
      if (!disable[j][i])
      {
        switch (mod)
        {
        case SWITCH:
          if (prev_SW[j][i] == 0 && SW[j][i] == 1)
          {
            mode = !mode;
            pre_devmode = mode;
          }
          Serial.println(prev_SW[j][i]);
          break;
        case SWITCH_HOLD:
          if (prev_SW[j][i] == 0 && SW[j][i] == 1)
          {
            pre_devmode = mode;
            mode = !mode;
          }
          break;
        case X_ONLY:
          if (prev_SW[j][i] == 0 && SW[j][i] == 1)
          {
            if (y_only)
              y_only = false;
            if (z_only)
              z_only = false;
            x_only = !x_only;
          }
          break;
        case Y_ONLY:
          if (prev_SW[j][i] == 0 && SW[j][i] == 1)
          {
            if (x_only)
              x_only = false;
            if (z_only)
              z_only = false;
            y_only = !y_only;
          }
          break;
        case Z_ONLY:
          if (prev_SW[j][i] == 0 && SW[j][i] == 1)
          {
            if (x_only)
              x_only = false;
            if (y_only)
              y_only = false;
            z_only = !z_only;
          }
          break;
        case X_ONLY_HOLD:
          if (SW[j][i] == 1)
          {
            x_only_hold = true;
            x_frag = true;
          }
          break;
        case Y_ONLY_HOLD:
          if (SW[j][i] == 1)
          {
            y_only_hold = true;
            y_frag = true;
          }
          break;
        case Z_ONLY_HOLD:
          if (SW[j][i] == 1)
          {
            z_only_hold = true;
            z_frag = true;
          }
          break;
        case DPI:
          if (prev_SW[j][i] == 0 && SW[j][i] == 1)
          {
            dpi_set++;
            if (dpi_set > 2)
              dpi_set = 0;
          }
          break;
        case RAYER:
          if (prev_SW[j][i] == 0 && SW[j][i] == 1)
          {
            current_layer++;
            Serial.print("LAYERCHANGE");
            if (current_layer > 2)
              current_layer = 0;
            prev_layer = current_layer;
          }
          break;

        case APLICATION:
          if (prev_SW[j][i] == 0 && SW[j][i] == 1)
          {
            current_app++;
            Serial.print("APPCHANGE");
            if (current_app > 2)
              current_app = 0;
          }
          break;
        default:
          if (SW[j][i])
          {
            keycode[0] = app_layer[current_app][current_layer][1][k];
            usb_hid.keyboardReport(RID_KEYBOARD, mod, keycode);
            Serial.print("63 send key:");
            Serial.print(keycode[0]);
            Serial.print("\t CURRENT_APP:");
            Serial.print(current_app);
            Serial.print("\t CURRENT_LAYER:");
            Serial.println(current_layer);
          }
          else if (prev_SW[j][i] == 1 && SW[j][i] == 0)
          {
            keycode[0] = 0;
            usb_hid.keyboardReport(RID_KEYBOARD, mod, keycode);
          }
        }
      }
      k++;
    }
  }
  // pre_mode=mode;
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

void set_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const *in_data, uint16_t bufsize)
{
  if (bufsize != 63)
  {
    Serial.println("Not Valid Data");
    Serial.print("Get data size is:");
    Serial.println(bufsize);
    for (int i = 0; i < bufsize; i++)
    {
      Serial.print(in_data[i]);
      Serial.print("\t");
    }
    Serial.println(" ");
    return;
  }
  if (bufsize == 63)
  {
    switch (in_data[0])
    {
    case 0x03:
    {
      int set_app = in_data[1];
      x_reverse[set_app] = in_data[2];
      y_reverse[set_app] = in_data[3];
      z_reverse[set_app] = in_data[4];
      x_parallel_reverse[set_app] = in_data[5];
      y_parallel_reverse[set_app] = in_data[6];
      z_parallel_reverse[set_app] = in_data[7];
      dpi_pre[set_app][0] = in_data[9] + in_data[8] * 256;
      dpi_pre[set_app][1] = in_data[11] + in_data[10] * 256;
      dpi_pre[set_app][2] = in_data[13] + in_data[12] * 256;
      isLED[set_app] = in_data[14];
      eeprom_datawrite(in_data, bufsize, set_app, 0, 0, 1);
      break;
    }
    case 0x04:
    {
      int set_app = in_data[1];
      app_name[set_app] = "";
      for (int i = 2; i < bufsize; i++)
      {
        if (in_data[i] == 0)
          break;
        char c = in_data[i];
        app_name[set_app] += c;
      }
      eeprom_datawrite(in_data, bufsize, set_app, 0, 0, 0);
      Serial.println(app_name[set_app]);
      break;
    }

    case 0x05:
    {
      int set_app = in_data[1];
      int set_layer = in_data[2];
      for (int i = 0; i < 15; i++)
      {
        app_layer[set_app][set_layer][0][i] = in_data[2 * i + 3];
        app_layer[set_app][set_layer][1][i] = in_data[2 * i + 4];
        Serial.print(in_data[2 * i + 3]);
        Serial.print("\t");
        Serial.print(in_data[2 * i + 4]);
        Serial.print("\t");
      }
      app_layer[set_app][set_layer][0][2] = in_data[3];
      app_layer[set_app][set_layer][1][2] = in_data[4];
      app_layer[set_app][set_layer][0][1] = in_data[5];
      app_layer[set_app][set_layer][1][1] = in_data[6];
      app_layer[set_app][set_layer][0][0] = in_data[7];
      app_layer[set_app][set_layer][1][0] = in_data[8];
      eeprom_datawrite(in_data, bufsize, set_app, set_layer, 1, 0);
      Serial.println("");
      Serial.print("app:");
      Serial.print(set_app);
      Serial.print("\t layer:");
      Serial.println(set_layer);
      break;
    }
    default:
      Serial.println("first is incrrect");
      break;
    }
  }
}
