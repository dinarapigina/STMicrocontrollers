/*
  ******************************************************************************
  *
	* @file    stm32f10x_usart.c
	* @file    stm32f10x_usart.h
	* @file    example_usart.c
  * @author  Gryumov Stanislav
  * @version V1.0.0
  * @date    19.02.2019
  * @brief   Библиотека передачи данных по интерфейчу USART
  *			 
  *		Отладочная плата: STM32VLDISCOVERY 
	*		Описание библиотеки
	*
	*		USART1: PA9 -> TX (передача), P10 -> RX (прием) 
	*		USART1: PA2 -> TX (передача), P3 -> RX (прием)
	*		
	*		Функция инициализации: 
	*		
	*		USARTx - номер USART1/USART2
	*		baudrate - скорость передачи данных бот/с 1200,2400,4800,9600,14400,19200...
	*		usartBegin(USARTx,baudrate); 
	*		
	*		Функция передачи данных: 
	*		USARTx - номер USART1/USART2
	*		srt - передаваемая строка
	*		usartTransmission(USARTx,str);
	*		
	*		Функция передачи строки: 
	*		USARTx - номер USART1/USART2
	*		USARTx_Interrupt - имя фукции(вектора)прерываний, переход по принятии строки 
	*		buffer - массив типа char для начала нужно обьявить пример:char RxBuffer[255];
	*		usartReceiver(USARTx,USARTx_Interrupt,buffer);
			
	******************************************************************************
*/

#include "stm32f10x.h"       
#include "string.h"

#define 	FREQUENCY   		 ((uint32_t)72000000) /* частота */

void usartBegin(USART_TypeDef * USARTx, uint16_t baudrate);
void usartTransmission(USART_TypeDef * USARTx, char *str);
void usartReceiver(USART_TypeDef * USARTx,void (*function_Interrupt)(void),char	*buffer);


