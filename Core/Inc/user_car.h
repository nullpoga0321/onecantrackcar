#ifndef __USER_CAR_H__
#define __USER_CAR_H__

#include "stm32f1xx_hal.h"

void set_all_speed(uint8_t i_want_speed);
void car_goahead(void);
void car_goback(void);
void car_goleft(void);
void car_goright(void);
void self_left(void);
void self_right(void);
void car_gostop(void);

#endif
