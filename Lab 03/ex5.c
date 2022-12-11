/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char count = 0;  // Counter to increment to get 100ms when 1ms is detected

int main(){

    DDRB = DDRB | (1<<5);  // Set PB5 as output

    // Set timer0 under normal mode with prescaling 1:64
	TCCR0A = 0x00;  
	TCCR0B = 0x03;  

	TIMSK0 = TIMSK0 | (1<<0);	// Set timer overflow interrupts

	TCNT0 = 6;		// Set value to begin count (255+1-250 = 6)
	
	sei();	// Enable for global interrupts
    
    //keep busy
    while(1){

    }


    return 0;
}

ISR(TIMER0_OVF_vect){

    // get a count of 100 (when ISR executed count increment by one)
    count++;
    
    // Blinking the light if 100ms detected
    if(count == 100){
        PORTB = PORTB ^ (1<<5);    // Blink the LED
        count = 0;          // Reset the count
    }
}