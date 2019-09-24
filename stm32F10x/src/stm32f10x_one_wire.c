/*
* Описание взаимодействия с цифровым датчиком ds18b20 
* Для этого нужно инициализировать функцию delayMicroseconds_Init();
* После инициализации можно считывать данные из функции temperature();
* Подключение ds18b20 к stm32 к порту A0 - A7   
*/
 
#include "stm32f10x_one_wire.h" 

//void delayBegin(TIM_TypeDef * TIMx)
//{
//		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   
//		TIMx->PSC     = 24 - 1;              
//		TIMx->CR1     = TIM_CR1_OPM;          
//}

//void delayMicroseconds(TIM_TypeDef * TIMx, uint32_t value)
//{
//		if (value >= 10000){TIM2->PSC = 24000 - 1; value /= 1000;}
//		else{TIM2->PSC = 24 - 1;}
//		TIMx->ARR = value;                  
//		TIMx->CNT = 0;
//		TIMx->CR1 = TIM_CR1_CEN;	      
//		while((TIM2->SR & TIM_SR_UIF)==0){} 
//		TIMx->SR &= ~TIM_SR_UIF;	      
//}

void OneWireBegin(GPIO_TypeDef * GPIOx,TIM_TypeDef * TIMx)
{
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
	
	delayBegin(TIMx);
	
}

void OneWireReset(GPIO_TypeDef * GPIOx,uint8_t numberPort)
{
		if (numberPort < 8)
		{
			GPIOx->CRL = (0x2 << numberPort*4); 	// PA1
		}
		else
		{
			GPIOx->CRH = (0x2 << (numberPort - 8)*4); 	// PA1
		}
		GPIOx->BSRR = (GPIO_BSRR_BR0 << numberPort);
		delayMicroseconds(TIM2,480);
		GPIOx->BSRR = (GPIO_BSRR_BS0 << numberPort);
		if (numberPort < 8)
		{
			GPIOx->CRL = (0x8 << numberPort*4); 	// PA1
		}
		else
		{
			GPIOx->CRH = (0x8 << (numberPort - 8)*4); 	// PA1
		}
		delayMicroseconds(TIM2,30);
		while((GPIOx->IDR & (0x1 << numberPort)) == 0);
		delayMicroseconds(TIM2,15);

}

void OneWireWriteByte(GPIO_TypeDef * GPIOx, uint8_t numberPort, uint8_t byte)
{
		
		if (numberPort < 8)
		{
			GPIOx->CRL = (0x2 << numberPort*4); 	// PA1
		}
		else
		{
			GPIOx->CRH = (0x2 << (numberPort - 8)*4); 	// PA1
		}
		GPIOx->BSRR = (GPIO_BSRR_BS0 << numberPort); // PA1

		uint8_t volatile bit = 0;
		
		for (uint8_t i = 0 ;i < 8; i++)
		{
				bit = (1 << i);
				bit = ((byte & bit) >> i );

				if (bit)
				{
						GPIOx->BSRR = (GPIO_BSRR_BR0 << numberPort); // PA1
						delayMicroseconds(TIM2,15);
						GPIOx->BSRR = (GPIO_BSRR_BS0 << numberPort);
						delayMicroseconds(TIM2,45);

				}
				else
				{
						GPIOx->BSRR = (GPIO_BSRR_BR0 << numberPort);
						delayMicroseconds(TIM2,45);
						GPIOx->BSRR = (GPIO_BSRR_BS0 << numberPort);
						delayMicroseconds(TIM2,15);
				}
		}
	
}

uint8_t OneWireReadByte(GPIO_TypeDef * GPIOx, uint8_t numberPort)
{
		uint8_t volatile byteRead = 0x0;

		for (uint8_t volatile i=0; i<8; i++)
		{	
				if (numberPort < 8)
				{
					GPIOx->CRL = (0x2 << numberPort*4); 	// PA1
				}
				else
				{
					GPIOx->CRH = (0x2 << (numberPort - 8)*4); 	// PA1
				}
				GPIOx->BSRR = (GPIO_BSRR_BR0 << numberPort);
				for(uint8_t j=0;j<20;j++);
				if (numberPort < 8)
				{
					GPIOx->CRL = (0x8 << numberPort*4); 	// PA1
				}
				else
				{
					GPIOx->CRH = (0x8 << (numberPort - 8)*4); 	// PA1
				}
				for(uint16_t j=0;j<20;j++);	
				byteRead |= (((GPIOx->IDR & (0x1 << numberPort)) >> (numberPort)) << i);
				delayMicroseconds(TIM2,60);
		}

		return byteRead;

}

