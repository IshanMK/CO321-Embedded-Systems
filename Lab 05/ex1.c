/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/

#include <avr/io.h>
#include <util/delay.h>

int main(){

    //select ADC1 as an input(MUX04-MUX00 = 0001)
    //ADLAR = 1 ==> Left justified ==> ignore last 6 bits ==> read only first 10 bits
    ADMUX |= (1 << MUX0) | (1 << ADLAR);

    //ADEN = 1 ==> enbale the ADC
    //ADPS[2:0] ==> 111 ==> Prescaler ==> 2^7 = 128 ==> 16MHz/128 ==> 125kHz
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    //select AVcc as the Vref
    ADMUX |= (1 << REFS0) ;

    //set PORTD as the output
    DDRD = 0b11111111;

    while(1){

        //start conversion    
        ADCSRA |= (1 << ADSC);

        //wait until the end of conversion
        //at the end of conversion ADIF will be high

        while(!(ADCSRA & (1 << ADIF))){
           
        }

        //wait till ADC stablilize
        _delay_ms(10);

        //give the output as the ADC word
        PORTD = ADCH ;

        //clear the completion signal for next conversion
        ADCSRA |= (1 << ADIF); 
    }

    return 0 ;
}