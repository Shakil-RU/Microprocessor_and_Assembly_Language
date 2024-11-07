/*#include "stm32f10x.h"

void SystemClock_Config(void);
void GPIO_Init(void);
void Delay(volatile uint32_t s);

int main(void)
{
    // Initialize the system clock
    SystemClock_Config();

    // Initialize GPIO
    GPIO_Init();

    // Main loop
    while (1)
    {
        //Set PC13 (turn on LED)
        GPIOC->BSRR = GPIO_BSRR_BS13;
        Delay(7200000); // Approximately 1 second delay

        // Reset PC13 (turn off LED)
        GPIOC->BSRR = GPIO_BSRR_BR13;
        Delay(7200000); // Approximately 1 second delay
    }
}

void SystemClock_Config(void)
{
	
    // Enable HSE oscillator
	  RCC->CR |= RCC_CR_HSEON;
	  while (!(RCC->CR & RCC_CR_HSERDY)); // Wait till HSE is ready

    // Set PLL source to HSE and multiply by 9 (8 MHz HSE * 9 = 72 MHz)
    RCC->CFGR |= RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9;

    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY)); // Wait till PLL is ready

    // Select PLL as system clock source
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // Wait till PLL is used as system clock source

    // Set the AHB prescaler to 1
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

    // Set the APB1 prescaler to 2 (because APB1 clock must be = 36 MHz)
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

    // Set the APB2 prescaler to 1
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
}

void GPIO_Init(void)
{
    // Enable clock for GPIOC
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // Configure PC13 as General purpose output push-pull
    GPIOC->CRH &= ~GPIO_CRH_MODE13; // Clear mode bits for PC13
    GPIOC->CRH |= GPIO_CRH_MODE13_1; // Output mode, max speed 2 MHz
    GPIOC->CRH &= ~GPIO_CRH_CNF13; // General purpose output push-pull
}

void Delay(volatile uint32_t s)
{
    for (s; s>0; s--);
}
*/



