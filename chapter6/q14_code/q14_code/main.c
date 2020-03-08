#define  F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

uint8_t bcd27seg(uint8_t d){
	switch (d)
	{
		case 0: return 0xC0;
		case 1: return 0xF9;
		case 2: return 0xA4;
		case 3: return 0xB0;
		case 4: return 0x99;
		case 5: return 0x92;
		case 6: return 0x82;
		case 7: return 0xF8;
		case 8: return 0x80;
		case 9: return 0x90;
		default: return 0x40;
	}
}

int main(void)
{
	DDRA = 0x00;
	DDRB = 0x00;
	DDRC = 0xFF;
	DDRD = 0xFF;
	
	uint8_t dipsw1, dipsw2, mode_sel;
	int8_t c10 = 0;
	int8_t c01 = 0;
	
    while (1) 
    {
		dipsw1 = PINA;
		dipsw1 &= 0x0F;
		if(dipsw1 > 9)
			dipsw1 = 9;
		
		dipsw2 = PINB;
		dipsw2 &= 0x0F;
		if(dipsw2 > 9)
			dipsw2 = 9;
		
		mode_sel = (PINB >> 7) ;		
		
		if(mode_sel){
			c01++;
			if(c01 == 10){
				c01 = 0;
				c10++;
			}
			if(c10 >= dipsw1){
				if(c01 > dipsw2){
					c01 = 0;
					c10 = 0;
				}
			}
		}
		else{
			c01--;
			if(c01 < 0){
				if(c10 <= 0){
					c10 = dipsw1;
					c01 = dipsw2;
				}
				else{
					c01 = 9;
					c10--;
				}
			}
		}
		PORTC = bcd27seg(c10);
		PORTD = bcd27seg(c01);
		_delay_ms(200);
	}
}
