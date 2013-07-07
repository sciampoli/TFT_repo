/*
 * init_LCD.c
 *
 *  Created on: 07/lug/2013
 *      Author: sciampoli
 */

#include <avr/io.h>
#include <util/delay.h>



#define DDR_SPI DDRB
#define SS DDB2     	//PIN10
#define DD_MOSI DDB3 	//PIN11
#define DD_MISO DDB4 	//PIN12
#define SCK DDB5 		//PIN13

/* LCD */
#define D_C DDB1		//PIN9
#define LCD_RESET DDB0	//PIN8
/*COMMAND */
#define NOP 0x00
#define RDID 0x04
#define RDID1 0xDa
#define RDID2 0xDb
#define RDID3 0xDc


void SPI_MasterInit(void){
/* Set MOSI, SCK, SS output, all others input */
DDR_SPI = _BV(DD_MOSI) | _BV(SCK) | _BV(SS);
PORTB |= _BV(SS);
/* Enable SPI, Master, set clock rate fck/16 */
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


char SPI_MasterTransmit(char cData){

	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}


void reset_LCD(void){

	PORTB &= ~_BV(LCD_RESET);
	_delay_ms(100);
	PORTB |= _BV(LCD_RESET);
	_delay_ms(100);
}

void init_LCD(void){

	char read;
	PORTB &= ~_BV(SS);
	PORTB &= ~_BV(D_C);
	SPI_MasterTransmit(RDID1);
	read = SPI_MasterTransmit(RDID1);
	PORTB |= _BV(D_C);
	PORTB |= _BV(SS);

}

int main(){
	return 0;
}
