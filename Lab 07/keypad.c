/*
E / 18 / 173
E /18 /375
Kasthuripitiya K.A.I.M.
*/
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "usart.c"

char keypad[4][4] = {{'*', '0', '#', 'D'},
					{'7', '8', '9', 'C'},
					{'4', '5', '6', 'B'},
					{'1', '2', '3', 'A'}};

//when no button is pressed all the column pins are held high and row pins are held low
//When a button is pressed, the column pin is pulled LOW 
//The Arduino now knows which column the button is in, 
//so now it just needs to find the row the button is in. 
//It does this by switching each one of the row pins HIGH, and at the same time reading all of the column pins to detect which column pin returns to HIGH
//When the column pin goes HIGH again, the Arduino has found the row pin that is connected to the button

//if two HIGH found the button pressed is found

//set the PINS D0-D3 as columns --> inputs
//set D4-D7 as rows --> outputs

/*
References : 
https://www.factoryforward.com/4x4-matrix-keypad-principle-interfacing-arduino/
*/
char readThePressedKey(){

    char pressedLetter ;

    //define row and col value
    //unsigned is must otherwise it will give undefined outputs
    //eg : for "%c" , 11 --> vertical Tab 
    //for "%u" , 11 --> character 11
    unsigned int colVal , rowVal ;
    // char* str = (char*)malloc(2);

    // unsigned char col , row;
    //define the input and output pins
    //PD4-PD7
    //DDRD = 0x00; // inputs(columns)
    DDRD &= ~(1 << PD6) ;
    DDRD &= ~(1 << PD7) ;
    DDRB &= ~(1 << PB0) ;
    DDRB &= ~(1 << PB1) ;    

    //PC0-PC3
    
    DDRB |= (1 << PB5) ;
    DDRB |= (1 << PB4) ;
    DDRB |= (1 << PB3) ;
    DDRB |= (1 << PB2) ;


    //in idle state rows are LOW and columns are HIGH

    //PORTD = 0b11111111;
    PORTD |= (1 << PD6) ;
    PORTD |= (1 << PD7) ;
    PORTB |= (1 << PB0) ;
    PORTB |= (1 << PB1) ;



    //PORTC = 0b000000;
    PORTB &= ~(1 << PB5) ;
    PORTB &= ~(1 << PB4) ;
    PORTB &= ~(1 << PB3) ;
    PORTB &= ~(1 << PB2) ;

    //do the bitwise and operation to find the relevant column

    //wait till any of the colums become LOW
    //by default all the PINS are HIGH
    while((PIND & (1<<PD7))&&(PIND & (1<<PD6))&&(PINB & (1<<PB1))&&(PINB & (1<<PB0)));

    if(!(PIND & (1<<PD6))){
        colVal = 0 ;
    }
    if(!(PIND & (1<<PD7))){
        colVal = 1 ;
    }
    if(!(PINB & (1<<PB0))){
        colVal = 2 ;
    }
    if(!(PINB & (1<<PB1))){
        colVal = 3 ;
    }
    

    // The Arduino knows the key is in which column. But we have 4 key in that column. 
    //We need to detect the exact key by scanning the Rows. 
    //The scanning happens by sending 1 (HIGH) to the Row pins one by one and read at column pins. 
    //This will return a HIGH (1) Signal only at the pressed key location.
    for(int i = 2 ; i < 6 ; i++){
        PORTB = PORTB | (1 << i) ;
        _delay_ms(20);
        if((PIND & (1<<PD7))&&(PIND & (1<<PD6))&&(PINB & (1<<PB1))&&(PINB & (1<<PB0))){
            rowVal = i- 2 ;
            break;
        }
    }    

    /*
    C0 C1 C2 C3
    R3
    R2
    R1
    R0
    */
   
    //we need to find the relevant row
    // char selectedKey[2] = { keypad[rowVal][colVal] , '\0'};
    // str[0] = 3 - rowVal + '0';
    // str[1] = colVal + '0';

    // str[0] = keypad[3 - rowVal][3 - colVal];
    // str[2] = '\0';

    //to stop sending the un identifed char after the first launch
    pressedLetter = keypad[3 - rowVal][colVal];

    char* data = "0123456789*#ABCD";
    if(strchr(data , pressedLetter) != NULL){
        return pressedLetter;
    }
    else{
        //this will be returned for undefined characters
        return '\0';
    }
    // return pressedLetter;
    // sendstr(str);
}

// int main(){
//     usart_init();
//     while(1){
//         char c[2] = {readThePressedKey() , '\0'};
//         sendstr(c);
//         // readThePressedKey();
//         _delay_ms(2000);
//     }
//     return 0 ;
// }