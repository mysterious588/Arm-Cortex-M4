#include "TM4C123.h"                    // Device header

#define CLOCK_GATING_PORTF (1<<5)

// Built In RGB Leds
#define RED                (1<<1)
#define BLUE               (1<<2)
#define GREEN              (1<<3)

void delay_ms(unsigned int);

int main(){
	
	SYSCTL->RCGCGPIO = CLOCK_GATING_PORTF;
	
	GPIOF->DIR = RED | BLUE | GREEN;
	
	GPIOF->DEN = RED | BLUE | GREEN;
	
	GPIOF->DATA = RED | BLUE ;
	
	while (1){
		//Blink
		GPIOF->DATA ^= (RED | BLUE);
		delay_ms(1000);
  }
	return 0;
}

void delay_ms(unsigned int duration){
    unsigned int i = 0;
    while (i < 3400 * duration)
        i++;
}