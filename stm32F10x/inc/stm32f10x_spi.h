#include "stm32f10x.h"  

#define DIVIDER_2   	((uint16_t)(0x0000)) 	                                  /* 000 Fpclk/2  */
#define DIVIDER_4 		((uint16_t)SPI_CR1_BR_0)										            /* 001 Fpclk/4  */
#define DIVIDER_8 		((uint16_t)SPI_CR1_BR_1)										            /* 010 Fpclk/8  */
#define DIVIDER_16		((uint16_t)SPI_CR1_BR_0 | SPI_CR1_BR_1)					  			/* 011 Fpclk/16 */
#define DIVIDER_32 		((uint16_t)SPI_CR1_BR_2)									             	/* 100 Fpclk/32 */
#define DIVIDER_64 		((uint16_t)SPI_CR1_BR_2 | SPI_CR1_BR_0)									/* 101 Fpclk/64 */
#define DIVIDER_128 	((uint16_t)SPI_CR1_BR_2 | SPI_CR1_BR_1)									/* 110 Fpclk/128*/
#define DIVIDER_256		(SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0)						/* 111 Fpclk/256*/

void spiBegin(SPI_TypeDef * SPIx, uint16_t baudrate);
void spiTransmission(SPI_TypeDef * SPIx,uint8_t addr, uint8_t *dataWrite, uint8_t size,uint32_t Timout);
void spiTransmissionReceiver(SPI_TypeDef * SPIx,uint8_t addr, uint8_t *dataWrite,uint8_t *dataRead, uint8_t size);
void spiReceiver(SPI_TypeDef * SPIx,uint8_t addr, uint8_t *dataRead, uint8_t size);
void spiTransmissionByte(SPI_TypeDef * SPIx,uint8_t byte);