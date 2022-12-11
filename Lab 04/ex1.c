/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/

/*
Modulatiing frequency = 1 / T
f(wave) = 976.56Hz , DC = 50%
so , OCR0A = 127 , N(presacle) = 64
Here PD6 is the OC0A pin
*/

#include <avr/io.h>

int main(){

	//set PD6(OC0A) pin as the output
	DDRD = DDRD | (1<<PD6);

	//Duty cycle 50%(Output compare register)
	OCR0A = 127 ; 

	//Fast PWM Non-Inverting mode 
	TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);

	//1:64 prescaler
	TCCR0B |= (1 << CS01) | (1 << CS00);

	//Keep busy
	while(1){

	}

	return 0 ;
}