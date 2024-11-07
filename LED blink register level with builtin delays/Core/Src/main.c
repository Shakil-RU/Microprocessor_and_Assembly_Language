
#define RCC_BASE            (0x40021000)
#define GPIOC_BASE			(0x40011000)


	#define RCC_APB2ENR				  (*(volatile unsigned int *)(RCC_BASE + 0x18)) //point to the peripheral clock enable register for GPIOC

	#define GPIOC_CRH				  (*(volatile unsigned int *)(GPIOC_BASE + 0x04)) // point to the port configuration register high(gpio_crh)
	#define GPIOC_ODR				  (*(volatile unsigned int *)(GPIOC_BASE + 0x0C)) // point to the port output data register

int main(void)


{	    RCC_APB2ENR |= (1 << 4); // enable the port 13

	  	GPIOC_CRH &= ~(3 << 20);//reset or clear the bits 20 and 21


	  	GPIOC_CRH |= (1 << 21);   // set value to 21 because 20 is already 0
	  	GPIOC_CRH &= ~(3 << 22);  //  reset bit 22 AND 23 by psssing 00

	  	while(1) {
	  		GPIOC_ODR |= (1 << 13); // set 1 to on the bit
	  		for(int i = 0; i<1000000;i++);

	  		GPIOC_ODR &= ~(1 << 13);  // set 0 to off the bit
	  		for(int i = 0; i<1000000;i++);


	  	}

 }

