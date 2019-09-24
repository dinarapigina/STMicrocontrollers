#include "stm32f10x_i2c.h"

uint32_t  volatile systemCounter = 0; 

void SysTick_Handler(void) 
{
	  systemCounter++;
	  if(systemCounter > 100)
		{
	  	 NVIC_SystemReset();
			 systemCounter = 0;
		}	
}

void SysTickBegin(uint32_t times)
{
	  SysTick->LOAD = times;
		SysTick->VAL  = times;
		SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
}

void i2cBegin(void)
{	
	
	  //SysTickBegin(72000000);
		
	  //�������� ������������ ������ � ������ I2C

	  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // �������� ������������ ����� B
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // �������� ������������ I2C1
		RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // �������� ������������ �������������� �������
		
		// �������� PB6 - SCL

	  GPIOB->CRL &= ~GPIO_CRL_MODE6;				// �������� ����
		GPIOB->CRL |= GPIO_CRL_MODE6_1;				// Output mode, speed 2 MHz (10)
		
		GPIOB->CRL &= ~GPIO_CRL_CNF6;					// �������� ����
		GPIOB->CRL |= GPIO_CRL_CNF6;					// Alternate function output Open-drain (11)
			
		// �������� PB7 - SDA
		GPIOB->CRL &= ~GPIO_CRL_MODE7;				// �������� ����
		GPIOB->CRL |= GPIO_CRL_MODE7_1;				// Output mode, speed 2 MHz (10)
		
		GPIOB->CRL &= ~GPIO_CRL_CNF7;					// �������� ����
		GPIOB->CRL |= GPIO_CRL_CNF7;					// Alternate function output Open-drain (11)
		
		//����������� ������ � ����� I2C
		
		// ��������� ���������� ������ I2C-��������� ��
		I2C1->CR2 =   0x18;   		 // ������� ������������ ������ 24���
		I2C1->CCR =   0x1E;        // ������� SCL 400�, ������ �������� 0x3C,
		I2C1->CCR &= ~I2C_CCR_FS;  // Standard mode
		I2C1->TRISE = 0x19;   		 // Rise time
		I2C1->CR1 |= I2C_CR1_ACK;  // �������� �������������
		I2C1->OAR1 = 0x10;          // ����������� �����
		I2C1->CR1 |= I2C_CR1_PE;   // �������� ���������		
	
}

void i2cReceiver(uint8_t addressWrite, uint8_t addressRead, uint8_t adress,uint8_t *buffer,uint8_t size)
{
		uint8_t i = 0x00;
		I2C1->CR1 |= I2C_CR1_ACK;
		I2C1->CR1 |= I2C_CR1_START;
		uint32_t timeOut = 0;
		while(!(I2C1->SR1 & I2C_SR1_SB)){if(timeOut == 7200000){NVIC_SystemReset();}timeOut++;};
		(void)I2C1->SR1;
		// ����� ����� ����������
		I2C1->DR = addressWrite;
		
		while(!(I2C1->SR1 & I2C_SR1_ADDR)){if(timeOut == 7200000){NVIC_SystemReset();}timeOut++;};;
		(void)I2C1->SR1;
		(void)I2C1->SR2;
		// ����� ����� ��������
		I2C1->DR = adress;
		
		while(!(I2C1->SR1 & I2C_SR1_TXE)){if(timeOut == 7200000){NVIC_SystemReset();}timeOut++;};;
		I2C1->CR1 |= I2C_CR1_START;
		while(!(I2C1->SR1 & I2C_SR1_SB));
		(void)I2C1->SR1;
		// ������ ������ � �������
		I2C1->DR = addressRead;
		
		while(!(I2C1->SR1 & I2C_SR1_ADDR)){if(timeOut == 7200000){NVIC_SystemReset();}timeOut++;};;
		(void)I2C1->SR1;
		(void)I2C1->SR2;
		
		if(size > 0x01)
		{
			size--;
			while(size--)
			{
				while(!(I2C1->SR1 & I2C_SR1_RXNE));
				buffer[i++] = I2C1->DR;
			}
		}
		while(!(I2C1->SR1 & I2C_SR1_BTF)){if(timeOut == 7200000){NVIC_SystemReset();}timeOut++;};
		I2C1->CR1 &= ~I2C_CR1_ACK;
		buffer[i++] = I2C1->DR;
		I2C1->CR1 |= I2C_CR1_STOP;
			
		systemCounter = 0;
		timeOut = 0;
}


