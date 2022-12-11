/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define BLINK_DELAY_MS 500

int main(){

    DDRD  = DDRD & ~(1 << 2);       //set PD2(INT0) as input
    DDRB = DDRB | (1 << 0) ;      //set PB0 as the output

    //rising edge detection for INT0
    EICRA = EICRA & ~(1 << ISC00);
    EICRA = EICRA | (1 << ISC01);

    //enable global external inputs
    sei();

    //enable external inputs for INT0
    EIMSK = EIMSK | (1 << INT0);

    PORTB = 0 ;         //set the initial output of PORTB to zero

    // checking whether the Push button is pressed or not if pressed this will become true
    // while loop is for continuosly reading the input
    while(1){

    }

    return 0 ;
}

ISR(INT0_vect){

    //toggle the output of PB0
    PORTB = PORTB ^ (1 << 0);
    _delay_ms(BLINK_DELAY_MS);
}