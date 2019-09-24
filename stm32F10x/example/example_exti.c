/*
  ******************************************************************************
  *
	* @file    stm32f10x_exti.c
	* @file    stm32f10x_exti.h
	* @file    example_exti.h
  * @author  Gryumov Stanislav
  * @version V1.0.0
  * @date    15.02.2019
  * @brief   ���������� �������� ������ �� ���������� USART
  *			 
  *		���������� �����: STM32VLDISCOVERY 
	*		�������� ����������
	*		
	*		������� �������������: 
	*
	*		attachInterrupt(GPIOx,Pxy,EXTIx_Interrupt,edge_mode);
	*		GPIOx: ���� �� ������� ����������� ���������� GPIOA./.GPIOB./.GPIOC./.GPIOD
	*		Pxy: x - ����� �����, y - ����� ����� PA0/PA1/PB2 
	*		EXTIx_Interrupt: ����������� ������� ���������� 
	*		edge_mode: ���������� �� ������� FALLING - �� ������� ������ / RISING - �� ��������� ������ / BOTH - �� ����� �������
	*
 	******************************************************************************
*/

#include "stm32f10x_exti.h"  

void EXTI0_Interrupt(void)
{
		/* user code */
		GPIOC->ODR ^= 0x0100;		// PC8 - ��������� / ���������� ����������
}

void EXTI1_Interrupt(void)
{
		/* user code */
		GPIOC->ODR ^= 0x0200;		// PC9 - ��������� / ���������� ����������
}

void EXTI2_Interrupt(void)
{
		/* user code */	
		GPIOC->ODR ^= 0x0300;		// PC8, PC9 - ��������� / ���������� ����������
}

int main()
{
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;					// ������� ������������ ����� PC ��� �������� ����������� 
	GPIOC -> CRH = 0x22;												// PC9 - �� ����� �����

	attachInterrupt(GPIOB,PB0,EXTI0_Interrupt,FALLING);  // ��������� ���������� �� ����� PB0 �� ������� ������
	
	attachInterrupt(GPIOA,PA1,EXTI1_Interrupt,RISING);	 // ��������� ���������� �� ����� PA1 �� ��������� ������
	
	attachInterrupt(GPIOC,PC2,EXTI2_Interrupt,BOTH);		 // ��������� ���������� �� ����� PC2 �� ����� �������
		
	while(1)
	{
		/* user code */	
	}

}



