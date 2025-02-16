#include "matrix.h"
#include "config.h"

bool matrix_scan()
{
  bool flag = 0;
  for (int i = 0; i < M_COL; i++)
  {
    digitalWrite(M_col_p[i], HIGH);
    delayMicroseconds(10);
    for (int j = 0; j < M_ROW; j++)
    {
      SW[i][j] = digitalRead(M_row_p[j]);
      digitalRead(M_row_p[j]) ? flag = 1 : flag = flag;
    }
    digitalWrite(M_col_p[i], LOW);
  }
  for (int i = 0; i < E_COL; i++)
  {
    digitalWrite(E_col_p[i], HIGH);
    delayMicroseconds(10);
    for (int j = 0; j < E_ROW; j++)
    {
      SW[i + M_COL][j] = digitalRead(E_row_p[j]);
      digitalRead(E_row_p[j]) ? flag = 1 : flag = flag;
    }
    digitalWrite(E_col_p[i], LOW);
    delayMicroseconds(10);
  }
  return flag;
}

void matrix_disp()
{
  Serial.print("\n");
  for (int i = 0; i < M_ROW; i++)
  {
    Serial.print("\t\t\t\t\t");
    for (int j = 0; j < M_COL + E_COL; j++)
    {
      Serial.print(SW[j][i]);
      Serial.print("\t");
    }
    Serial.print("\n");
  }
}

void PIN_setup()
{
  for (int i = 0; i < M_ROW; i++)
  {
    pinMode(M_row_p[i], INPUT_PULLDOWN);
  }
  for (int i = 0; i < M_COL; i++)
  {
    pinMode(M_col_p[i], OUTPUT);
  }
  for (int i = 0; i < E_ROW; i++)
  {
    pinMode(E_row_p[i], INPUT_PULLDOWN);
  }
  for (int i = 0; i < E_COL; i++)
  {
    pinMode(E_col_p[i], OUTPUT);
  }
}