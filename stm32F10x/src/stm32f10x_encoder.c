#include "stm32f10x.h"

void beginEncoderTim1(void) 
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;							
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;							
	GPIOA->CRH &= ~(GPIO_CRH_CNF8_0 | GPIO_CRH_CNF9_0);			
	GPIOA->CRH |= GPIO_CRH_CNF8_1 | GPIO_CRH_CNF9_1;

	GPIOA->BSRR = GPIO_BSRR_BR8;
	GPIOA->BSRR = GPIO_BSRR_BR9;	

	TIM1->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;		
	TIM1->CCER  &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P); 			
	TIM1->SMCR  |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;				
	TIM1->ARR = 65535;											
	TIM1->CR1 |= TIM_CR1_CEN; 								
	TIM1->CNT = 0;
}

void beginEncoderTim3(void) 
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;						
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;							
	GPIOA->CRL &= ~(GPIO_CRL_CNF6_0 | GPIO_CRL_CNF7_0);		
	GPIOA->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_CNF7_1;

	GPIOA->BSRR = GPIO_BSRR_BR6;
	GPIOA->BSRR = GPIO_BSRR_BR7;

	TIM3->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;		
	TIM3->CCER  &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P); 			
	TIM3->SMCR  |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;				
	TIM3->ARR = 65535;											
	TIM3->CR1 |= TIM_CR1_CEN; 							
	TIM3->CNT = 0;
}
	

int main(void)
{		

	beginEncoderTim3(); 
	beginEncoderTim1(); 

	uint16_t volatile encoder1;
	uint16_t volatile encoder2;

	while(1)
	{

		encoder2 = TIM3->CNT;
		encoder1 = TIM1->CNT;

	}
	
}