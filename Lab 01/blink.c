#include <avr/io.h>
#include <util/delay.h>
#define BLINK_DELAY_MS 200

int main (){

    // Set port pins 8,9,10,11 as outputs
    DDRB = DDRB|(0b001111); 

    // set PORTB pins to zero
    PORTB = 0;
  	while(1){
      PORTB = ~PORTB; //set PORTB pins to 1
      _delay_ms(BLINK_DELAY_MS);
          
    }
}
