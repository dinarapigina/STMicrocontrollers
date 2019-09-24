#include "stm32f10x.h"    

void tim2Begin(void);
void gpioBegin(void);
void tb6612fngBegin(void);
void beginEncoderTim1(void);
void beginEncoderTim3(void);
void stop();
void forwards(uint8_t left, uint8_t right);
void backward(uint8_t left, uint8_t right);
float encoderRead(void);
void motor(int pwm);
