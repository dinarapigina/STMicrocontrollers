#include "stm32f10x_one_wire.h"

float temperature(GPIO_TypeDef * GPIOx, uint8_t numberPort)
{

		int16_t  temp;
		float  	 temp_cels;
		uint8_t  byteRead_H;
		uint8_t  byteRead_L;

		OneWireReset(GPIOx,numberPort);
		OneWireWriteByte(GPIOx,numberPort,0xCC);
		OneWireWriteByte(GPIOx,numberPort,0x44);

		delayMicroseconds(TIM2,1000000);

		OneWireReset(GPIOx,numberPort);
		OneWireWriteByte(GPIOx,numberPort,0xCC);
		OneWireWriteByte(GPIOx,numberPort,0xBE);

		byteRead_L = OneWireReadByte(GPIOx,numberPort);
		byteRead_H = OneWireReadByte(GPIOx,numberPort);
		temp  =  ((byteRead_H << 8) | byteRead_L);
		temp_cels = temp * 0.0625;

		return temp_cels;

}

int main()
{
	
		OneWireBegin(GPIOC,TIM2);
		
		float volatile temp_cels;
		
		while(1)
		{	
			temp_cels = temperature(GPIOC,PC9);
		}
	
}
