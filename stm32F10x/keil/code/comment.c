
//float encoderReadInterrupt(void);
//void encoderLeftOne();
//void encoderLeftTwo();
//void encoderRightOne();
//void encoderRightTwo();
//#include "stm32f10x_exti.h"  
//#define lengthPulseInterrupt (float)(0.0007025084745)  // = R*2*pi/pulse_per_round = 33*2*3.14/295 = 0.174886 mm (R=33mm)

//		attachInterrupt(GPIOA,PA6,encoderLeftOne,RISING);
//		attachInterrupt(GPIOA,PA7,encoderLeftTwo,RISING);
//		attachInterrupt(GPIOA,PA8,encoderRightOne,RISING);
//		attachInterrupt(GPIOA,PA9,encoderRightTwo,RISING);

//int32_t volatile encoderLeftInterrupt = 0;
//int32_t volatile encoderRightInterrupt = 0;

//void encoderLeftOne()
//{
//	if(GPIOA->IDR & GPIO_IDR_IDR7)
//		{
//			encoderLeftInterrupt--;
//		}	
//}
//void encoderLeftTwo()
//{
//	if(GPIOA->IDR & GPIO_IDR_IDR6)
//	{
//		encoderLeftInterrupt++;
//	}	
//}
//void encoderRightOne()
//{
//	if(GPIOA->IDR & GPIO_IDR_IDR9)
//	{
//		encoderRightInterrupt++;
//	}	
//}
//void encoderRightTwo()
//{
//	if(GPIOA->IDR & GPIO_IDR_IDR8)
//	{
//		encoderRightInterrupt--;
//	}
//}

//float encoderReadInterrupt(void)
//{
//	
//	float encoderPositionLeft;
//	float encoderPositionRight;
//	float encoderPositionCenter;
//	
//	encoderPositionLeft = encoderLeftInterrupt * lengthPulseInterrupt;
//  encoderPositionRight = encoderRightInterrupt * lengthPulseInterrupt;
//  encoderPositionCenter = 0.5*(encoderPositionLeft + encoderPositionRight); 
//   
//	return encoderPositionCenter;
//}





//		{if(timeOutFlag == 10000){NVIC_SystemReset();}timeOutFlag++;}

//		{
//			if(timeOutFlag == 10000)
//			{
//				NVIC_SystemReset();
//			}
//			timeOutFlag++;		
//		}

//void watchdocBegin(void)
//{
//	RCC->APB1ENR|=1<<11;
//	WWDG->CFR&=0xFC00;
//	WWDG->CFR|=0<<9|3<<7|0x5F;
//	
//	WWDG->CR|=1<<7;
//	WWDG->SR=0;
//	
//	NVIC->ISER[WWDG_IRQn/32]=1<<WWDG_IRQn;
//	NVIC->IP[WWDG_IRQn]=0x50;
//	
//	WWDG->CFR|=1<<9;
//}

//void WWDG_IRQHandler(void)
//{
//	WWDG->CR |= 0x7F;
//	WWDG->SR=0;	
//	GPIOC->ODR ^= GPIO_ODR_ODR13;
//for(uint32_t i=0;i<240000;i++);	
//}

//		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
//		GPIOC->CRH   &=~ (GPIO_CRH_CNF13 | GPIO_CRH_MODE13 );
//		GPIOC->CRH   |=   GPIO_CRH_MODE13 ;
	
//GPIOC->ODR ^= GPIO_ODR_ODR13;		
//	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
//	GPIOA->CRH &=~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);	
//	GPIOA->CRH |= GPIO_CRH_MODE10_1;
//GPIOA->ODR ^= GPIO_ODR_ODR10;
			
//	encoderPositionDifferential = (encoderRead() - encoderPositionCenterOld)/0.01;	
//		
//	encoderPosition = 0.95*(encoderPosition) + 0.05*encoderPositionDifferential;
//	
//	encoderPositionCenterOld = encoderRead();
//	
//	PWM = PWM_value_scale*(k1*(filter_angle - offset_angle) + k2*GYRO_XANGLE + k3*encoderRead() + k4*encoderPosition);

//  float volatile encoderPositionCenterOld = 0;
//	float volatile encoderPositionDifferential = 0;
//	float volatile encoderPosition = 0;
//	uint8_t PWM;

