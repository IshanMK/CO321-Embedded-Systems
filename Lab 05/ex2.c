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

    //set PORTD (PD0)as the output
    DDRD |= (0b111111111);

    while(1){

        //start conversion    
        ADCSRA |= (1 << ADSC);

        //wait until the end of conversion
        //at the end of conversion ADIF will be high

        while(!(ADCSRA & (1 << ADIF))){
           
        }
        
        //give the output as the ADC word
        //for 3.3 V it gives 0b10101110 + 10 ==> ADCH + ADCL ==> ADCW
        //assuming that it requires at least 3.3V
        //for 2.7V ==> 1000111011 ==> 571
        //AVcc ==> 1.21031518625V
        PORTD = ADCW < 0b1010111010 ? 0x01 : 0x00;
        // PORTD = ADCW < 0b1010111010 ? 1 << PD0 : ~(1 << PD0);

        //clear the completion signal for next conversion
        ADCSRA |= (1 << ADIF); 
    }

    return 0 ;
}