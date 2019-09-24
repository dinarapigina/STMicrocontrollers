/*
  ******************************************************************************
  *
	* @file    stm32f10x_exti.c
	* @file    stm32f10x_exti.h
	* @file    example_exti.h
  * @author  Gryumov Stanislav
  * @version V1.0.0
  * @date    15.02.2019
  * @brief   Библиотека передачи данных по интерфейчу USART
  *			 
  *		Отладочная плата: STM32VLDISCOVERY 
	*		Описание библиотеки
	*		
	*		Функция инициализации: 
	*
	*		attachInterrupt(GPIOx,Pxy,EXTIx_Interrupt,edge_mode);
	*		GPIOx: порт на который настраиваем прерывание GPIOA./.GPIOB./.GPIOC./.GPIOD
	*		Pxy: x - буква порта, y - номер порта PA0/PA1/PB2 
	*		EXTIx_Interrupt: обозначение функции прерывания 
	*		edge_mode: прерывание по событию FALLING - по заднему фронту / RISING - по переднему фронту / BOTH - по обоим фронтам
	*
 	******************************************************************************
*/

#include "stm32f10x_exti.h"  

void EXTI0_Interrupt(void)
{
		/* user code */
		GPIOC->ODR ^= 0x0100;		// PC8 - включение / выключение светодиода
}

void EXTI1_Interrupt(void)
{
		/* user code */
		GPIOC->ODR ^= 0x0200;		// PC9 - включение / выключение светодиода
}

void EXTI2_Interrupt(void)
{
		/* user code */	
		GPIOC->ODR ^= 0x0300;		// PC8, PC9 - включение / выключение светодиода
}

int main()
{
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;					// вкление тактирования порта PC для моргания светодиодов 
	GPIOC -> CRH = 0x22;												// PC9 - на порта выход

	attachInterrupt(GPIOB,PB0,EXTI0_Interrupt,FALLING);  // настройка прерывания на порту PB0 по заднему фронту
	
	attachInterrupt(GPIOA,PA1,EXTI1_Interrupt,RISING);	 // настройка прерывания на порту PA1 по переднему фронту
	
	attachInterrupt(GPIOC,PC2,EXTI2_Interrupt,BOTH);		 // настройка прерывания на порту PC2 по обоим фронтам
		
	while(1)
	{
		/* user code */	
	}

}



