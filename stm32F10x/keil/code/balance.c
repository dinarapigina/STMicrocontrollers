////#include "stm32f10x_mpu6050.h"
////#include "stm32f10x_tb6612fng.h"  
//#include "stm32f10x.h"                  // Device header
//#include "math.h"


////void tim4Begin(void)
////{
////	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
////	TIM4->PSC = 720 - 1;
////	TIM4->ARR = 1000;
////	TIM4->DIER |= TIM_DIER_UIE; 
////	TIM4->CR1  |=	TIM_CR1_CEN; 
////	NVIC_EnableIRQ(TIM4_IRQn);	
////}

////uint8_t flagTimer=1;

////void TIM4_IRQHandler(void) // обработчик флага 
////{	
////	TIM4->SR &=~TIM_SR_UIF; 
////  flagTimer =0;
////}


//int main()
//{	
//	
//	//tim4Begin();
////	tb6612fngBegin();
//  
//	//i2cBegin();
//	//mpu6050Begin();
//	
//	
//	float gyro_accel[6];
//	float volatile accel_angle;
//	float volatile angle;
//	float volatile dt = 0.01; // (72000000/7200*100) = 0.01
//	float volatile FK = 0.1; // коэффициент комплементарного фильтра
//	//float volatile step = 0;
//	
//	while(1)
//	{

////			if(flagTimer == 0)
////			{
//////			  flagTimer = 1;
//////				mpu6050Read(gyro_accel);
//////	
//////				if(gyro_accel[AZ] != 0)
//////				accel_angle = RAD*atan(gyro_accel[AY]/gyro_accel[AZ]);
//////				 
//////				angle = (1 - FK)*(angle + gyro_accel[GX]*dt) + FK * accel_angle;
//////				
//////				GPIOA->ODR ^= GPIO_ODR_ODR10;
////			  //step = encoderRead();
////			}
////		
//	}

//}

int main()
{

	while(1){}

}
