/*
C-application to set the setpoint for the pwm driver; based on the example of Rene Moll 10/4/2012.
defined base for pwm: PWM_DRIVER_0_BASE
regnum? 0x00
to write is in form of? data: should be bits
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <io.h>
#include "system.h"

#DEFINE LEFT 0
#DEFINE RIGHT 1

int main(){
    int direction = LEFT;

    while(1){
    IOWR(PWM_DRIVER_0_BASE, 0x00, 0<<31 | (direction<<8 | 0x80));
    //IOWR(PWM_DRIVER_0_BASE, 0x00, 1); //direction to 1
    int encoder1val = IORD(ENCODER_IP_BUS_0_BASE, 0x00);
    printf("encoder value is: %u\n", encoder1val);
    sleep(1);
    }
}
