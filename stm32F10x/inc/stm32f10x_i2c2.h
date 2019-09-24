#include "stm32f10x.h"  
void SysTickBegin(uint32_t times);
void i2cBegin(void);
void i2cTransmission(uint8_t registerSensor, uint8_t RegisterAddress, uint8_t dataWrite);
void i2cReceiver(uint8_t addressWrite, uint8_t addressRead, uint8_t adress,uint8_t *buffer,uint8_t size);
uint8_t i2cReceiverByte(uint8_t addressWrite, uint8_t addressRead, uint8_t adress);
void i2cTransmissionByte(uint8_t registerSensor, uint8_t dataWrite);
