/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define BLINK_DELAY_MS 500

int main(){

    DDRD = DDRD & ~(1 << 2);     //set PD2(INT0) as input
    DDRB = 0b111111 ;           //set PORTB as output

    // set for negative edge detection
    EICRA = EICRA & ~(1 << ISC00);
    EICRA = EICRA | (1 << ISC01);

    // enable global interrupts
    sei();

    // enable external interrupt for int0
    EIMSK = EIMSK | (1 << INT0);
    
    PORTB = 0 ;                 //Set the initial value of portB as zero 

    // checking whether the Push button is pressed or not if pressed this will become true
    // while loop is for continuosly reading the input
    while (1){
        
    }
    
    return 0;
}

ISR(INT0_vect){
    // _delay_ms(BLINK_DELAY_MS);     
    PORTB++;
    // _delay_ms(BLINK_DELAY_MS);
}