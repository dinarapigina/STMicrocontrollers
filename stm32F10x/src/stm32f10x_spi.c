#include "stm32f10x_spi.h"
#include "stm32f10x_delay.h"

void spiBegin(SPI_TypeDef * SPIx,uint16_t baudrate)
{
		RCC->APB2ENR |=  RCC_APB2ENR_AFIOEN;     //включить тактирование альтернативных функций
		RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN;     //включить тактирование порта А
		
		//Вывод управления ST: выход строп бит записи данных в драйвер, общего назначения,50MHz                            
		GPIOA->CRL   |=  GPIO_CRL_MODE3_1;    //
		GPIOA->CRL   &= ~GPIO_CRL_CNF3;     //
		GPIOA->BSRR   =  GPIO_BSRR_BR3;     //
	
		//Вывод управления SS: выход двухтактный, общего назначения,50MHz                            
		GPIOA->CRL   |=  GPIO_CRL_MODE4;    //
		GPIOA->CRL   &= ~GPIO_CRL_CNF4;     //
		GPIOA->BSRR   =  GPIO_BSRR_BS4;     //
		 
		//Вывод SCK: выход двухтактный, альтернативная функция, 50MHz
		GPIOA->CRL   |=  GPIO_CRL_MODE5;    //
		GPIOA->CRL   &= ~GPIO_CRL_CNF5;     //
		GPIOA->CRL   |=  GPIO_CRL_CNF5_1;   //
		 
		//Вывод MISO: вход цифровой с подтягивающим резистором, подтяжка к плюсу
		GPIOA->CRL   &= ~GPIO_CRL_MODE6;    //
		GPIOA->CRL   &= ~GPIO_CRL_CNF6;     //
		GPIOA->CRL   |=  GPIO_CRL_CNF6_1;   //
		GPIOA->BSRR   =  GPIO_BSRR_BS6;     //
		 
		//Вывод MOSI: выход двухтактный, альтернативная функция, 50MHz
		GPIOA->CRL   |=  GPIO_CRL_MODE7;    //
		GPIOA->CRL   &= ~GPIO_CRL_CNF7;     //
		GPIOA->CRL   |=  GPIO_CRL_CNF7_1;   //
		
		//Настроим модуль SPI.
		RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; //подать тактирование 
		
		SPIx->CR1     = 0x0000;             //очистить первый управляющий регистр
		SPIx->CR2     = 0x0000;             //очистить второй управляющий регистр
		SPIx->CR1    |= SPI_CR1_MSTR;       //контроллер должен быть мастером    
		SPIx->CR1    |= baudrate;         	//задаем скорость
		SPIx->CR1    |= SPI_CR1_SSI;        //обеспечить высокий уровень программного NSS
		SPIx->CR1    |= SPI_CR1_SSM;        //разрешить программное формирование NSS
		SPIx->CR1    |= SPI_CR1_SPE;        //разрешить работу модуля SPI
		
}

void spiTransmissionByte(SPI_TypeDef * SPIx,uint8_t byte)
{
		while (!(SPIx->SR & SPI_SR_TXE));
		SPIx->DR = byte;
		while (!(SPIx->SR & SPI_SR_TXE));
		while ((SPIx->SR & SPI_SR_BSY));
}

void spiTransmission(SPI_TypeDef * SPIx,uint8_t addr, uint8_t *dataWrite, uint8_t size,uint32_t Timout)
{
		while (!(SPIx->SR & SPI_SR_TXE));
		SPIx->DR = addr;
		delayMicroseconds(TIM2,Timout);
		while (size--) 
		{
				while (!(SPIx->SR & SPI_SR_TXE));
				SPIx->DR = *dataWrite++;
				delayMicroseconds(TIM2,Timout);
		}
		while (!(SPIx->SR & SPI_SR_TXE));
		while ((SPIx->SR & SPI_SR_BSY));	
}

void spiReceiver(SPI_TypeDef * SPIx,uint8_t addr, uint8_t *dataRead, uint8_t size)
{
	  uint8_t temp = 0;
	
		while (!(SPI1->SR & SPI_SR_TXE));
		SPIx->DR = addr;
		while (!(SPIx->SR & SPI_SR_RXNE));
		temp = SPIx->DR;
	
		while (size--) 
		{
			while (!(SPIx->SR & SPI_SR_TXE));
			SPIx->DR = 0xFF;
			while (!(SPIx->SR & SPI_SR_RXNE));
			*dataRead++ = SPIx->DR;
			delayMicroseconds(TIM2,2);
		}
		
		while (!(SPIx->SR & SPI_SR_TXE));
		while ((SPIx->SR & SPI_SR_BSY));	

}

void spiTransmissionReceiver(SPI_TypeDef * SPIx,uint8_t addr, uint8_t *dataWrite,uint8_t *dataRead, uint8_t size)
{
  uint8_t temp = 0;
  while (!(SPIx->SR & SPI_SR_TXE));
  SPIx->DR = addr;
  while (!(SPIx->SR & SPI_SR_RXNE));
  temp = SPIx->DR;
  while (size--) 
	{
    while (!(SPIx->SR & SPI_SR_TXE));
    SPIx->DR = *dataWrite++;
    while (!(SPIx->SR & SPI_SR_RXNE));
    *dataRead++ = SPIx->DR;
  }
  while (!(SPIx->SR & SPI_SR_TXE));
  while ((SPIx->SR & SPI_SR_BSY));

}

