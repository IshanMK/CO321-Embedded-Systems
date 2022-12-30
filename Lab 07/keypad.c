/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/
#include <avr/io.h>
#include "usart.c"
#include <util/delay.h>
#include <string.h>

char keypad[4][4] = {{'1', '2', '3', 'A'},
					{'4', '5', '6', 'B'},
					{'7', '8', '9', 'C'},
					{'*', '0', '#', 'D'}};

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
    DDRD = 0x00; // inputs(columns)

    //PC0-PC3
    DDRC = 0b111111;

    //in idle state rows are LOW and columns are HIGH
    PORTD = 0b11111111;
    PORTC = 0b000000;

    //do the bitwise and operation to find the relevant column

    //wait till any of the colums become LOW
    //by default all the PINS are HIGH
    while((PIND == 0b11111111));

    switch(PIND){
        case 0b11101111:
            colVal = 0 ;
            break;
        case 0b11011111:
            colVal = 1;
            break;
        case 0b10111111:
            colVal = 2 ;
            break;
        case 0b01111111:
            colVal = 3;
            break;            
    }

    // The Arduino knows the key is in which column. But we have 4 key in that column. 
    //We need to detect the exact key by scanning the Rows. 
    //The scanning happens by sending 1 (HIGH) to the Row pins one by one and read at column pins. 
    //This will return a HIGH (1) Signal only at the pressed key location.
    for(int i = 0 ; i < 4 ; i++){
        PORTC = PORTC | (1 << i) ;
        _delay_ms(20);
        if(PIND == 0b11111111){
            rowVal = i ;
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
    
    // sendstr(str);
}

int main(){
    
    usart_init();
    while(1){
        char c[2] = {readThePressedKey() , '\0'};
        sendstr(c);
        // readThePressedKey();
        _delay_ms(2000);
    }
    return 0 ;
}