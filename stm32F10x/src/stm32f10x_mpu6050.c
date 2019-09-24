#include "stm32f10x_mpu6050.h"

void mpu6050Begin(void)
{
	/* Start I2C interface */
	i2cBegin(); 
	
	/* Config sensor */
	i2cTransmission(AddressWrite, MPU6050_RA_PWR_MGMT_1, 0x80); 
	
	for(int i=0;i<240000;i++){};                           
		
	i2cTransmission(AddressWrite, MPU6050_RA_PWR_MGMT_1, 0x01);  
	i2cTransmission(AddressWrite, MPU6050_RA_CONFIG , 0x01);
	i2cTransmission(AddressWrite,MPU6050_RA_SMPLRT_DIV, 0x01);  

	/* Config accelerometer */
	uint8_t dataRegisterConfig;
	dataRegisterConfig = i2cReceiverByte(0xD0,0xD1,MPU6050_RA_ACCEL_CONFIG);
	dataRegisterConfig = (dataRegisterConfig & 0xE7) | (uint8_t)(0x03 << 0); 
	i2cTransmission(AddressWrite, MPU6050_RA_ACCEL_CONFIG, dataRegisterConfig );

	/* Config gyroscope */
	dataRegisterConfig = i2cReceiverByte(0xD0,0xD1,MPU6050_RA_GYRO_CONFIG);
	dataRegisterConfig = (dataRegisterConfig & 0xE7) | (uint8_t)(0x03 << 0); 
	i2cTransmission(AddressWrite, MPU6050_RA_ACCEL_CONFIG,dataRegisterConfig);	
}

void tim4Begin(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4->PSC = (SystemCoreClock/100000 - 1); 
	TIM4->ARR = 1000;
	TIM4->DIER |= TIM_DIER_UIE; 
	TIM4->CR1  |=	TIM_CR1_CEN; 
	NVIC_EnableIRQ(TIM4_IRQn);	
}
  
  float volatile accel_angle;
	float volatile filter_angle;
	float volatile angle_encoder;
	float volatile encoderPositionOld = 0;
	float volatile PWM;
	float volatile K1 = 23;     
	float volatile K2 = 0.3;     
	float volatile K3 = 5;     
	float volatile K4 = 18;  
	float volatile K5 = 90;
  float volatile distance = 0;
	

void TIM4_IRQHandler(void)
{	
 	TIM4->SR &=~TIM_SR_UIF; 
	
	double volatile gyro_accel[6];
	uint8_t AccelGyroBuffer[14];
	int16_t  MPU6050_ACCEL_XOUT;
	int16_t  MPU6050_ACCEL_YOUT;
	int16_t  MPU6050_ACCEL_ZOUT;
	int16_t  MPU6050_TEMP;
	int16_t  MPU6050_GYRO_XOUT;
	int16_t  MPU6050_GYRO_YOUT;
	int16_t  MPU6050_GYRO_ZOUT;
	
	i2cReceiver(0xD0,0xD1,MPU6050_RA_ACCEL_XOUT_H,AccelGyroBuffer,14);

	MPU6050_ACCEL_XOUT = ((AccelGyroBuffer[0] << 8) | AccelGyroBuffer[1]);
	gyro_accel[0] = MPU6050_ACCEL_XOUT/MPU6050_ACCE_SENS_2; 

	MPU6050_ACCEL_YOUT = ((AccelGyroBuffer[2] << 8) | AccelGyroBuffer[3]);
	gyro_accel[1]= MPU6050_ACCEL_YOUT/MPU6050_ACCE_SENS_2; 

	MPU6050_ACCEL_ZOUT = ((AccelGyroBuffer[4] << 8) | AccelGyroBuffer[5]);
	gyro_accel[2] = MPU6050_ACCEL_ZOUT/MPU6050_ACCE_SENS_2; 

	MPU6050_TEMP = (((AccelGyroBuffer[6] << 8) | AccelGyroBuffer[7]));
	MPU6050_TEMP /= 340;
	MPU6050_TEMP += 36.53;

	MPU6050_GYRO_XOUT = ((AccelGyroBuffer[8]  << 8) | AccelGyroBuffer[9]);
	gyro_accel[3] = MPU6050_GYRO_XOUT/MPU6050_GYRO_SENS_250;

	MPU6050_GYRO_YOUT = ((AccelGyroBuffer[10] << 8) | AccelGyroBuffer[11]);
	gyro_accel[4] = MPU6050_GYRO_YOUT/MPU6050_GYRO_SENS_250;
	
	MPU6050_GYRO_ZOUT = ((AccelGyroBuffer[12] << 8) | AccelGyroBuffer[13]);
	gyro_accel[5] = MPU6050_GYRO_ZOUT/MPU6050_GYRO_SENS_250;

	if(gyro_accel[AZ] != 0)
	accel_angle = atan(gyro_accel[AY]/gyro_accel[AZ]);
		
	filter_angle = (1 - FK)*(filter_angle + DEGRAD*gyro_accel[GX]*dt) + FK * accel_angle;
  
	angle_encoder = (1 - FE)*(angle_encoder) + FE * (encoderRead() - encoderPositionOld)/dt;
	
 	encoderPositionOld = encoderRead();
	
	PWM = K5*(K1*(filter_angle) + K2*DEGRAD*gyro_accel[GX] + K3*(encoderRead() + distance) + K4*angle_encoder);
  
	motor(-PWM);	
		
}

int main()
{	
	
	mpu6050Begin();
	tim4Begin();
	tb6612fngBegin(); 
		
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRH &=~(GPIO_CRH_MODE11 | GPIO_CRH_CNF11);	
	GPIOA->CRH |= GPIO_CRH_MODE11_1;
	
//	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
//	GPIOB->CRL &=~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);	
//	GPIOB->CRL |=  GPIO_CRL_CNF0_1;	
		
	while(1)
	{

		GPIOA->BSRR = GPIO_BSRR_BS11;
		for(int i=0;i<7200000;i++){};   
		GPIOA->BSRR = GPIO_BSRR_BR11;
		for(int i=0;i<7200000;i++){}; 
	
	}

}


   
 