/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/

#include <avr/io.h>
#include <util/delay.h>

int main(){

    //set PD6(OC0A) pin as the output
	DDRD = DDRD | (1<<PD6);

    //Duty cycle 50%(Output compare register)
	OCR0A = 127 ; 

	//Fast PWM Non-Inverting mode 
	TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);

    /*
    1:1024 --> f(wave) = 61.04Hz
    1:256 --> f(wave) = 244.14Hz
    1:64 --> f(wave) = 976.56Hz
    1:8 --> f(wave) = 7.81kHz
    */

    //Keep busy
    while(1){
        for(unsigned char i = 5 ; i >=2 ; i--){
            TCCR0B = i;
            _delay_ms(2000);
        }
    }

    return 0 ;
}