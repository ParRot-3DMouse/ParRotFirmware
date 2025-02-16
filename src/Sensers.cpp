#include <PMW3360.h>
#include "config.h"
#include "Sensers.h"

#define SS1 5 // Slave Select pin. Connect this to SS on the module.
#define SS2 6
const int MISO_PIN = 4;
const int SCK_PIN = 2;
const int MOSI_PIN = 3;

void pmw_main()
{
  PMW3360_DATA data1 = sensor1.readBurst();
  PMW3360_DATA data2 = sensor2.readBurst();
  report[0] = slide(-data2.dx);
  report[2] = slide(data2.dy);
  report[1] = slide(-data1.dx);
}

int slide(int in)
{
  return in >= 32767 ? in - 65535 : in;
}

void SPI_setup()
{
  SPI.setRX(MISO_PIN);
  SPI.setTX(MOSI_PIN);
  SPI.setSCK(SCK_PIN);
}

void senser_setup()
{
  if (sensor1.begin(SS1)) // 10 is the pin connected to SS of the module.
    Serial.println("Sensor1 initialization successed");
  else
    Serial.println("Sensor1 initialization failed");
  delay(100);
  if (sensor2.begin(SS2)) // 10 is the pin connected to SS of the module.
    Serial.println("Sensor2 initialization successed");
  else
    Serial.println("Sensor2 initialization failed");
}

void DPI_change()
{
  if(dpi_set != prev_dpi){
    sensor1.setCPI(dpi_pre[current_app][dpi_set]);
    sensor2.setCPI(dpi_pre[current_app][dpi_set]);
    Serial.print("DPI Change");
    prev_dpi = dpi_set;
  }
}