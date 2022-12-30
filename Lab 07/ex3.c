/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/

#include "eeprom_basic.c"
#include "usart.c"
#include "caesar_cipher.c"
#include <stdlib.h>
#include <util/delay.h>
#include "keypad.c"

#define DEFAULT_KEY '3'

int main(int argc , char** argv){

    //store the string
    char str[11] ;

    //write default key to address 0
    EEPROMwrite(0 , DEFAULT_KEY);

    //initialize usart
    usart_init();

    while(1){

        sendstr("Encrypt(A) or Change(C) Default Secret Key : ");

        //detect the char 'U' first for unknown behaviour
        readThePressedKey();
        char option = readThePressedKey();
        
        if(option == 'A'){

            sendstr("Enter an text : ");

            //stop reading the already selected option
            readThePressedKey();
            unsigned int i = 0 ;
            //start reading the array of characters length of 10
            while(i < 10){
                char lettter = readThePressedKey();
                str[i] = lettter;
                i++;
            }
            str[i] = '\0';

            //send the result
            // sendstr(str);

            //read the key from eeprom
            int key = EEPROMread(0) - '0';

            char* encrypted = encrypt(str , key);
            // free(str);

            //send the result
            sendstr(encrypted);

            //remove the pointer
            free(encrypted);

        }
        else if(option == 'C'){
            sendstr("Enter the new Key : ");

            //stop reading the already selected option
            readThePressedKey();

            char newKey = readThePressedKey();

            //write the new key to eeprom's 0th address
            //in future this will be used as the key
            EEPROMwrite(0 , newKey);

            sendstr("Enter an text : ");

            //stop reading the already selected option
            readThePressedKey();

            unsigned int i = 0 ;
            //start reading the array of characters length of 10
            while(i < 10){
                char lettter = readThePressedKey();
                str[i] = lettter;
                i++;
            }
            str[i] = '\0';

            //read the key from eeprom
            int secretKey = EEPROMread(0) - '0';

            char* encrypted = encrypt(str , secretKey);

            //send the result
            sendstr(encrypted);

            //remove the pointer
            free(encrypted);
        }
        // else{
        //     str[0] = option;
        //     str[1] = '\0';
        //     sendstr(str);
        // }
        
    }

    return 0 ;
}