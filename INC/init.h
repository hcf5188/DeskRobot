#ifndef __INIT_H__
#define __INIT_H__
extern void LEDInit(void);
extern void ClockInit(void);
extern void systemInit(void);
extern void globalVariableInit(void);

extern uint32_t Test_eeprom_int_data[8];
#endif

