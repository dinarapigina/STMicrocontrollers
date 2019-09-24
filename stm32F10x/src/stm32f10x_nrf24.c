#include "stm32f10x_nrf24.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_delay.h"

void csBegin(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRH 	&=~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
	GPIOA->CRH 	|=	GPIO_CRH_MODE8;	
	GPIOA->CRH 	&=~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9);
	GPIOA->CRH 	|=	GPIO_CRH_MODE9;
}

void  cs_On(void)
{
	GPIOA->BSRR = GPIO_BSRR_BR8;	
}

void cs_Off(void)
{
	GPIOA->BSRR = GPIO_BSRR_BS8;	
}

void  ceSet(void)
{
	GPIOA->BSRR = GPIO_BSRR_BS9;	
}

void ceReset(void)
{
	GPIOA->BSRR = GPIO_BSRR_BR9;	
}

uint8_t nRF24_ReadReg(uint8_t addr)
{
  uint8_t dataRead = 0x00;
	addr |= R_REGISTER;
	cs_On();
	spiTransmissionByte(SPI1,addr);
	delayMicroseconds(TIM2,2);
	if(addr!=STATUS)
	{
		spiReceiver(SPI1,addr,&dataRead,1);
  }
	cs_Off();
	return dataRead;
}

void nRF24_WriteReg(uint8_t addr, uint8_t dataWrite)
{
  addr |= W_REGISTER;	//включим бит записи в адрес
  cs_On();
	spiTransmission(SPI1,addr,&dataWrite,1,2);
  cs_Off();
}

void nRF24ReadBuffer(uint8_t addr,uint8_t *pBuffer,uint8_t bytes)
{
  cs_On();
		spiReceiver(SPI1,addr,pBuffer,bytes); 
  cs_Off();
}


void nRF24WriteBuffer(uint8_t addr, uint8_t *pBuffer,uint8_t bytes)
{
  addr |= W_REGISTER;		//включим бит записи в адрес
  cs_On();
		spiTransmission(SPI1,addr,pBuffer,bytes,2);
		delayMicroseconds(TIM2,2);
  cs_Off();
}

void nRF24_FlushRX(void)
{
  uint8_t dataWrite = FLUSH_RX;
  cs_On();
	spiTransmission(SPI1,0x00,&dataWrite,1,2);
  delayMicroseconds(TIM2,1);
  cs_Off();

}

void nRF24_FlushTX(void)
{
  uint8_t dataWrite = FLUSH_TX;
  cs_On();
	spiTransmission(SPI1,0x00,&dataWrite,1,2);
  delayMicroseconds(TIM2,1);
  cs_Off();
}

void nRF24L01_RX_Mode(void)
{
  uint8_t regval=0x00;
  regval = nRF24_ReadReg(CONFIG); //разбудим модуль и переведём его в режим приёмника, включив биты PWR_UP и PRIM_RX
  regval |= (1<<PWR_UP)|(1<<PRIM_RX);
  nRF24_WriteReg(CONFIG,regval);
  ceSet();
	delayMicroseconds(TIM2,1500);
	nRF24_FlushRX();
  nRF24_FlushTX();

}
uint8_t TX_ADDRESS[5] = {0x11,0xDD,0xCC,0xBB,0xAA};
uint8_t RX_BUF[5] = {0};

void nRf24Begin(void)
{
	ceReset();
	delay(TIM2,5);
	nRF24_WriteReg(CONFIG,0x0A);
	while(nRF24_ReadReg(CONFIG) == 0x0A)
	{
			nRF24_WriteReg(CONFIG,0x0A);
			delay(TIM2,5);
	}
	delay(TIM2,5);
	nRF24_WriteReg(EN_AA, 0x02);
	nRF24_WriteReg(EN_RXADDR, 0x02);
	nRF24_WriteReg(SETUP_AW, 0x01);
	nRF24_WriteReg(SETUP_RETR, 0x5F);
	nRF24_WriteReg(FEATURE, 0);
	nRF24_WriteReg(DYNPD, 0);
	nRF24_WriteReg(STATUS, 0x70);
	nRF24_WriteReg(RF_CH, 76); // частота 2476 MHz
	nRF24_WriteReg(RF_SETUP, 0x06); //TX_PWR:0dBm, Datarate:1Mbps
	nRF24WriteBuffer(TX_ADDR,TX_ADDRESS,5);
	nRF24WriteBuffer(RX_ADDR_P1,TX_ADDRESS,5);
	nRF24_WriteReg(RX_PW_P1,2);
	nRF24L01_RX_Mode();
}

uint8_t volatile buffer[3];

int main()
{
	spiBegin(SPI1,DIVIDER_256);
	delayBegin(TIM2);
	csBegin();
	nRf24Begin();
	
	
	while(1)
	{
// nRF24_ReadReg(CONFIG);
// nRF24_ReadReg(EN_AA);
// nRF24_ReadReg(RF_SETUP);
// nRF24_ReadReg(SETUP_RETR);
//		 nRF24_ReadReg(RF_CH);
//		nRF24ReadBuffer(TX_ADDR,buffer,3);
//		nRF24ReadBuffer(RX_ADDR_P1,buffer,3);
		//delay(TIM2,1000);

	}

}