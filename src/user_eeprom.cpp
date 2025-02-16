
#include <EEPROM.h>
#include "config.h"

void eeprom_datawrite(uint8_t const *data, int size, int app, int layer, int ifkey, int ifconfig)
{
  Serial.print(size * (4 * app + ifkey * (layer + 1)+(12+app)*ifconfig));
  for (int i = 0; i < size; i++)
  {
    EEPROM.write(size * (4 * app + ifkey * (layer + 1))+(12+app)*ifconfig + i, data[i]);
    //Serial.print(data[i]);
    //Serial.printa("\t");
  }
  if (EEPROM.commit())
  {
    Serial.println("EEPROM successfully committed");
    OLED_state = 'w';
  }
  else
  {
    Serial.println("ERROR! EEPROM commit failed");
  }
}

void eeprom_dataread(int size, int total_app, int total_layer, int if_have_name, int if_have_config)
{
  uint8_t data[total_app][total_layer + if_have_name+if_have_config][size] = {0};
  for (int i = 0; i < total_app; i++)
  {
    for (int j = 0; j < total_layer + if_have_name+if_have_config; j++)
    {
      Serial.print("APP:");
      Serial.print(i);
      Serial.print("\t LAYER:");
      Serial.print(j);
      Serial.print("\t");
      for (int k = 0; k < size; k++)
      {
        data[i][j][k] = EEPROM.read(size * ((total_layer + if_have_name+if_have_config) * i + j) + k);
        Serial.print(data[i][j][k]);
        Serial.print("\t");
      }
      Serial.println("");
    }
    // Serial.println("====================================");
  }

  for (int i = 0; i < total_app; i++)
  {
    for (int j = 0; j < total_layer + if_have_name+if_have_config; j++)
    {
      if(data[i][j][0]==0x03){
        int set_app = data[i][j][1];
        x_reverse[set_app] = data[i][j][2];
        y_reverse[set_app] = data[i][j][3];
        z_reverse[set_app] = data[i][j][4];
        x_parallel_reverse[set_app] = data[i][j][5];
        y_parallel_reverse[set_app] = data[i][j][6];
        z_parallel_reverse[set_app] = data[i][j][7];
        dpi_pre[set_app][0] = data[i][j][9] + data[i][j][8] * 256;
        dpi_pre[set_app][1] = data[i][j][11] + data[i][j][10] * 256;
        dpi_pre[set_app][2] = data[i][j][13] + data[i][j][12] * 256;
        isLED[set_app] = data[i][j][14];
      }
      else if (data[i][j][0] == 0x04)
      {
        int set_app = data[i][j][1];
        app_name[set_app] = "";
        for (int k = 2; k < size; k++)
        {
          char c = data[i][j][k];
          app_name[set_app] += c;
        }
        Serial.println(app_name[set_app]);
      }
      else if (data[i][j][0] == 0x05)
      {
        int set_app = data[i][j][1];
        int set_layer = data[i][j][2];
        Serial.println("");
        Serial.print("app:");
        Serial.print(set_app);
        Serial.print("\t layer:");
        Serial.print(set_layer);
        Serial.print("\t");
        for (int k = 0; k < 15; k++)
        {
          app_layer[set_app][set_layer][0][k] = data[i][j][2 * k + 3];
          app_layer[set_app][set_layer][1][k] = data[i][j][2 * k + 4];
          Serial.print(app_layer[set_app][set_layer][0][k]);
          Serial.print("\t");
          Serial.print(app_layer[set_app][set_layer][1][k]);
          Serial.print("\t");
        }
        app_layer[set_app][set_layer][0][2] = data[i][j][3];
        app_layer[set_app][set_layer][1][2] = data[i][j][4];
        app_layer[set_app][set_layer][0][1] = data[i][j][5];
        app_layer[set_app][set_layer][1][1] = data[i][j][6];
        app_layer[set_app][set_layer][0][0] = data[i][j][7];
        app_layer[set_app][set_layer][1][0] = data[i][j][8];
        Serial.println("");
      }
      else
      {
        Serial.println("first is incrrect");
      }
    }
  }
}