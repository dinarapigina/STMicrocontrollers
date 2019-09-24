#include "stm32f10x.h"   

void delayBegin(TIM_TypeDef * TIMx);
void delay(TIM_TypeDef * TIMx,uint32_t millisecond);
void delayMicroseconds(TIM_TypeDef * TIMx, uint32_t us);