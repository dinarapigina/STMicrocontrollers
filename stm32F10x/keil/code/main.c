#include "stm32f10x.h"                  // Device header

void tim4Begin()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4->PSC = 2400 - 1;
	TIM4->ARR = 1000;
	TIM4->DIER |= TIM_DIER_UIE; 
	TIM4->CR1  |=	TIM_CR1_CEN; 
	NVIC_EnableIRQ(TIM4_IRQn);	
}

int volatile coun=0;

void	TIM4_IRQHandler(void)
{
	
	TIM4->SR &=~TIM_SR_UIF; 
	
	GPIOC->ODR ^= GPIO_ODR_ODR8;
	coun++;
}

int main()
{
 

	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &=~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);	
	GPIOC->CRH |= GPIO_CRH_MODE8;
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL = 0x8;

	
	tim4Begin();
	
	while(1)
	{

	
				
	}
			
}