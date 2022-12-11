/*
E / 18 / 173
Kasthuripitiya K.A.I.M.

*/
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char count = 0; // Count variable for get 50 count when 1ms is detected

int main(){

    DDRB = DDRB | 0b00000011;     // Declare PB0 And PB1 as outputs for LEDs

    // For 50ms (Use Timer0)
   
    // Set timer0 under normal mode with prescaling 1:64
    TCCR0A = 0x00;  
    TCCR0B = 0x03; 

    TIMSK0 = TIMSK0 | (1<<0);   // Setting for Overflow interrupts from timer 0

    TCNT0 = 6;          // For 1 ms there should be 250 increments (255+1-250 = 6)


    // For 500ms (use Timer1)

    // Set timer1 under normal mode with prescaling 1:256
    TCCR1A = 0x00;  
    TCCR1B = 0x04;  
    
    TIMSK1 = TIMSK1 | (1<<0);   // Setting for overflow interrupts from timer 1

    TCNT1 = 0x85EE;      // For 500ms there should be 31250 incremnets (65535+1-31250 = 34286)



    sei();  // Setting global interrupts high

    // keep busy
    while(1){

    }

    return 0;
}


// ISR for 50ms 
ISR(TIMER0_OVF_vect){

    // Increment count for every 1ms
    count++;

    // If count = 50ms
    if(count == 50){
        PORTB = PORTB ^ (1<<0);    // Toggle the LED at PB4
        count = 0;          // reset the count
    }
}

ISR(TIMER1_OVF_vect){

    PORTB = PORTB ^ (1<<1);    // Toggle the LED at PB5
}