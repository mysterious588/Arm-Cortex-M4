/*
** Check section 10.3 in page 618
** Written By: Ahmed Khaled
*/
#include <stdint.h>

// RCGCGPIO Controls the clock gating of the GPIO
#define RCGCGPIO (*((volatile uint32_t *) 0x400FE608)) // page 315
// APB GPIO PORTF Data Register, Sets the pins' voltage
#define GPIODATF (*((volatile uint32_t *) 0x400253FC)) // page 623
// APB GPIO PORTF Direction Register, Sets pins as inputs/outputs
#define GPIODIRF (*((volatile uint32_t *) 0x40025400)) // page 624
// APB GPIO PORTF Digital Enable Register, Enable the digital functions of the pins
#define GPIODENF (*((volatile uint32_t *) 0x4002551C)) // page 643

void delay_ms(unsigned int duration);

int main() {
    // Wake up PORTF's clock
    RCGCGPIO = 0x20;
    // Sets the fourth pin in PORTF as output
    GPIODIRF = 0x08;
    // Enable digital functions on fourth pin
    GPIODENF = 0x08;

    while(1){
        // inverts the LED
        GPIODATF ^= 0x08;
        delay_ms(1000);
    }
}

void delay_ms(unsigned int duration){
    unsigned int i = 0;
    while (i < 1000 * duration)
        i++;
}


