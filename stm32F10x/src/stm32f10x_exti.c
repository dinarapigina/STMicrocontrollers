#include "stm32f10x_exti.h"              

static void EXTIx_IRQHandler(void)
{

}

static void (*_EXTI0_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI1_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI2_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI3_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI4_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI5_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI6_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI7_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI8_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI9_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI10_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI11_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI12_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI13_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI14_Interrupt)(void) = EXTIx_IRQHandler;
static void (*_EXTI15_Interrupt)(void) = EXTIx_IRQHandler;


void EXTI0_IRQHandler(void) 
{
	EXTI->PR |= (1<<0);						
	_EXTI0_Interrupt();
}


void EXTI1_IRQHandler(void) 
{
	EXTI->PR |= (1<<1);					
	_EXTI1_Interrupt();
}

void EXTI2_IRQHandler(void) 
{
	EXTI->PR |= (1<<2);						
	_EXTI2_Interrupt();
}

void EXTI3_IRQHandler(void) 
{
	EXTI->PR |= (1<<3);					
	_EXTI3_Interrupt();
}

void EXTI4_IRQHandler(void)
{
	EXTI->PR |= (1<<4);						
	_EXTI4_Interrupt();
}

void EXTI9_5_IRQHandler(void)
{	
	switch (EXTI->PR) 
	{
		case (1<<5): EXTI->PR |= (1<<5); _EXTI5_Interrupt(); break;
		case (1<<6): EXTI->PR |= (1<<6); _EXTI6_Interrupt(); break;
		case (1<<7): EXTI->PR |= (1<<7); _EXTI7_Interrupt(); break;
		case (1<<8): EXTI->PR |= (1<<8); _EXTI8_Interrupt(); break;
		case (1<<9): EXTI->PR |= (1<<9); _EXTI9_Interrupt(); break;
	}
}

void EXTI15_10_IRQHandler(void)	
{
	switch (EXTI->PR) 
	{
		case (1<<10): EXTI->PR |= (1<<10); _EXTI10_Interrupt(); break;
		case (1<<11): EXTI->PR |= (1<<11); _EXTI11_Interrupt(); break;
		case (1<<12): EXTI->PR |= (1<<12); _EXTI12_Interrupt(); break;
		case (1<<13): EXTI->PR |= (1<<13); _EXTI13_Interrupt(); break;
		case (1<<14): EXTI->PR |= (1<<14); _EXTI14_Interrupt(); break;
		case (1<<15): EXTI->PR |= (1<<15); _EXTI15_Interrupt(); break;
	}
}


void extiBebin(GPIO_TypeDef * GPIOx, uint16_t pin, uint8_t edge_mode) 
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	switch ((uint32_t) GPIOx) 
	{
#if defined(RCC_APB2ENR_IOPAEN)
		case (uint32_t) GPIOA: RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; break;
#endif
#if defined(RCC_APB2ENR_IOPBEN)
		case (uint32_t) GPIOB: RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; break;
#endif
#if defined(RCC_APB2ENR_IOPCEN)
		case (uint32_t) GPIOC: RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; break;
#endif
#if defined(RCC_APB2ENR_IOPDEN)
		case (uint32_t) GPIOD: RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; break;
#endif
#if defined(RCC_APB2ENR_IOPEEN)
		case (uint32_t) GPIOE: RCC->APB2ENR |= RCC_APB2ENR_IOPEEN; break;
#endif
#if defined(RCC_APB2ENR_IOPFEN)
		case (uint32_t) GPIOF: RCC->APB2ENR |= RCC_APB2ENR_IOPFEN; break;
#endif
#if defined(RCC_APB2ENR_IOPGEN)
		case (uint32_t) GPIOG: RCC->APB2ENR |= RCC_APB2ENR_IOPGEN; break;
#endif
	}
	switch (edge_mode) 
	{
		case FALLING: 	EXTI->FTSR |= pin; 	EXTI->RTSR &=~pin; break;
		case RISING: 		EXTI->FTSR &=~pin; 	EXTI->RTSR |= pin; break;
		case BOTH: 			EXTI->FTSR |= pin;	EXTI->RTSR |= pin; break;
	}
	switch (pin) 
	{
		case (1<< 0): AFIO->EXTICR[0] = (AFIO->EXTICR[0] &~0x000f) | (((GPIOx - GPIOA) >> 5) <<  0); break;
		case (1<< 1): AFIO->EXTICR[0] = (AFIO->EXTICR[0] &~0x00f0) | (((GPIOx - GPIOA) >> 5) <<  4); break;
		case (1<< 2): AFIO->EXTICR[0] = (AFIO->EXTICR[0] &~0x0f00) | (((GPIOx - GPIOA) >> 5) <<  8); break;
		case (1<< 3): AFIO->EXTICR[0] = (AFIO->EXTICR[0] &~0xf000) | (((GPIOx - GPIOA) >> 5) << 12); break;
		case (1<< 4): AFIO->EXTICR[1] = (AFIO->EXTICR[1] &~0x000f) | (((GPIOx - GPIOA) >> 5) <<  0); break;
		case (1<< 5): AFIO->EXTICR[1] = (AFIO->EXTICR[1] &~0x00f0) | (((GPIOx - GPIOA) >> 5) <<  4); break;
		case (1<< 6): AFIO->EXTICR[1] = (AFIO->EXTICR[1] &~0x0f00) | (((GPIOx - GPIOA) >> 5) <<  8); break;
		case (1<< 7): AFIO->EXTICR[1] = (AFIO->EXTICR[1] &~0xf000) | (((GPIOx - GPIOA) >> 5) << 12); break;
		case (1<< 8): AFIO->EXTICR[2] = (AFIO->EXTICR[2] &~0x000f) | (((GPIOx - GPIOA) >> 5) <<  0); break;
		case (1<< 9): AFIO->EXTICR[2] = (AFIO->EXTICR[2] &~0x00f0) | (((GPIOx - GPIOA) >> 5) <<  4); break;
		case (1<<10): AFIO->EXTICR[2] = (AFIO->EXTICR[2] &~0x0f00) | (((GPIOx - GPIOA) >> 5) <<  8); break;
		case (1<<11): AFIO->EXTICR[2] = (AFIO->EXTICR[2] &~0xf000) | (((GPIOx - GPIOA) >> 5) << 12); break;
		case (1<<12): AFIO->EXTICR[3] = (AFIO->EXTICR[3] &~0x000f) | (((GPIOx - GPIOA) >> 5) <<  0); break;
		case (1<<13): AFIO->EXTICR[3] = (AFIO->EXTICR[3] &~0x00f0) | (((GPIOx - GPIOA) >> 5) <<  4); break;
		case (1<<14): AFIO->EXTICR[3] = (AFIO->EXTICR[3] &~0x0f00) | (((GPIOx - GPIOA) >> 5) <<  8); break;
		case (1<<15): AFIO->EXTICR[3] = (AFIO->EXTICR[3] &~0xf000) | (((GPIOx - GPIOA) >> 5) << 12); break;
	};
}

