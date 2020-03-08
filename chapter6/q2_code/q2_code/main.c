#include <avr/io.h>

unsigned char bin_to_gray(unsigned char bin){
	return (bin>>1)^bin;
}

unsigned char gray_to_bin(unsigned char gray)
{
	gray ^= (gray >> 4);
	gray ^= (gray >> 2);
	gray ^= (gray >> 1);
	return gray;
}

int main(void){
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0xFF;
	
	unsigned char dip_in;
	
	while(1){
		dip_in = PINB;
		if(PINC & 0x01)
			PORTD = bin_to_gray(dip_in);
		else
			PORTD = gray_to_bin(dip_in);
	}
}