#include "stm32l4xx.h"

//#define SYSLOCK    80000000U  // макрос максимальной системной частоты при тактировании от HSI

#define TIM_EnableIT_UPDATE(TIMx) TIMx->DIER |= TIM_DIER_UIE  // Макрос разрешения прерывания
#define TIM_EnableCounter(TIMx)   TIMx->CR1 |= TIM_CR1_CEN     // Макрос включения таймера

#define PIN_B5_ON()   GPIOB->BSRR |=GPIO_BSRR_BS5;       // включить пин B5
#define PIN_B5_OFF()  GPIOB->BSRR |=GPIO_BSRR_BR5;       // выключить пин B5


//----- Инициализация таймера TIM3 -------------
// @note - Тактирование производится от MSI с частотой 4МГц
static void TIM3_Init (void)
	{
		RCC->APB1ENR1  |=  RCC_APB1ENR1_TIM3EN;       // включаем тактирование таймера от шины APB1
		NVIC_EnableIRQ (TIM3_IRQn);                   // разрешаем глобальное прерывание для таймера
		WRITE_REG(TIM3->PSC, 7999);                   // задаем делителем какое количество тактов должно быть за 1 секунду
		WRITE_REG(TIM3->ARR, 500);                  // задаем длительность в 1 секунду
	}


__IO uint32_t SysTick_CNT = 0;
__IO uint8_t tim3_cnt	    = 0;



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

// ---------- Обработчик прерывания ---------------
void TIM3_IRQHandler(void)
	{
		if (READ_BIT(TIM3->SR, TIM_SR_UIF))
		{
			CLEAR_BIT(TIM3->SR, TIM_SR_UIF);
			
			switch(tim3_cnt)
			{
				case 0: PIN_B5_ON(); break;
				case 1: PIN_B5_OFF(); break;
			}
			
			tim3_cnt++;
			if (tim3_cnt > 5) 
			{
				tim3_cnt = 0;
			}
		}
	}







