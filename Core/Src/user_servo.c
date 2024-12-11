#include "user_servo.h"
extern TIM_HandleTypeDef htim3;


void servo_setangle(float angle)
{
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,angle/180*2000+500);
}








