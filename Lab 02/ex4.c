/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define BLINK_DELAY_MS 500

int main(){

    DDRD = DDRD & (~(1 << 2) | ~(1 << 3));     //set PD2(INT0) , PD3(INT1) as input
    DDRB = 0b111111 ;                           // set PORT B as output

    //rising edge detection for INT0
    EICRA = EICRA | (1 << ISC00);
    EICRA = EICRA | (1 << ISC01);

    // rising edge detection for INT1
    EICRA = EICRA | (1 << ISC10);
    EICRA = EICRA | (1 << ISC11);

    //enable globle external interrupts
    sei();

    // enable external interrupts for INT0
    EIMSK = EIMSK | (1 << INT0);

    // enable external interrupts for INT1
    EIMSK = EIMSK | (1 << INT1);

    PORTB = 0 ;                 //Set the initial value of portB as zero 

    // checking whether the Push button is pressed or not if pressed this will become true
    // while loop is for continuosly reading the input
    while (1){
        
    }
    
    return 0 ;
}

ISR(INT0_vect){

    // if the user pressed button A (input 0 at the end)
    PORTB = PORTB << 1 ;
    // _delay_ms(BLINK_DELAY_MS);
}

ISR(INT1_vect){
    //if the user has pressed the button B (input 1 at the end)
    PORTB = (PORTB << 1) + 1;
    // _delay_ms(BLINK_DELAY_MS);
}