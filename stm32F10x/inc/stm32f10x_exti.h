#include "stm32f10x.h"       

#define 	FALLING						((uint8_t)0)				//trigger on falling edge_mode
#define 	RISING						((uint8_t)1)				//trigger on rising edge_mode
#define 	BOTH							((uint8_t)2)				//trigger on falling and rising edge_modes

#define 	PA0 							((uint8_t)0)
#define 	PA1 							((uint8_t)1)
#define 	PA2 							((uint8_t)2)
#define 	PA3 							((uint8_t)3)
#define 	PA4 							((uint8_t)4)
#define 	PA5 							((uint8_t)5)
#define 	PA6 							((uint8_t)6)
#define 	PA7 							((uint8_t)7)
#define 	PA8 							((uint8_t)8)
#define 	PA9 							((uint8_t)9)
#define 	PA10 							((uint8_t)10)
#define 	PA11 							((uint8_t)11)
#define 	PA12 							((uint8_t)12)
#define 	PA13 							((uint8_t)13)
#define 	PA14 							((uint8_t)14)
#define 	PA15 							((uint8_t)15)

#define 	PB0 							((uint8_t)0)
#define 	PB1 							((uint8_t)1)
#define 	PB2 							((uint8_t)2)
#define 	PB3 							((uint8_t)3)
#define 	PB4 							((uint8_t)4)
#define 	PB5 							((uint8_t)5)
#define 	PB6 							((uint8_t)6)
#define 	PB7 							((uint8_t)7)
#define 	PB8 							((uint8_t)8)
#define 	PB9 							((uint8_t)9)
#define 	PB10 							((uint8_t)10)
#define 	PB11 							((uint8_t)11)
#define 	PB12 							((uint8_t)12)
#define 	PB13 							((uint8_t)13)
#define 	PB14 							((uint8_t)14)
#define 	PB15 							((uint8_t)15)


#define 	PC0 							((uint8_t)0)
#define 	PC1 							((uint8_t)1)
#define 	PC2 							((uint8_t)2)
#define 	PC3 							((uint8_t)3)
#define 	PC4 							((uint8_t)4)
#define 	PC5 							((uint8_t)5)
#define 	PC6 							((uint8_t)6)
#define 	PC7 							((uint8_t)7)
#define 	PC8 							((uint8_t)8)
#define 	PC9 							((uint8_t)9)
#define 	PC10 							((uint8_t)10)
#define 	PC11 							((uint8_t)11)
#define 	PC12 							((uint8_t)12)
#define 	PC13 							((uint8_t)13)
#define 	PC14 							((uint8_t)14)
#define 	PC15 							((uint8_t)15)


#define 	PD0 							((uint8_t)0)
#define 	PD1 							((uint8_t)1)
#define 	PD2 							((uint8_t)2)
#define 	PD3 							((uint8_t)3)
#define 	PD4 							((uint8_t)4)
#define 	PD5 							((uint8_t)5)
#define 	PD6 							((uint8_t)6)
#define 	PD7 							((uint8_t)7)
#define 	PD8 							((uint8_t)8)
#define 	PD9 							((uint8_t)9)
#define 	PD10 							((uint8_t)10)
#define 	PD11 							((uint8_t)11)
#define 	PD12 							((uint8_t)12)
#define 	PD13 							((uint8_t)13)
#define 	PD14 							((uint8_t)14)
#define 	PD15 							((uint8_t)15)





void extiBebin(GPIO_TypeDef * GPIOx, uint16_t pin, uint8_t edge_mode);
void extiActivation(uint16_t pin, void (*function_Interrupt)(void));
void attachInterrupt(GPIO_TypeDef * GPIOx, uint16_t pin, void (*function_Interrupt)(void), uint8_t edge_mode);




