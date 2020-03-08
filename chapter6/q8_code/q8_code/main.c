#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void){
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0xFF;
	
	int8_t dipsw8, dipsw4, result;
	
	while(1){
		dipsw8 = PINB;
		dipsw4 = PINC;
		dipsw4 &= 0x0F;
		
		if(dipsw4 == 0){
			for(int i = 0; i<8 ;i++){
				if(i == 0)
					PORTD = 0x80;
				else
					PORTD = (PORTD>>1);
				_delay_ms(1000);
				if((PINC & 0x0F) != 0)
					break;
			}
		}
		else{
			result = dipsw8/dipsw4;
			if(result < 0){
				PORTD = result;
				_delay_ms(1000);
				PORTD &= 0x00;
				_delay_ms(1000);
			}
			else
				PORTD = result;
		}
	}
}