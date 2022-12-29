/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/

#include "eeprom_basic.c"
#include "usart.c"
#include "caesar_cipher.c"
#include <stdlib.h>
#include <util/delay.h>

#define DEFAULT_KEY '3'

int main(int argc , char** argv){

    //store the string
    char* str ;

    //write default key to address 0
    EEPROMwrite(0 , DEFAULT_KEY);

    //initialize usart
    usart_init();

    while(1){
        
        //display this message
        sendstr("Enter an Text : ");

        //receive the text first
        str = receivestr();

        sendstr("Encrypt(E) or Change(C) Default Secret Key : ");

        //get the option as read or write
        char option = usart_receive();

        //receive the newline character
        usart_receive();

        if(option == 'E'){

            //read the key from eeprom
            int key = EEPROMread(0) - '0';

            //do the encryption
            str = encrypt(str , key);
            
            sendstr("Encryption done!");

            sendstr(str);
            free(str);
        }
        else if(option == 'C'){

            //asking for the new key
            sendstr("Enter the new key : ");

            //get the option as read or write
            char keyVal = usart_receive();

            //receive the newline character
            usart_receive();

            //write the new key to eeprom's 0th address
            //in future this will be used as the key
            EEPROMwrite(0 , keyVal);

            //read the key from eeprom
            int secretKey = EEPROMread(0) - '0';

            str = encrypt(str , secretKey);

            //write the data to the eeprom starting from the address 0
            sendstr("Encryption done!");

            sendstr(str);
            free(str);
            
        }
        else{
            free(str);
            continue;
        }
    }

    return 0 ;
}