void extiActivation(uint16_t pin, void (*function_Interrupt)(void)) 
{
	
	EXTI->PR |= pin;						
	EXTI->IMR |= pin;							
	EXTI->EMR |= pin;							

	switch (pin) 
	{
		case (1<<0): 	NVIC_EnableIRQ(EXTI0_IRQn); 			_EXTI0_Interrupt  = function_Interrupt; break;
		case (1<<1): 	NVIC_EnableIRQ(EXTI1_IRQn); 			_EXTI1_Interrupt  = function_Interrupt; break;
		case (1<<2): 	NVIC_EnableIRQ(EXTI2_IRQn); 			_EXTI2_Interrupt  = function_Interrupt; break;
		case (1<<3): 	NVIC_EnableIRQ(EXTI3_IRQn); 			_EXTI3_Interrupt  = function_Interrupt; break;
		case (1<<4): 	NVIC_EnableIRQ(EXTI4_IRQn); 			_EXTI4_Interrupt  = function_Interrupt; break;
		case (1<<5): 	NVIC_EnableIRQ(EXTI9_5_IRQn); 		_EXTI5_Interrupt  = function_Interrupt; break;
		case (1<<6): 	NVIC_EnableIRQ(EXTI9_5_IRQn); 		_EXTI6_Interrupt  = function_Interrupt; break;
		case (1<<7): 	NVIC_EnableIRQ(EXTI9_5_IRQn); 		_EXTI7_Interrupt  = function_Interrupt; break;
		case (1<<8): 	NVIC_EnableIRQ(EXTI9_5_IRQn);			_EXTI8_Interrupt  = function_Interrupt; break;
		case (1<<9): 	NVIC_EnableIRQ(EXTI9_5_IRQn); 		_EXTI9_Interrupt  = function_Interrupt; break;
		case (1<<10): NVIC_EnableIRQ(EXTI15_10_IRQn); 	_EXTI10_Interrupt = function_Interrupt; break;
		case (1<<11): NVIC_EnableIRQ(EXTI15_10_IRQn); 	_EXTI11_Interrupt = function_Interrupt; break;
		case (1<<12): NVIC_EnableIRQ(EXTI15_10_IRQn);		_EXTI12_Interrupt = function_Interrupt; break;
		case (1<<13): NVIC_EnableIRQ(EXTI15_10_IRQn); 	_EXTI13_Interrupt = function_Interrupt; break;
		case (1<<14): NVIC_EnableIRQ(EXTI15_10_IRQn); 	_EXTI14_Interrupt = function_Interrupt; break;
		case (1<<15): NVIC_EnableIRQ(EXTI15_10_IRQn); 	_EXTI15_Interrupt = function_Interrupt; break;
	}
}



void attachInterrupt(GPIO_TypeDef * GPIOx ,uint16_t pin,void (*function_Interrupt)(void),uint8_t edge_mode)
{

     extiBebin(GPIOx,(1 << pin),edge_mode); 
     extiActivation((1 << pin),function_Interrupt); 
	
}
