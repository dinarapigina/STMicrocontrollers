#include "stm32f10x.h"
#include "stm32f10x_watchdog.h" 

void resetSystem(void)
{
	 NVIC_SystemReset();
} 

void watchdocBegin(void)
{
	//NVIC->ISER[0] |= NVIC_ISER_SETENA_0;// ������������� ����������
//	RCC->APB1ENR |= RCC_APB1ENR_WWDGEN; // �������� ������������ WWDG
//	WWDG->CFR |= WWDG_CFR_WDGTB0; // ������ ������� ������������ WWDG
//	WWDG->CFR |= 0x41; // ������ ����
//	WWDG->CR |= 0x7F; // ��������� ������ WWDG � ���������� ���������
//	WWDG->SR &=~WWDG_SR_EWIF; // �������� ���� EWI
//	//WWDG->CFR |=WWDG_CFR_EWI; // ��������� ����������
//	
//	NVIC_EnableIRQ(WWDG_IRQn);
	
	RCC->APB1ENR|= RCC_APB1ENR_WWDGEN; 	//??wwdg??
	NVIC->ISER[0] |= NVIC_ISER_SETENA_0;
	// Basic Configure
	WWDG->CFR |= (11)<<7;
	WWDG->CFR |= 0x7f;       // 7-bit window value
	WWDG->CR  |= 0x7f; 			 // 7-bit reload value 
	WWDG->CR  |= 1<<7; 
	// interrupt configure
	WWDG->SR = 0x00;
	WWDG->CFR |= 1<<9; 	// Early wakeup interrupt
	WWDG->CFR |=WWDG_CFR_EWI;
	NVIC_EnableIRQ(WWDG_IRQn);
	// Enable 
	
}

void WWDG_IRQHandler(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &=~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);	
	GPIOC->CRH |= GPIO_CRH_MODE8_1;
	GPIOC->BSRR = GPIO_BSRR_BS8;
//	
	WWDG->CR |= 0x7F; // �������� �������� ������� WWDG
	WWDG->SR &=~WWDG_SR_EWIF; // �������� ���� EWI
	
		// Trun on write permission: KR +SR
//	IWDG->KR = 0x5555;
//	IWDG->SR = 0<<0;
//	IWDG->SR = 0<<1;
//	IWDG->SR = 0<<2;
//	
//	// IWDG Control
//	IWDG->PR = 1<<2; 		// 4 div
//	IWDG->RLR = 0x1f4;  // 12 bits
//	IWDG->KR = 0xAAAA;
//	IWDG->KR = 0xCCCC;
	
	

}
// ������� ������� ����������� ������� WWDG
void watchdocStart(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_WWDGEN; // �������� ������������ WWDG
	WWDG->CR |= 0x7F; // �������� �������� ������� WWDG
	WWDG->SR &=~WWDG_SR_EWIF; // �������� ���� EWI
}
// ������� �������� ����������� ������� WWDG
void watchdocStop(void)
{
		RCC->APB1ENR |= RCC_APB1RSTR_WWDGRST; // ��������� ������������ WWDG
}


int main()
{
	watchdocBegin();

	while(1)
	{
	
	}

}

