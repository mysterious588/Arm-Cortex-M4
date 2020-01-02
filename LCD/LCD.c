/*******************************************************************************
*****************This driver is made for HD4478 LCD displays********************
********************Using the eight data pins of the LCD************************
*******************************************************************************/

/*-------------------------------Connections----------------------------------*/
/*--------------------------------RS >> PA5-----------------------------------*/
/*--------------------------------RW >> PA6-----------------------------------*/
/*--------------------------------EN >> PA7-----------------------------------*/
/*--------------------------------Dn >> PDn-----------------------------------*/

#include "TM4C123.h"
#define CPU_FREQ 16000000

/******************************Pins Configurations*****************************/
#define LCD_RS     (1 << 5) //Register select pin for the LCD    PIN 4    (LCD)
#define LCD_RW     (1 << 6) //Read/Write pin fro the LCD         PIN 5    (LCD)
#define LCD_ENABLE (1 << 7) //Enable pin 			 PIN 6    (LCD)
#define LCD_DATA 0XFF       //Data pins                          PIN 7-14 (LCD)

/*************************LCD Register Configurations**************************/
#define DISPLAY_MODE_R     0x38 
#define AUTO_INCREMENT_R   0x06
#define DISPLAY_ON_R       0x0F
#define CLEAR_DISPLAY_R    0x01
#define CURSOR_HOME_R      0x08


void LCD_init(void);
void LCD_Cmd(unsigned char command);
void LCD_Data(unsigned char data);
void delay_ms(unsigned int duration);

int main(){
	while (1){
		LCD_init();
		LCD_Cmd(CLEAR_DISPLAY_R);
		LCD_Cmd(CURSOR_HOME_R);
		char *data = "Hello world!"; //Creative, right?
		
		//Print the data
		for (unsigned char i = 0; i < sizeof(data); i++){
				LCD_Data(data[i]);
				delay_ms(50);
		}	
	}
}

void LCD_init(void){
	//Enable Clocks
	SYSCTL->RCGCGPIO |= 0x01 | 0x02;                //PORTA, PORTB Clock Gating
	//PORTA Initilization
	GPIOA->DIR |= LCD_RS | LCD_RW | LCD_ENABLE;     //0b 1110 0000 PA5, PA6 PA7
	GPIOA->DEN |= LCD_RS | LCD_RW | LCD_ENABLE;
	//PORTB Initilization
	GPIOB->DIR |= LCD_DATA;
	GPIOB->DEN |= LCD_DATA;
	//LCD Registers Initilization
	LCD_Cmd(DISPLAY_MODE_R);
	LCD_Cmd(AUTO_INCREMENT_R);
	LCD_Cmd(DISPLAY_ON_R);
	LCD_Cmd(CLEAR_DISPLAY_R);
}

void LCD_Data(unsigned char data){
	GPIOA->DATA |= LCD_RS;
	GPIOB->DATA = data;
	GPIOA->DATA |= LCD_ENABLE;
	delay_ms(50);
	GPIOA->DATA &= !(LCD_RS | LCD_RW | LCD_ENABLE); //clears the LCD Control register
}

void LCD_Cmd(unsigned char command){
	GPIOA->DATA &= !(LCD_RS | LCD_RW | LCD_ENABLE); //clears the LCD Control register
	GPIOB->DATA = command; 
	GPIOA->DATA |= LCD_ENABLE;
	delay_ms(50);
	GPIOA->DATA &= !(LCD_RS | LCD_RW | LCD_ENABLE); //clears the LCD Control register
}

void delay_ms(unsigned int duration){
	SysTick->CTRL = 0x00;
	SysTick->LOAD = (uint32_t) (duration*(CPU_FREQ)/1000) - 1;
	SysTick->CTRL = 0x05;
	while ((SysTick->CTRL & (1<<16)) == 0); //check Count Flag
	SysTick->CTRL = 0x00;
}