/*
#define RCC_BASE        0x40021000
#define GPIOC_BASE      0x40011000

#define RCC_CR          (*(volatile unsigned int *)(RCC_BASE + 0x00))
#define RCC_CFGR        (*(volatile unsigned int *)(RCC_BASE + 0x04))
#define RCC_APB2ENR     (*(volatile unsigned int *)(RCC_BASE + 0x18)) // Pointer to APB2 peripheral clock enable register

#define RCC_APB2ENR_IOPCEN (1 << 4) // Bit 4 IOPCEN: IO port C clock enable

#define GPIOC_CRL       (*(volatile unsigned int *)(GPIOC_BASE + 0x00)) // This is not used
#define GPIOC_CRH       (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_IDR       (*(volatile unsigned int *)(GPIOC_BASE + 0x08)) // Not used
#define GPIOC_ODR       (*(volatile unsigned int *)(GPIOC_BASE + 0x0C)) // Not used
#define GPIOC_BSRR      (*(volatile unsigned int *)(GPIOC_BASE + 0x10))
#define GPIOC_BRR       (*(volatile unsigned int *)(GPIOC_BASE + 0x14)) // Not used

#define RCC_CR_HSEON    (1 << 16)
#define RCC_CR_HSERDY   (1 << 17)
#define RCC_CR_PLLON    (1 << 24)
#define RCC_CR_PLLRDY   (1 << 25)

#define RCC_CFGR_SW_PLL (2 << 0)
#define RCC_CFGR_SWS_PLL (2 << 2)
#define RCC_CFGR_PLLSRC (1 << 16)
#define RCC_CFGR_PLLMULL9 (7 << 18)
#define RCC_CFGR_HPRE_DIV1 (0 << 4)
#define RCC_CFGR_PPRE1_DIV2 (4 << 8)
#define RCC_CFGR_PPRE2_DIV1 (0 << 11)
#define RCC_CFGR_SWS      (3 << 2)

#define GPIO_CRH_MODE13 (3 << 20) // To clear the mode bit
#define GPIO_CRH_MODE13_1 (1 << 21) // 10 for Output mode, max speed 2 MHz
#define GPIO_CRH_CNF13 (3 << 22)
#define GPIO_BSRR_BS13 (1 << 13)
#define GPIO_BSRR_BR13 (1 << 29)

void SystemClock_Config(void);
void GPIO_Init(void);
void Delay(volatile unsigned int s);

int main(void)
{
    // Initialize the system clock
    //SystemClock_Config();

    // Initialize GPIO
    GPIO_Init();

    // Main loop
    while (1)
    {
        // Set PC13 (turn on LED)
        GPIOC_BSRR = GPIO_BSRR_BS13;
        Delay(7200000); // Approximately 1 second delay

        // Reset PC13 (turn off LED)
        GPIOC_BSRR = GPIO_BSRR_BR13;
        Delay(7200000); // Approximately 1 second delay
    }
}

void SystemClock_Config(void)
{
    // Enable HSE oscillator
    RCC_CR |= RCC_CR_HSEON;
    while (!(RCC_CR & RCC_CR_HSERDY)); // Wait till HSE is ready

    // Set PLL source to HSE and multiply by 9 (8 MHz HSE * 9 = 72 MHz)
    RCC_CFGR |= RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9;

    // Enable PLL
    RCC_CR |= RCC_CR_PLLON;
    while (!(RCC_CR & RCC_CR_PLLRDY)); // Wait till PLL is ready

    // Select PLL as system clock source
    RCC_CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC_CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // Wait till PLL is used as system clock source

    // Set the AHB prescaler to 1
    RCC_CFGR |= RCC_CFGR_HPRE_DIV1;

    // Set the APB1 prescaler to 2 (because APB1 clock must be = 36 MHz)
    RCC_CFGR |= RCC_CFGR_PPRE1_DIV2;

    // Set the APB2 prescaler to 1
    RCC_CFGR |= RCC_CFGR_PPRE2_DIV1;
}

void GPIO_Init(void)
{
    // Enable clock for GPIOC
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;

    // Configure PC13 as General purpose output push-pull
    GPIOC_CRH &= ~GPIO_CRH_MODE13; // Clear mode bits for PC13
    GPIOC_CRH |= GPIO_CRH_MODE13_1; // Output mode, max speed 2 MHz
    GPIOC_CRH &= ~GPIO_CRH_CNF13; // General purpose output push-pull
}

void Delay(volatile unsigned int s)
{
    for (; s > 0; s--);
}
*/



/*
#define RCC_BASE        0x40021000
#define GPIOC_BASE      0x40011000

#define RCC_APB2ENR     (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define RCC_CR					(*(volatile unsigned int *)(RCC_BASE + 0x00))
#define RCC_CFGR				(*(volatile unsigned int *)(RCC_BASE + 0x04))

#define GPIOC_CRH       (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR       (*(volatile unsigned int *)(GPIOC_BASE + 0x0C))

#define RCC_APB2ENR_IOPCEN (1 << 4)
#define RCC_CR_HSEON (1 << 16)
#define RCC_CR_HSERDY (1 << 17)
#define RCC_CR_PLLON (1 << 24)
#define RCC_CR_PLLRDY (1 << 25)
#define RCC_CFGR_PLLSRC (1 << 16)
#define RCC_CFGR_PLLMULL9 (7 << 18)
#define RCC_CFGR_SW_PLL (2 << 0)
#define RCC_CFGR_SWS_PLL (2 << 2)
#define RCC_CFGR_SWS (3 << 2)
#define RCC_CFGR_HPRE_DIV1 (0 << 4)
#define RCC_CFGR_PPRE2_DIV1 (0 << 11)
	
#define GPIO_CRH_MODE13 (3 << 20)
#define GPIO_CRH_MODE13_1 (1 << 21)
#define GPIO_CRH_CNF13 (3 << 22)
#define GPIO_ODR_PIN13_ON (1 << 13)

int main(void) {
	
	// Enable HSE oscillator
	RCC_CR |= RCC_CR_HSEON;
	while(!(RCC_CR & RCC_CR_HSERDY));
	
	// Set PLL source to HSE and multiply by 9 (8 MHz HSE * 9 = 72 MHz)
	RCC_CFGR |= RCC_CFGR_PLLSRC;
	RCC_CFGR |= RCC_CFGR_PLLMULL9;
	
	// Enable PLL
	RCC_CR |= RCC_CR_PLLON;
	while(!(RCC_CR & RCC_CR_PLLRDY));
	
	// Select PLL as system clock source
	RCC_CFGR |= RCC_CFGR_SW_PLL;
	while((RCC_CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
	
	// Set the AHB and APB2 prescaler to 1
	RCC_CFGR |= RCC_CFGR_HPRE_DIV1;
	RCC_CFGR |= RCC_CFGR_PPRE2_DIV1;
	
	RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;

  GPIOC_CRH &= ~GPIO_CRH_MODE13;
  GPIOC_CRH |= GPIO_CRH_MODE13_1;
  GPIOC_CRH &= ~GPIO_CRH_CNF13;
	
	while (1) {
		GPIOC_ODR |= GPIO_ODR_PIN13_ON;
		for(int i = 0; i < 720000; i++);
		
		GPIOC_ODR &= ~GPIO_ODR_PIN13_ON;
		for(int i = 0; i < 720000; i++);
	}
}*/




