
#define RCC_BASE            (0x40021000)
#define GPIOC_BASE			(0x40011000)
#define TIM2_BASE			(0x40000000)

#define RCC_APB2ENR		(*(volatile unsigned int *)(RCC_BASE + 0x18))
#define RCC_APB1ENR		(*(volatile unsigned int *)(RCC_BASE + 0x1C))
#define RCC_CFGR		(*(volatile unsigned int *)(RCC_BASE + 0x04))

#define TIM2_ARR        (*(volatile unsigned int *)(TIM2_BASE + 0x2C))
#define TIM2_PSC        (*(volatile unsigned int *)(TIM2_BASE + 0x28))
#define TIM2_SR         (*(volatile unsigned int *)(TIM2_BASE + 0x10))
#define TIM2_CR1		(*(volatile unsigned int *)(TIM2_BASE + 0x00))

#define GPIOC_CRH		(*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR		(*(volatile unsigned int *)(GPIOC_BASE + 0x0C))

void delay(int s);

int main(void) {

	RCC_CFGR &= ~(3 << 0); // Set HSI as System clock: 8MHz
	while((RCC_CFGR & (3 << 2)) != (0 << 2)); // Wait until clock is ready

	RCC_APB2ENR |= (1 << 4); // enable port c clock
	RCC_APB1ENR |= (1 << 0); // enable TiM2 clock

	GPIOC_CRH &= ~(15 << 20); // clear bits 20-23
	GPIOC_CRH |= (1 << 21); // Set operating frequency at 2 MHz
	GPIOC_CRH &= ~(3 << 22); // Set as general purpose output

	while(1) {
		GPIOC_ODR |= (1 << 13); // Set 1 for the 13th pin
		delay(500); //ms

		GPIOC_ODR &= ~(1 << 13); // Set 0 for the 13th pin
		delay(500); //ms
	}
}

void delay(int ms) {
	TIM2_PSC = 8000 - 1; // Divide 8 MHz system clock to run TIM2 at 1000 Hz
	TIM2_ARR = ms - 1; //store the given value in ms

	// Clear update flag
  TIM2_SR &= ~(1 << 0); // Clear the interrupt update flag of the status register

	// Enable
	TIM2_CR1 |= (1 << 0); // enable TIM2

	while(!(TIM2_SR & 0x01)); // wait until the Status register bit is set that is TIM2 has reached the given value

	// Disable
	TIM2_CR1 &= ~(1 << 0); //disable the TIM2

}
