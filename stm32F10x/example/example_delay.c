/*
  ******************************************************************************
  *
  * @file    stm32f10x_delay.c
  * @file    stm32f10x_delay.h
  * @file    example_delay.c
  * @author  Gryumov Stanislav
  * @email   gryumov@gmail.com
  * @version V1.0.0
  * @date    21.02.2019
  * @brief   Hardware delay library
  *			 
  *		Debug Board: STM32VLDISCOVERY 
  *
  ******************************************************************************
*/

#include "stm32f10x_delay.h"

void gpioBegin()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH 	&=~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8);	/* reset port 8 */
	GPIOC->CRH 	|=	GPIO_CRH_MODE8_1;					/* port configured to output frequency 50MHz 0010 - 0x2 */
	GPIOC->CRH 	&=~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9); 	/* reset port 9 */
	GPIOC->CRH 	|=	GPIO_CRH_MODE9; 					/* port configured to output frequency 50MHz 0011 - 0x3 */
}

int main()
{

	gpioBegin();  						/* port initialization PC8,PC9 */ 
	delayBegin(TIM2); 					/* initialization TIM2 */
	
	while(1)
	{	
		GPIOC->BSRR = GPIO_BSRR_BR8; 	/* PC8 port LOW */
		GPIOC->BSRR = GPIO_BSRR_BS9;	/* PC9 port HIGH */
		
		delay(TIM2,1000); 				/* delay 1 second */
		
		GPIOC->BSRR = GPIO_BSRR_BS8;	/* PC8 port HIGH */
		GPIOC->BSRR = GPIO_BSRR_BR9;	/* PC9 port LOW */
		
		delay(TIM2,100); 				/*delay 100 milliseconds 0.1 second*/
	}
}