// Using Timer (TIM2)
/*#define RCC_BASE        0x40021000
#define GPIOC_BASE      0x40011000
#define TIM2_BASE				0x40000000

#define RCC_APB2ENR     (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define RCC_APB1ENR     (*(volatile unsigned int *)(RCC_BASE + 0x1C))
#define RCC_CR					(*(volatile unsigned int *)(RCC_BASE + 0x00))
#define RCC_CFGR				(*(volatile unsigned int *)(RCC_BASE + 0x04))

#define GPIOC_CRH       (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR       (*(volatile unsigned int *)(GPIOC_BASE + 0x0C))
	
#define TIM2_CR1				(*(volatile unsigned int *)(TIM2_BASE + 0x00))
#define TIM2_PSC        (*(volatile unsigned int *)(TIM2_BASE + 0x28))
#define TIM2_ARR        (*(volatile unsigned int *)(TIM2_BASE + 0x2C))
#define TIM2_SR         (*(volatile unsigned int *)(TIM2_BASE + 0x10))
	
#define TIM2_CR1_CEN (1 << 0)

#define RCC_APB2ENR_IOPCEN (1 << 4)
#define RCC_APB1ENR_TIM2EN (1 << 0)

#define RCC_CR_HSEON (1 << 16)
#define RCC_CR_HSERDY (1 << 17)
#define RCC_CR_PLLON (1 << 24)
#define RCC_CR_PLLRDY (1 << 25)
#define RCC_CFGR_PLLSRC (1 << 16)
#define RCC_CFGR_PLLMULL9 (7 << 18)
#define RCC_CFGR_SW_PLL (2 << 0)
#define RCC_CFGR_SWS_PLL (2 << 2)
#define RCC_CFGR_SWS (3 << 2)
#define RCC_CFGR_HPRE_DIV1 (0 << 4)
#define RCC_CFGR_PPRE2_DIV1 (0 << 11)
#define RCC_CFGR_PPRE1_DIV2 (1 << 10)
	
#define GPIO_CRH_MODE13 (3 << 20)
#define GPIO_CRH_MODE13_1 (1 << 21)
#define GPIO_CRH_CNF13 (3 << 22)
#define GPIO_ODR_PIN13_ON (1 << 13)

void delay(volatile unsigned int ms);

int main(void) {
	
	// Enable HSE oscillator
	//RCC_CR |= RCC_CR_HSEON;
	//while(!(RCC_CR & RCC_CR_HSERDY));
	
	// Set PLL source to HSE and multiply by 9 (8 MHz HSE * 9 = 72 MHz)
	//RCC_CFGR |= RCC_CFGR_PLLSRC;
	//RCC_CFGR |= RCC_CFGR_PLLMULL9;
	
	// Enable PLL
	//RCC_CR |= RCC_CR_PLLON;
	//while(!(RCC_CR & RCC_CR_PLLRDY));
	
	// Select PLL as system clock source
	//RCC_CFGR |= RCC_CFGR_SW_PLL;
	//while((RCC_CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
	
	RCC_CFGR &= ~(3 << 0);
	while((RCC_CFGR & (3 << 2)) != (0 << 2))
	
	// Set the AHB and APB2 prescaler to 1
	RCC_CFGR |= RCC_CFGR_HPRE_DIV1;
	RCC_CFGR |= RCC_CFGR_PPRE2_DIV1;
	RCC_CFGR |= RCC_CFGR_PPRE1_DIV2; // This statement is not working
	
	//RCC_CR &= ~(1 << 0); // HSI is disabled
	
	RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;
	RCC_APB1ENR |= RCC_APB1ENR_TIM2EN;

  GPIOC_CRH &= ~GPIO_CRH_MODE13;
  GPIOC_CRH |= GPIO_CRH_MODE13_1;
  GPIOC_CRH &= ~GPIO_CRH_CNF13;
	
	while (1) {
		GPIOC_ODR |= GPIO_ODR_PIN13_ON;
		delay(1000);
		
		GPIOC_ODR &= ~GPIO_ODR_PIN13_ON;
		delay(1000);
	}
}

void delay(volatile unsigned int ms){
		
	TIM2_PSC = 8000 - 1;  // Prescaler: 36 MHz / 36000 = 1000
  TIM2_ARR = ms - 1;  // 1 ms per tick
  
  // Clear update flag
  TIM2_SR &= ~(0x01);
  
  // Enable the counter
  TIM2_CR1 |= TIM2_CR1_CEN;
  
  // Wait for the update event
  while (!(TIM2_SR & 0x01));
  
  // Disable the counter
  TIM2_CR1 &= ~(TIM2_CR1_CEN);
}*/

