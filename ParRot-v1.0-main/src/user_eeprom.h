#ifndef USER_EEPROM_H
#define USER_EEPROM_H

void eeprom_dataread(int size, int total_app, int total_layer, int if_have_name, int if_have_config);
void eeprom_datawrite(uint8_t const *in_data, int bufsize, int set_app, int set_layer, int ifkey,int ifconfig);

#endif