#include "user_autogo.h"

#include "user_car.h"
#include "user_servo.h"
#include "sr04.h"

extern float distance;

void auto_go(void){
    car_goahead();
    sr04_start();
    if(distance < 15){auto_right();}
}

void auto_right(void){
    car_gostop();
    servo_setangle(0);//朝右边侦察
    RCCdelay_us(1000000);
    sr04_start();
    if(distance > 15)
    {
        servo_setangle(90);
        RCCdelay_us(1000000);
        self_right();
        RCCdelay_us(1000000);
        car_goahead();
        RCCdelay_us(500000);
    }else{auto_left();}
}

void auto_left(void){
    servo_setangle(180);
    RCCdelay_us(1000000);
    sr04_start();
    if(distance >15){
        servo_setangle(90);
        RCCdelay_us(1000000);
        self_left();
        RCCdelay_us(1000000);
        car_goahead();
        RCCdelay_us(500000);
    }else{
        servo_setangle(90);
        RCCdelay_us(1000000);
        find_way();
    }
}

uint8_t find_way(void){
    uint16_t software_tim = 0;
    while (distance<15)
    {
        software_tim = software_tim + 1;
        if (software_tim>120){
            while (distance<15){car_gostop();}
            return;
        }
        self_left();
        RCCdelay_us(500000);
        if (distance>15)
        {
            car_gostop();
            RCCdelay_us(500000);
        }
    }
    return;
}
