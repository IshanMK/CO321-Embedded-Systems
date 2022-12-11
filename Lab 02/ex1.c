/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/

#include <avr/io.h>
#include <util/delay.h>
#define BLINK_DELAY_MS 1000


int main(){

    DDRD = DDRD & ~(1 << 7);     //set PD7 as input
    DDRB = 0b111111 ;           //set PORTB as output

    PORTB = 0 ;                 //Set the initial value of portB as zero 

    // checking whether the Push button is pressed or not if pressed this will become true
    // while loop is for continuosly reading the input
    while (1){
        if(PIND & (1<<7)){
            PORTB++;
            _delay_ms(BLINK_DELAY_MS);
        }
        
    }
    
    return 0;
}