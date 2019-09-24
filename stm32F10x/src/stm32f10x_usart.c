#include "stm32f10x_usart.h"   

#define USART1_REMAP 1  // REMAP ON TX PA9->PB6, PX PA10->PB7 

void usartBegin(USART_TypeDef * USARTx, uint16_t baudrate)
{
	
		uint32_t volatile _BRR = ((SystemCoreClock +  baudrate / 2 ) / baudrate); // вычисляем скорость передачи данных USART
			   
		RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;	
		
		if (USARTx == USART1)
		{
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN;			
#if USART1_REMAP
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; 
			GPIOB->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6);
			GPIOB->CRL |= GPIO_CRL_CNF6_1;  /* PB6 TX*/
			GPIOB->CRL |= GPIO_CRL_MODE6_1;		
			GPIOB->CRL &= ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7);
			GPIOB->CRL |= GPIO_CRL_CNF7_0; /* PB7 RX */			
			AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;
#else		
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 
			GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);
			GPIOA->CRH |= GPIO_CRH_CNF9_1;  /* PA9 TX*/
			GPIOA->CRH |= GPIO_CRH_MODE9_1;		
			GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
			GPIOA->CRH |= GPIO_CRH_CNF10_0; /* PA10 RX */
#endif			
		}
		
		if (USARTx == USART2)
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 
			RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
			GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);
			GPIOA->CRL |= GPIO_CRL_CNF2_1;  /* PA2 TX*/
			GPIOA->CRL |= GPIO_CRL_MODE2_1;		
			GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);
			GPIOA->CRL |= GPIO_CRL_CNF3_0; /* PA3 RX */
		}
		
		if (USARTx == USART3)
		{
			RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;   
			GPIOB->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
			GPIOB->CRH |= GPIO_CRH_CNF10_1;  /* PB10 TX*/
			GPIOB->CRH |= GPIO_CRH_MODE10_1;	
			
			GPIOB->CRH &= ~(GPIO_CRH_MODE11 | GPIO_CRH_CNF11);
			GPIOB->CRH |= GPIO_CRH_CNF11_0; /* PB11 RX */
		}
		
		USARTx->BRR = _BRR;
		USARTx->CR2 = 0;
		USARTx->CR1 = 0;
		USARTx->CR1 |= USART_CR1_TE;
		USARTx->CR1 |= USART_CR1_RE;
		USARTx->CR1 |= USART_CR1_UE;
			
}

void usartTransmission(USART_TypeDef * USARTx, char *str)
{
	uint16_t i = 0;
	
	for (i=0; i < strlen(str); i++)
	{	
		while(!(USARTx->SR&USART_SR_TC)){};
	  USARTx->DR = str[i];
	}
	
	while(!(USARTx->SR&USART_SR_TC));
	//USARTx->DR = '\n';
	
}

static void USARTx_IRQHandler(void){}

static void (*_USART1_Interrupt)(void) = USARTx_IRQHandler;
static void (*_USART2_Interrupt)(void) = USARTx_IRQHandler;
static void (*_USART3_Interrupt)(void) = USARTx_IRQHandler;
	
char *receiverBuffer;

void usartReceiver(USART_TypeDef * USARTx,void (*function_Interrupt)(void),char	*buffer)
{			
		USARTx->CR1 |= USART_CR1_RXNEIE;
		if (USARTx == USART1)
		{	
				NVIC_EnableIRQ(USART1_IRQn);
				receiverBuffer = buffer;
				_USART1_Interrupt  = function_Interrupt;
		}
		
		if (USARTx == USART2)
		{
				NVIC_EnableIRQ(USART2_IRQn);
				receiverBuffer = buffer;
				_USART2_Interrupt  = function_Interrupt;
		}
		
		if (USARTx == USART3)
		{
				NVIC_EnableIRQ(USART3_IRQn);
				receiverBuffer = buffer;
				_USART3_Interrupt = function_Interrupt;
		}
}

void USART1_IRQHandler(void)
{
	char tmp;
	if ((USART1->SR & USART_SR_RXNE)!=0)	
	{
		tmp = USART1->DR;
		if (tmp == 0x0D)							
		{	
			_USART1_Interrupt();
			return;	
		}	
		receiverBuffer[strlen(receiverBuffer)] = tmp;
	} 	
}

void USART2_IRQHandler(void)
{
	char tmp;
	if ((USART2->SR & USART_SR_RXNE)!=0)	
	{
		tmp = USART2->DR;
		if (tmp == 0x0D)							
		{	
			_USART2_Interrupt();
			return;	
		}	
		receiverBuffer[strlen(receiverBuffer)] = tmp;
	} 	
}

void USART3_IRQHandler(void)
{
	char tmp;
	if ((USART3->SR & USART_SR_RXNE)!=0)	
	{
		tmp = USART3->DR;
		if (tmp == 0x0D)							
		{	
			_USART3_Interrupt();
			return;	
		}	
		receiverBuffer[strlen(receiverBuffer)] = tmp;
	} 	
}

