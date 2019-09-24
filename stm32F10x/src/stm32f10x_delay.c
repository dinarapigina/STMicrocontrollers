#include "stm32f10x_delay.h"

void delayBegin(TIM_TypeDef * TIMx)
{
		switch ((uint32_t) TIMx) 
		{
#if defined(RCC_APB2ENR_TIM1EN)
			case (uint32_t) TIM1: RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; break;
#endif
#if defined(RCC_APB1ENR_TIM2EN)
			case (uint32_t) TIM2: RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; break;
#endif
#if defined(RCC_APB1ENR_TIM3EN)
			case (uint32_t) TIM3: RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; break;
#endif
#if defined(RCC_APB1ENR_TIM4EN)
			case (uint32_t) TIM4: RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; break;
#endif
#if defined(RCC_APB1ENR_TIM5EN)
			case (uint32_t) TIM5: RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; break;
#endif
#if defined(RCC_APB1ENR_TIM6EN)
			case (uint32_t) TIM6: RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; break;
#endif
#if defined(RCC_APB1ENR_TIM7EN)
			case (uint32_t) TIM7: RCC->APB1ENR |= RCC_APB1ENR_TIM7EN; break;
#endif
#if defined(RCC_APB2ENR_TIM8EN)
			case (uint32_t) TIM8: RCC->APB2ENR |= RCC_APB2ENR_TIM8EN; break;
#endif
#if defined(RCC_APB2ENR_TIM9EN)
			case (uint32_t) TIM9: RCC->APB2ENR |= RCC_APB2ENR_TIM9EN; break;
#endif	
		}
		
		TIMx->PSC     = 24 - 1;              
		TIMx->CR1     = TIM_CR1_OPM;          
}

void delay(TIM_TypeDef * TIMx,uint32_t millisecond)
{
		if (millisecond >= 100){TIMx->PSC = 24000 - 1;}
		else{TIMx->PSC = 240 - 1; millisecond *= 100;}
		TIMx->ARR = millisecond;                  
		TIMx->CNT = 0;
		TIMx->CR1 = TIM_CR1_CEN;	      
		while((TIMx->SR & TIM_SR_UIF)==0){} 
		TIMx->SR &= ~TIM_SR_UIF;	      
}

void delayMicroseconds(TIM_TypeDef * TIMx, uint32_t us)
{
		if (us >= 10000){TIMx->PSC = 24000 - 1; us /= 1000;}
		else{TIMx->PSC = 24 - 1;}
		TIMx->ARR = us;                  
		TIMx->CNT = 0;
		TIMx->CR1 = TIM_CR1_CEN;	      
		while((TIMx->SR & TIM_SR_UIF)==0){} 
		TIMx->SR &= ~TIM_SR_UIF;	
}
