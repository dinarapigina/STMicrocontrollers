#include "stm32f10x.h"    

void pwmBegin()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;   
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;	
	
	GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);  /* PA0 */  
	GPIOA->CRL |= (GPIO_CRL_CNF0_1 | GPIO_CRL_MODE0);
	
	TIM2->PSC  = 1;	
	TIM2->ARR = 12;
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_0;
	TIM2->CCER |= TIM_CCER_CC1E;
	TIM2->CR1 |=  TIM_CR1_OPM;		 /* Режим одного импульса */
			      	
}

void pwdBit(uint8_t bit )
{
	switch(bit)
	{
		case 0:TIM2->ARR = 12; TIM2->CCR1 = 8; TIM2->CR1 |= TIM_CR1_CEN; while(!(TIM2->SR & TIM_SR_UIF)){} break;
		case 1:TIM2->ARR = 12; TIM2->CCR1 = 1; TIM2->CR1 |= TIM_CR1_CEN; while(!(TIM2->SR & TIM_SR_UIF)){} break;
	}	
}

void writeTrioByte(uint32_t rgb)
{
	uint8_t bit;
	for(uint8_t coun = 0;coun<24;coun++)
	{	
		bit = ((rgb >> coun)&(0x1));
		pwdBit(bit);
	}
}



int main()
{
	
	pwmBegin();
		
	while(1)
	{
				 
		 writeTrioByte(0x00FF00);	
		 writeTrioByte(0xFF0000);		
		 writeTrioByte(0x0000FF);
	
		 for(int i=0;i<2400000;i++);
		 
		 writeTrioByte(0x0000FF);	
		 writeTrioByte(0x00FF00);	
		 writeTrioByte(0xFF0000);		
		
		 for(int i=0;i<2400000;i++);
		
		 writeTrioByte(0xFF0000);
		 writeTrioByte(0x0000FF);	
		 writeTrioByte(0x00FF00);			
		
		 for(int i=0;i<2400000;i++);
		 		
	}
	
}







     