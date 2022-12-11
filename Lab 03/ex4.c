/*
E / 18 / 173
Kasthuripitiya K.A.I.M.

*/

/*
Xtal = 1 / 16 us
Prescaler 1:1024 --> Tcounter_clk = 1024 x 1/16 = 64us
Counter increments needed = 10^6/64 = 15625 increments
Initial counter value = 65535 + 1 - 15625 = 49911
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define BLINK_DELAY_MS 100

int main(){
    //set PORTB pin 5 as output
    DDRB = 0b101111 ;
    
    // load timer counter register
    TCNT1 = 0xC2F7;

    // Set timer1 under normal mode with prescaling 1:1024
    TCCR1A = 0x00;
    TCCR1B = 0x05;

    TIMSK1 = TIMSK1 | (1 << TOIE1);              // Enable timer1 overflow interrupt (TOIE1)

    //Enable global interrupts
    sei();
    
    while(1){
           
        for(unsigned char i = 0 ; i < 4 ; i++){
        	// PORTB = 0 ; // set all PORTB to low
          	PORTB = PORTB | 1 << i; //Set the ith pin to high and others to low
          	_delay_ms(BLINK_DELAY_MS);
            PORTB = PORTB & ~(1<<i);
        }
      	
        // Revesrse the pattern
       	for(unsigned char i = 2 ; i > 0 ; i--){
        	// PORTB = 0 ;
          	PORTB = PORTB | 1 << i;
          	_delay_ms(BLINK_DELAY_MS);
            PORTB = PORTB & ~(1<<i);
        }
        
    }

    
    return 0 ;
}

ISR(TIMER1_OVF_vect){

	PORTB = PORTB ^ (1<<5);	//Toggling the PB5
	TCNT1 = 0xC2F7;	// Reset the timer1 value
}