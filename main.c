#include "stm32l4xx.h"

void PORT_5_INIT (void)
	{
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

		
		GPIOB->MODER   &= GPIO_MODER_MODE5_0;;          
		GPIOB->MODER   |= ~GPIO_MODER_MODE5_1;
		GPIOB->OTYPER  &= ~GPIO_OTYPER_OT5;
		GPIOB->OSPEEDR &= GPIO_OSPEEDER_OSPEEDR5_0;
		GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_1;
		GPIOB->PUPDR   &= GPIO_PUPDR_PUPD5_0;
		GPIOB->PUPDR   &= GPIO_PUPDR_PUPD5_1;
			
		
	}

int main (void)
{
	PORT_5_INIT();
	
	while(1)
	{
		
		GPIOB->BSRR |=GPIO_BSRR_BS5;
		GPIOB->BSRR |=GPIO_BSRR_BR5;

	}
}







