#include "user_motor.h"

extern TIM_HandleTypeDef htim2;

void motor_setleftspeed(uint8_t speed)
{
    if (speed > 0)
    {   
        //正转
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
        __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,speed);
    }
    else if (speed == 0)
    {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
        __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,speed);
    }
    else{
        //反转
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
        __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3, -speed );
    }
}

void motor_setrightspeed(uint8_t speed)
{
    if (speed > 0)
    {   
        //由于电机为对称安装,此电机为逆时针故取负值
    
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
        __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,-speed);
    }
    else if (speed == 0)
    {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
        __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,speed);
    }
    else{
        //反转
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
        __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,-speed );
    }
}
 

