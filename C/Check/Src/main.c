#include <stdint.h>
#include "main.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//PA5 на выход
	GPIOA->CRL &= ~GPIO_CRL_CNF5;
	GPIOA->CRL |= GPIO_CRL_MODE5;
	for(;;)
	{
		GPIOA->ODR ^= GPIO_ODR_ODR5;
		delay(500000);
	}
}

void delay(uint32_t ticks)
{
	for (uint32_t i=0; i<ticks; i++);
}
