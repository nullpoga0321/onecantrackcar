#include "user_car.h"
#include "user_motor.h"

uint8_t selfdefine_speed;

void set_all_speed(uint8_t i_want_speed){
    selfdefine_speed = 0;
    selfdefine_speed = i_want_speed;
}

void car_goahead(){
    motor_setleftspeed(selfdefine_speed);
    motor_setrightspeed(selfdefine_speed);
}

void car_goback(){
    motor_setleftspeed(-selfdefine_speed);
    motor_setrightspeed(-selfdefine_speed);
}

void car_goleft(){
    motor_setleftspeed(0);
    motor_setrightspeed(selfdefine_speed);
}

void car_goright(){
    motor_setleftspeed(selfdefine_speed);
    motor_setrightspeed(0);
}

void self_left(){
    motor_setleftspeed(-selfdefine_speed);
    motor_setrightspeed(selfdefine_speed);
}

void self_right(){
    motor_setleftspeed(selfdefine_speed);
    motor_setrightspeed(-selfdefine_speed);
}

void car_gostop(){
    motor_setleftspeed(0);
    motor_setrightspeed(0);
}
