#include "stm32f10x_spi.h"
#include "stm32f10x_delay.h"

void spiBegin(SPI_TypeDef * SPIx,uint16_t baudrate)
{
		RCC->APB2ENR |=  RCC_APB2ENR_AFIOEN;     //�������� ������������ �������������� �������
		RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN;     //�������� ������������ ����� �
		
		//����� ���������� ST: ����� ����� ��� ������ ������ � �������, ������ ����������,50MHz                            
		GPIOA->CRL   |=  GPIO_CRL_MODE3_1;    //
		GPIOA->CRL   &= ~GPIO_CRL_CNF3;     //
		GPIOA->BSRR   =  GPIO_BSRR_BR3;     //
	
		//����� ���������� SS: ����� �����������, ������ ����������,50MHz                            
		GPIOA->CRL   |=  GPIO_CRL_MODE4;    //
		GPIOA->CRL   &= ~GPIO_CRL_CNF4;     //
		GPIOA->BSRR   =  GPIO_BSRR_BS4;     //
		 
		//����� SCK: ����� �����������, �������������� �������, 50MHz
		GPIOA->CRL   |=  GPIO_CRL_MODE5;    //
		GPIOA->CRL   &= ~GPIO_CRL_CNF5;     //
		GPIOA->CRL   |=  GPIO_CRL_CNF5_1;   //
		 
		//����� MISO: ���� �������� � ������������� ����������, �������� � �����
		GPIOA->CRL   &= ~GPIO_CRL_MODE6;    //
		GPIOA->CRL   &= ~GPIO_CRL_CNF6;     //
		GPIOA->CRL   |=  GPIO_CRL_CNF6_1;   //
		GPIOA->BSRR   =  GPIO_BSRR_BS6;     //
		 
		//����� MOSI: ����� �����������, �������������� �������, 50MHz
		GPIOA->CRL   |=  GPIO_CRL_MODE7;    //
		GPIOA->CRL   &= ~GPIO_CRL_CNF7;     //
		GPIOA->CRL   |=  GPIO_CRL_CNF7_1;   //
		
		//�������� ������ SPI.
		RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; //������ ������������ 
		
		SPIx->CR1     = 0x0000;             //�������� ������ ����������� �������
		SPIx->CR2     = 0x0000;             //�������� ������ ����������� �������
		SPIx->CR1    |= SPI_CR1_MSTR;       //���������� ������ ���� ��������    
		SPIx->CR1    |= baudrate;         	//������ ��������
		SPIx->CR1    |= SPI_CR1_SSI;        //���������� ������� ������� ������������ NSS
		SPIx->CR1    |= SPI_CR1_SSM;        //��������� ����������� ������������ NSS
		SPIx->CR1    |= SPI_CR1_SPE;        //��������� ������ ������ SPI
		
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

