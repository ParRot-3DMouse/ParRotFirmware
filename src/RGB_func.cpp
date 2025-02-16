#include "config.h"
#include "RGB_func.h"
#include "disp_func.h"

int THUMB_LED_hue[THUMB_LED_NUMBERS] = {0, 180};
int THUMB_LED_sat[THUMB_LED_NUMBERS] = {0};
int THUMB_LED_val[THUMB_LED_NUMBERS] = {0};

int SIDE_LED_hue[SIDE_LED_NUMBERS] = {0, 120, 240};
int SIDE_LED_sat[SIDE_LED_NUMBERS] = {0};
int SIDE_LED_val[SIDE_LED_NUMBERS] = {0};

int hue_diff = 1;
int sat_diff = 10;
int val_diff = 10;

unsigned long led_cycle = 5000;

const uint16_t RED = 0;
const uint16_t GREEN = 120;
const uint16_t BLUE = 240;

unsigned long last_LED_time = 0;

void LED_state_update()
{
    LED_state = 1;

    isz_only ? LED_state = 'z' : LED_state = LED_state;
    isy_only ? LED_state = 'y' : LED_state = LED_state;
    isx_only ? LED_state = 'x' : LED_state = LED_state;
}
void LED_HS_update()
{
    switch (LED_state)
    {
    case 'x':
        for (int i = 0; i < THUMB_LED_NUMBERS; i++)
        {
            THUMB_LED_hue[i] = RED;
            THUMB_LED_sat[i] = 100;
        }
        for (int i = 0; i < SIDE_LED_NUMBERS; i++)
        {
            SIDE_LED_hue[i] = RED;
            SIDE_LED_sat[i] = 100;
        }
        break;
    case 'y':
        for (int i = 0; i < THUMB_LED_NUMBERS; i++)
        {
            THUMB_LED_hue[i] = GREEN;
            THUMB_LED_sat[i] = 100;
        }
        for (int i = 0; i < SIDE_LED_NUMBERS; i++)
        {
            SIDE_LED_hue[i] = GREEN;
            SIDE_LED_sat[i] = 100;
        }
        break;
    case 'z':
        for (int i = 0; i < THUMB_LED_NUMBERS; i++)
        {
            THUMB_LED_hue[i] = BLUE;
            THUMB_LED_sat[i] = 100;
        }
        for (int i = 0; i < SIDE_LED_NUMBERS; i++)
        {
            SIDE_LED_hue[i] = BLUE;
            SIDE_LED_sat[i] = 100;
        }
        break;
    default:
        for (int i = 0; i < THUMB_LED_NUMBERS; i++)
        {
            THUMB_LED_hue[i] = (THUMB_LED_hue[i] + 360 * (millis() - last_LED_time) / led_cycle) % 360;
            THUMB_LED_sat[i] = 100;
        }
        for (int i = 0; i < SIDE_LED_NUMBERS; i++)
        {
            SIDE_LED_hue[i] = (SIDE_LED_hue[i] + 360 * (millis() - last_LED_time) / led_cycle) % 360;
            SIDE_LED_sat[i] = 100;
        }
        break;
    }
}

void LED_val_update()
{
    switch (LED_state)
    {
    case 'x':
    case 'y':
    case 'z':
    case 2:
        for (int i = 0; i < THUMB_LED_NUMBERS; i++)
        {
            THUMB_LED_val[i] = 100;
        }
        for (int i = 0; i < SIDE_LED_NUMBERS; i++)
        {
            SIDE_LED_val[i] = 100;
        }
        break;
    case 1:
        for (int i = 0; i < THUMB_LED_NUMBERS; i++)
        {
            SW[0][i + 1] == 1 ? THUMB_LED_val[i] = 100 : THUMB_LED_val[i] > 0 ? THUMB_LED_val[i] -= val_diff
                                                                              : THUMB_LED_val[i] = 0;
            THUMB_LED_val[i] = constrain(THUMB_LED_val[i], 0, 100);
        }
        for (int i = 0; i < SIDE_LED_NUMBERS; i++)
        {
            SW[1][i] == 1 ? SIDE_LED_val[i] = 100 : SIDE_LED_val[i] > 0 ? SIDE_LED_val[i] -= val_diff
                                                                        : SIDE_LED_val[i] = 0;
            SIDE_LED_val[i] = constrain(SIDE_LED_val[i], 0, 100);
        }
        break;
    }
}

uint32_t hsv2rgb(uint16_t hue, uint8_t sat, uint8_t val)
{
    uint8_t r, g, b;
    uint8_t region, remainder, p, q, t;

    // Limit hue to the range 0-360
    if (hue > 360)
    {
        hue = 360;
    }

    // Limit sat and val to the range 0-100
    if (sat > 100)
    {
        sat = 100;
    }
    if (val > 100)
    {
        val = 100;
    }

    // Convert sat and val from 0-100 to 0-255
    sat = (sat * 255) / 100;
    val = (val * 255) / 100;

    if (sat == 0)
    {
        r = val;
        g = val;
        b = val;
        return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
    }

    region = hue / 60;
    remainder = (hue - (region * 60)) * 6;

    p = (val * (255 - sat)) >> 8;
    q = (val * (255 - ((sat * remainder) >> 8))) >> 8;
    t = (val * (255 - ((sat * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
    case 0:
        r = val;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = val;
        b = p;
        break;
    case 2:
        r = p;
        g = val;
        b = t;
        break;
    case 3:
        r = p;
        g = q;
        b = val;
        break;
    case 4:
        r = t;
        g = p;
        b = val;
        break;
    default:
        r = val;
        g = p;
        b = q;
        break;
    }

    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}