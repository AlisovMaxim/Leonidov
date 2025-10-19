#include <stdint.h>
#include "main.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void EXTI15_10_IRQHandler()
{
	if(EXTI->PR & EXTI_PR_PR13)
	{
		delay(100000);
		GPIOA->ODR ^= GPIO_ODR_ODR5;
		EXTI->PR |= EXTI_PR_PR13;
	}
}

int main(void)
{
	//Тактирование A
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//PA5 на выход
	GPIOA->CRL &= ~GPIO_CRL_CNF5;
	GPIOA->CRL |= GPIO_CRL_MODE5;
	//Тактирование C
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
	//Настройка альтернативной функции на порт C
	AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI13_PC;
	//Настройка прерывания
	EXTI->IMR |= EXTI_IMR_MR13;
	EXTI->FTSR |= EXTI_FTSR_FT13;
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_SetPriority(EXTI15_10_IRQn, 0);

	for(;;)
	{

	}
}

void delay(uint32_t takts)
{
	for (uint32_t i=0; i<takts; i++);
}
