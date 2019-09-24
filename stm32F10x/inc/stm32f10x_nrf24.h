
#include "stm32f10x.h"  

#define ACTIVATE 		((uint8_t)0x50) //
#define RD_RX_PLOAD ((uint8_t)0x61) // Define RX payload register address
#define WR_TX_PLOAD ((uint8_t)0xA0) // Define TX payload register address
#define FLUSH_TX 		((uint8_t)0xE1)
#define FLUSH_RX 		((uint8_t)0xE2)

#define CONFIG 			((uint8_t)0x00) //'Config' register address
#define EN_AA 			((uint8_t)0x01) //'Enable Auto Acknowledgment' register address
#define EN_RXADDR 	((uint8_t)0x02) //'Enabled RX addresses' register address
#define SETUP_AW 		((uint8_t)0x03) //'Setup address width' register address
#define SETUP_RETR	((uint8_t)0x04) //'Setup Auto. Retrans' register address
#define RF_CH 			((uint8_t)0x05) //'RF channel' register address
#define RF_SETUP 		((uint8_t)0x06) //'RF setup' register address
#define STATUS 			((uint8_t)0x07) //'Status' register address
#define RX_ADDR_P0 	((uint8_t)0x0A) //'RX address pipe0' register address
#define RX_ADDR_P1 	((uint8_t)0x0B) //'RX address pipe1' register address
#define TX_ADDR 		((uint8_t)0x10) //'TX address' register address
#define RX_PW_P0 		((uint8_t)0x11) //'RX payload width, pipe0' register address
#define RX_PW_P1		((uint8_t)0x12) //'RX payload width, pipe1' register address
#define FIFO_STATUS ((uint8_t)0x17) //'FIFO Status Register' register address
#define DYNPD 			((uint8_t)0x1C)
#define FEATURE 		((uint8_t)0x1D)

#define PRIM_RX			((uint8_t)0x00) //RX/TX control (1: PRX, 0: PTX)
#define PWR_UP 			((uint8_t)0x01) //1: POWER UP, 0:POWER DOWN
#define RX_DR 			((uint8_t)0x40) //Data Ready RX FIFO interrupt
#define TX_DS 			((uint8_t)0x20) //Data Sent TX FIFO interrupt
#define MAX_RT		  ((uint8_t)0x10) //Maximum number of TX retransmits interrupt
#define W_REGISTER 	((uint8_t)0x20) //запись в регистр
#define R_REGISTER 	((uint8_t)0x00) //чтение с регистра

void csBegin(void);
void nRf24Begin(void);
uint8_t nRF24_ReadReg(uint8_t addr);
void nRF24_WriteReg(uint8_t addr, uint8_t dataWrite);