/* ������� ������ � �������
 * ������� ���������: ����� ��������, ������ ��� ������
 */

void i2cTransmission(uint8_t registerSensor, uint8_t RegisterAddress, uint8_t dataWrite)
{

		I2C1->CR1 |= I2C_CR1_START;
		while (!(I2C1->SR1 & I2C_SR1_SB));
		(void)(I2C1->SR1);	//������� ������ �������� SR1

		// ����� ����� ����������
		I2C1->DR = registerSensor;
		while((!(I2C1->SR1 & (I2C_SR1_AF | I2C_SR1_ADDR)))){};
		(void)(I2C1->SR1);  //������� ������ �������� SR1
		(void)(I2C1->SR2);
		(void)(I2C1->SR2);	// �����! ����� ���������� ������ �������� SR2

		// ����� ����� ��������
		I2C1->DR = RegisterAddress;
		while (!(I2C1->SR1 & I2C_SR1_BTF));	 /* Byte Transfer Finished */

		// ����� ������ � �������
		I2C1->DR = dataWrite;
		while (!(I2C1->SR1 & I2C_SR1_BTF));  /* Byte Transfer Finished */
		
}

void i2cTransmissionByte(uint8_t registerSensor, uint8_t dataWrite)
{

		I2C1->CR1 |= I2C_CR1_START;
		while (!(I2C1->SR1 & I2C_SR1_SB));
		(void)(I2C1->SR1);	//������� ������ �������� SR1

		// ����� ����� ����������
		I2C1->DR = registerSensor;
		while((!(I2C1->SR1 & (I2C_SR1_AF | I2C_SR1_ADDR)))){};
		(void)(I2C1->SR1);  //������� ������ �������� SR1
		(void)(I2C1->SR2);
		(void)(I2C1->SR2);	// �����! ����� ���������� ������ �������� SR2

		// ����� ������ � �������
		I2C1->DR = dataWrite;
		while (!(I2C1->SR1 & I2C_SR1_BTF));  /* Byte Transfer Finished */
		
}

uint8_t i2cReceiverByte(uint8_t addressWrite, uint8_t addressRead, uint8_t adress)
{
		uint8_t data;

		I2C1->CR1 |= I2C_CR1_ACK;
		I2C1->CR1 |= I2C_CR1_START;

		while(!(I2C1->SR1 & I2C_SR1_SB));
		(void)I2C1->SR1;
		// ����� ����� ����������
		I2C1->DR = addressWrite;
		
		while(!(I2C1->SR1 & I2C_SR1_ADDR));
		(void)I2C1->SR1;
		(void)I2C1->SR2;
		// ����� ����� ��������
		I2C1->DR = adress;
		
		while(!(I2C1->SR1 & I2C_SR1_TXE));
		I2C1->CR1 |= I2C_CR1_START;
		while(!(I2C1->SR1 & I2C_SR1_SB));
		(void)I2C1->SR1;
		// ������ ������ � �������
		I2C1->DR = addressRead;
		
		while(!(I2C1->SR1 & I2C_SR1_ADDR));
		(void)I2C1->SR1;
		(void)I2C1->SR2;
		I2C1->CR1 |= I2C_CR1_STOP;
		I2C1->CR1 &= ~I2C_CR1_ACK;
		while(!(I2C1->SR1 & I2C_SR1_RXNE));
		data = I2C1->DR;
		return data;

}