#define RCC_BASE            (0x40021000)
#define GPIOC_BASE					(0x40011000)
#define TIM2_BASE						(0x40000000)

#define RCC_APB2ENR				  (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define RCC_APB1ENR				  (*(volatile unsigned int *)(RCC_BASE + 0x1C))
#define RCC_CFGR					  (*(volatile unsigned int *)(RCC_BASE + 0x04))
	
#define TIM2_ARR        (*(volatile unsigned int *)(TIM2_BASE + 0x2C))
#define TIM2_PSC        (*(volatile unsigned int *)(TIM2_BASE + 0x28))
#define TIM2_SR         (*(volatile unsigned int *)(TIM2_BASE + 0x10))
#define TIM2_CR1				(*(volatile unsigned int *)(TIM2_BASE + 0x00))
	
#define GPIOC_CRH						(*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR						(*(volatile unsigned int *)(GPIOC_BASE + 0x0C))

void delay(int s);

int main(void) {
	
	RCC_CFGR &= ~(3 << 0);
	while((RCC_CFGR & (3 << 2)) != (0 << 2));
		
	RCC_APB2ENR |= (1 << 4);
	RCC_APB1ENR |= (1 << 0);
	
	GPIOC_CRH &= ~(3 << 20);
	GPIOC_CRH |= (1 << 21);
	GPIOC_CRH &= ~(3 << 22);
	
	while(1) {
		GPIOC_ODR |= (1 << 13);
		delay(1000); //ms
		
		GPIOC_ODR &= ~(1 << 13);
		delay(1000); //ms
	}
}

void delay(int s) {
	TIM2_PSC = 8000 - 1; // 1000 Hz
	TIM2_ARR = s - 1;
	
	// Clear update flag
  TIM2_SR &= ~(0x01);
	
	// Enable
	TIM2_CR1 |= (1 << 0);
	
	while(!(TIM2_SR & 0x01));
	
	// Disable
	TIM2_CR1 &= ~(1 << 0);
	
}