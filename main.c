#include "stm32l4xx.h"

//#define SYSLOCK    80000000U                 // макрос максимальной системной частоты

#define TIM_EnableIT_UPDATE(TIMx) TIMx->DIER |= TIM_DIER_UIE  // Макрос разрешения прерывания
#define TIM_EnableCounter(TIMx)   TIMx->CR1 |= TIM_CR1_CEN     // Макрос включения таймера

#define PIN_B5_ON()   GPIOB->BSRR |=GPIO_BSRR_BS5;       // включить пин B5
#define PIN_B5_OFF()  GPIOB->BSRR |=GPIO_BSRR_BR5;       // выключить пин B5


static void TIM3_Init (void)
	{
		RCC->APB1ENR1  |=  RCC_APB1ENR1_TIM3EN;
		NVIC_EnableIRQ (TIM3_IRQn);
		WRITE_REG(TIM3->PSC, 7999);                          // задаем количество тактов за 1 секунду
		WRITE_REG(TIM1->ARR, 10000);                         // 
	}




__IO uint32_t SysTick_CNT = 0;


////////void SetSysClockTo80(void)
////////{
////////	
////////	/* Enable Prefetch Buffer  */
////////	FLASH->ACR &= ~FLASH_ACR_LATENCY;
////////	FLASH->ACR |= FLASH_ACR_LATENCY_4WS;	
////////	
////////	/* Enable HSI */
////////	RCC->CR |= RCC_CR_HSION;
////////	
////////	/* wait till HSI is ready  */	
////////	//while(READ_BIT(RCC->CR, RCC_CR_HSIRDY == RESET));
////////	while(!(RCC->CR & RCC_CR_HSIRDY));
////////	
////////	/* Configure AHB PRESCALARS HCLK  */
////////	RCC->CFGR  &= ~RCC_CFGR_HPRE;
////////	RCC->CFGR  |=  RCC_CFGR_HPRE_DIV1;
////////	
////////	/* Configure AHB1 PRESCALARS */
////////	RCC->CFGR  |=  RCC_CFGR_PPRE1_DIV1;
////////	
////////	/* Configure AHB2 PRESCALARS */
////////	RCC->CFGR  |=  RCC_CFGR_PPRE2_DIV1;
////////	
////////	/* Configure MAIN PLL  */
////////	//RCC->CR &= RCC_CR_PLLON;
////////	RCC->PLLCFGR &=  (RCC_PLLCFGR_PLLM);
////////	
////////	RCC->PLLCFGR &=  ~RCC_PLLCFGR_PLLN;
////////	RCC->PLLCFGR |=  (RCC_PLLCFGR_PLLN_1 | RCC_PLLCFGR_PLLN_3);
////////	
////////	RCC->PLLCFGR |=  RCC_PLLCFGR_PLLSRC_HSI;
////////	RCC->PLLCFGR &=  ~RCC_PLLCFGR_PLLR;	
////////	
////////	/* Enable PLLCLK  */
////////	RCC->PLLCFGR  |=  RCC_PLLCFGR_PLLREN;
////////	
////////	
////////	/* Enable the PLL and for it to become ready  */
////////	RCC->CR |=  RCC_CR_PLLON;
////////	while (!(RCC->CR & RCC_CR_PLLRDY));
////////	
////////	/* Select the Clock Source and wait for it to be set  */
////////	RCC->CFGR  |=  RCC_CFGR_SW_PLL;
////////	
////////	/* Wait till PLL is used as clock source  */
////////		while(!(RCC->CFGR & RCC_CFGR_SWS));
////////}


void SysTick_Init(void)
{
	SysTick->LOAD &= ~SysTick_LOAD_RELOAD_Msk;
	SysTick->LOAD = 80000000/1000-1;
	SysTick->VAL  &= ~SysTick_VAL_CURRENT_Msk;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void)
{
	if (SysTick_CNT > 0) SysTick_CNT--;
	
}

void delay_ms (uint32_t ms)
{
	SysTick->VAL &= ~SysTick_VAL_CURRENT_Msk;
	SysTick->VAL = 80000000/1000-1;
	SysTick_CNT = ms;
	while(SysTick_CNT);
	
}	


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
	//SetSysClockTo80();
	PORT_5_INIT();
	SysTick_Init();
	
	TIM3_Init();
	TIM_EnableIT_UPDATE(TIM3);
	TIM_EnableCounter(TIM3);
	
	
	while(1)
	{
		
	}
}


void TIM3_IRQHandler(void)
	{
		if (READ_BIT(TIM3->SR, TIM_SR_UIF))
		{
			
		}
	}







