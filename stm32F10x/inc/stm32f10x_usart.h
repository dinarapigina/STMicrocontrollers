/*
  ******************************************************************************
  *
	* @file    stm32f10x_usart.c
	* @file    stm32f10x_usart.h
	* @file    example_usart.c
  * @author  Gryumov Stanislav
  * @version V1.0.0
  * @date    19.02.2019
  * @brief   ���������� �������� ������ �� ���������� USART
  *			 
  *		���������� �����: STM32VLDISCOVERY 
	*		�������� ����������
	*
	*		USART1: PA9 -> TX (��������), P10 -> RX (�����) 
	*		USART1: PA2 -> TX (��������), P3 -> RX (�����)
	*		
	*		������� �������������: 
	*		
	*		USARTx - ����� USART1/USART2
	*		baudrate - �������� �������� ������ ���/� 1200,2400,4800,9600,14400,19200...
	*		usartBegin(USARTx,baudrate); 
	*		
	*		������� �������� ������: 
	*		USARTx - ����� USART1/USART2
	*		srt - ������������ ������
	*		usartTransmission(USARTx,str);
	*		
	*		������� �������� ������: 
	*		USARTx - ����� USART1/USART2
	*		USARTx_Interrupt - ��� ������(�������)����������, ������� �� �������� ������ 
	*		buffer - ������ ���� char ��� ������ ����� �������� ������:char RxBuffer[255];
	*		usartReceiver(USARTx,USARTx_Interrupt,buffer);
			
	******************************************************************************
*/

#include "stm32f10x.h"       
#include "string.h"

#define 	FREQUENCY   		 ((uint32_t)72000000) /* ������� */

void usartBegin(USART_TypeDef * USARTx, uint16_t baudrate);
void usartTransmission(USART_TypeDef * USARTx, char *str);
void usartReceiver(USART_TypeDef * USARTx,void (*function_Interrupt)(void),char	*buffer);


