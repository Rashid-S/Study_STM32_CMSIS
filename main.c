#include "stm32l4xx.h"

#define PIN_B5_ON()   GPIOB->BSRR |=GPIO_BSRR_BS5;       // включить пин B5
#define PIN_B5_OFF()  GPIOB->BSRR |=GPIO_BSRR_BR5;       // выключить пин B5


void PORT_C13_INIT (void)
	{
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
		
		GPIOC->MODER  &= ~(GPIO_MODER_MODE13_0 | GPIO_MODER_MODE13_1);
		GPIOC->PUPDR  &=  GPIO_PUPDR_PUPD13_0;
		GPIOC->PUPDR  |=  GPIO_PUPDR_PUPD13_1;
		GPIOC->BSRR   |=  GPIO_BSRR_BR13;
	}	


void PORT_B5_INIT (void)
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
	PORT_C13_INIT();
	PORT_B5_INIT();

	
	while(1)
	{
		if ((GPIOC->IDR  &  GPIO_IDR_ID13) == 0)
			{
				PIN_B5_ON();
			}
		else
			{
				PIN_B5_OFF();
			}
	}
}




