#include <avr/io.h>
#include <util/delay.h>
#define BLINK_DELAY_MS 200

int main (){

    // Set port pins 8,9,10,11 as outputs
    DDRB = DDRB|(0b001111); 
    while(1){
      	
      	for(unsigned char i = 0 ; i < 4 ; i++){
          	PORTB = PORTB | 1 << i; //Set the ith pin to high and others to low
          	_delay_ms(BLINK_DELAY_MS);
		PORTB = PORTB & ~(1<<i);
        }
      	
        // Revesrse the pattern
       	for(unsigned char i = 2 ; i > 0 ; i--){
          	PORTB = PORTB | 1 << i;
          	_delay_ms(BLINK_DELAY_MS);
		PORTB = PORTB & ~(1<<i);
        }    
        
    }
}