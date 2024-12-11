#include "sr04.h"
extern TIM_HandleTypeDef htim1;
uint16_t count;
float distance;


void RCCdelay_us(uint32_t udelay)
{
  __IO uint32_t Delay = udelay * 72 / 8;
  do
  {
    __NOP();
  }
  while (Delay --);
}

void sr04_start(void){
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
    //gpio pin 12 output 触发信号
    RCCdelay_us(12);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    //中断回调函数
    //GPIO12触发，GOIO13回响
    if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)==GPIO_PIN_SET)
    {
        __HAL_TIM_SetCounter(&htim1,0);
            //开始计时前先把计数器清零
        HAL_TIM_Base_Start(&htim1);
            //打开定时器的时钟让它开始计时
    }
    else
    {
        HAL_TIM_Base_Stop(&htim1);
            //如果读到的是下降沿低电平则停止计时
        count = __HAL_TIM_GET_COUNTER(&htim1);
        distance = (count*1.0/10*0.34)/2;
        //这里修改的是全局变量
        //SR04触发后定时器会自动进入这个回响中断
    }
}