// GPIOA->ODR ^= GPIO_ODR_ODR10;
//	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
//	GPIOA->CRH &=~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);	
//	GPIOA->CRH |= GPIO_CRH_MODE10;
//		
//    encoderPositionCenterOld =  encoderRead();
//		
//		forwards(80,80);
//    for(uint32_t i=0;i<2400000;i++);	
//	  forwards(0,0);


//	float volatile encoderPositionCenterOld;
//	float encoderPositionDifferential;
//	float dt = 0.02;

//			if (GYRO_XANGLE > 2)
//			{
//				forwards(120,120);
//				
//			}
//			else if (GYRO_XANGLE < -2)
//			{
//				backward(120,120);
//				
//			}
//			else 
//			{
//				 stop();
//				 for(int i=0;i<60000;i++){}; 
//			}
		

//    newAngle = atan2(-(float)MPU6050_ACCEL_XOUT, (float)MPU6050_ACCEL_ZOUT) + 3.14;  

//		ANGLE =  comp_filter(newAngle,-MPU6050_GYRO_YOUT,time);

//		
//		ACCEL_XANGLE = RAD*atan((float)- MPU6050_ACCEL_XOUT/sqrt(pow((float)MPU6050_ACCEL_YOUT,2)+pow((float)MPU6050_ACCEL_ZOUT,2)));
//		ACCEL_YANGLE = RAD*atan((float)- MPU6050_ACCEL_YOUT/sqrt(pow((float)MPU6050_ACCEL_XOUT,2)+pow((float)MPU6050_ACCEL_ZOUT,2)));
//		ACCEL_ZANGLE = RAD*atan((float)- MPU6050_ACCEL_ZOUT/sqrt(pow((float)MPU6050_ACCEL_XOUT,2)+pow((float)MPU6050_ACCEL_YOUT,2)));
//		
//			

//				encoder2 = TIM3->CNT;
//			  encoder1 = TIM1->CNT;

//		  if (encoder2 < 20)
//			{
//					4
//					for(uint32_t i=0;i<240000;i++);	
//			
//			}
//			if (encoder2 > 0)
//			{
//					GPIOA->BSRR = (GPIO_BSRR_BR2);
//					GPIOA->BSRR = (GPIO_BSRR_BR5);
//					GPIOA->BSRR = (GPIO_BSRR_BS3);
//					GPIOA->BSRR = (GPIO_BSRR_BS4);
//					for(uint32_t i=0;i<240000;i++);
//			
//			}
//		



//			GPIOA->BSRR = (GPIO_BSRR_BS2);
//		  GPIOA->BSRR = (GPIO_BSRR_BS5);
//		  GPIOA->BSRR = (GPIO_BSRR_BR4);
//		  GPIOA->BSRR = (GPIO_BSRR_BR3);
//			for(uint32_t i=0;i<2400000;i++);	
//			GPIOA->BSRR = (GPIO_BSRR_BR2);
//		  GPIOA->BSRR = (GPIO_BSRR_BR5);
//		  GPIOA->BSRR = (GPIO_BSRR_BS3);
//		  GPIOA->BSRR = (GPIO_BSRR_BS4);
//			for(uint32_t i=0;i<2400000;i++);	
//		
//			GPIOA->BSRR = (GPIO_BSRR_BS2);
//			for(uint32_t i=0;i<240000;i++);	
//			GPIOA->BSRR = (GPIO_BSRR_BR2);
//			for(uint32_t i=0;i<240000;i++);		
		
//			GPIOA->BSRR = (GPIO_BSRR_BS3);
//			for(uint32_t i=0;i<240000;i++);	
//			GPIOA->BSRR = (GPIO_BSRR_BR3);
//			for(uint32_t i=0;i<240000;i++);	
//				
//			GPIOA->BSRR = (GPIO_BSRR_BS4);
//			for(uint32_t i=0;i<2400000;i++);	
//			GPIOA->BSRR = (GPIO_BSRR_BR4);
//			for(uint32_t i=0;i<2400000;i++);	
//			
//		  GPIOA->BSRR = (GPIO_BSRR_BS5);
//			for(uint32_t i=0;i<2400000;i++);	
//			GPIOA->BSRR = (GPIO_BSRR_BR5);
//			for(uint32_t i=0;i<2400000;i++);	