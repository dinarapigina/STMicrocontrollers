#include "stm32f10x_tb6612fng.h"
#define lengthPulse (float)(0.000174886)  // = R*2*pi/pulse_per_round = 33*2*3.14/1185 = 0.174886 mm (R=33mm)
		
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

void tim2Begin(void)
{
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;   
	
	GPIOA->CRL &= ~GPIO_CRL_CNF0;  /* PA0 */  
	GPIOA->CRL |= GPIO_CRL_CNF0_1;
	
	GPIOA->CRL &= ~GPIO_CRL_MODE0;
	GPIOA->CRL |= GPIO_CRL_MODE0;
	
	GPIOA->CRL &= ~GPIO_CRL_CNF1;  /* PA1 */  
	GPIOA->CRL |= GPIO_CRL_CNF1_1;
	
	GPIOA->CRL &= ~GPIO_CRL_MODE1;
	GPIOA->CRL |= GPIO_CRL_MODE1;
		
	TIM2->PSC = (SystemCoreClock/24000000 - 1);
	TIM2->ARR = 255;
	
	TIM2->CCR1 = 0; 
	TIM2->CCR2 = 0;

	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; //CH1
	TIM2->CCER |=  TIM_CCER_CC1E; 
	TIM2->CCER &= ~TIM_CCER_CC1P; 
	
	TIM2->CCMR1 |=  TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2; //CH2
	TIM2->CCER |=  TIM_CCER_CC2E; // on CH2
	TIM2->CCER &= ~TIM_CCER_CC2P; 
	
	TIM2->CR1 &= ~TIM_CR1_DIR;
	TIM2->CR1 |= TIM_CR1_CEN;
}


void gpioBegin(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	GPIOA->CRL &=~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);	
	GPIOA->CRL |= GPIO_CRL_MODE2_1;
	
	GPIOA->CRL &=~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);	
	GPIOA->CRL |= GPIO_CRL_MODE3_1;
	
	GPIOA->CRL &=~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4);	
	GPIOA->CRL |= GPIO_CRL_MODE4_1;
	
  GPIOA->CRL &=~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5);	
	GPIOA->CRL |= GPIO_CRL_MODE5_1;
		
	//GPIOA->CRH &=~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);	
	//GPIOA->CRH |= GPIO_CRH_MODE10_1;
	
	//GPIOA->BSRR = GPIO_BSRR_BS10;
			
}

void forwards(uint8_t left,uint8_t right)
{
	TIM2->CCR1 = right; 
	TIM2->CCR2 = left; 	
	
	GPIOA->BSRR = (GPIO_BSRR_BS2);
	GPIOA->BSRR = (GPIO_BSRR_BS4);
	GPIOA->BSRR = (GPIO_BSRR_BR3);
	GPIOA->BSRR = (GPIO_BSRR_BR5);	
}

void backward(uint8_t left,uint8_t right)
{
	TIM2->CCR1 = right; 
	TIM2->CCR2 = left; 	
	
	GPIOA->BSRR = (GPIO_BSRR_BS3);
	GPIOA->BSRR = (GPIO_BSRR_BS5);
	GPIOA->BSRR = (GPIO_BSRR_BR2);
	GPIOA->BSRR = (GPIO_BSRR_BR4);
}

void stop()
{
	GPIOA->BSRR = (GPIO_BSRR_BR3);
	GPIOA->BSRR = (GPIO_BSRR_BR4);
	GPIOA->BSRR = (GPIO_BSRR_BR2);
	GPIOA->BSRR = (GPIO_BSRR_BR5);
}


float encoderRead(void)
{
	int16_t volatile encoderLeft;
  int16_t volatile encoderRight;
	
	float encoderPositionLeft;
	float encoderPositionRight;
	float encoderPositionCenter;
	
	encoderLeft = ~(TIM3->CNT);
	encoderRight = (TIM1->CNT);
	
	encoderPositionLeft = encoderLeft * lengthPulse;
  encoderPositionRight = encoderRight * lengthPulse;
  encoderPositionCenter = 0.5*(encoderPositionLeft + encoderPositionRight); 
   
	return encoderPositionCenter;
}

void motor(int pwm)
{
	if( pwm > 255)
	{
	   pwm = 255;
	}
	if(pwm < -255)
	{
		pwm = -255;
	} 
	if(pwm > 0)
	{
		forwards(pwm,pwm);
	}
	else if(pwm < 0)
	{
	  backward(-pwm,-pwm);
	}
}

void tb6612fngBegin()
{
	beginEncoderTim1();
	beginEncoderTim3();
	tim2Begin();
	gpioBegin();
}
