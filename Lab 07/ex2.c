/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/

#include "eeprom.c"
#include "usart.c"

int main(int argc , char** argv){

    //store the string
    char* str ;

    //initialize usart
    usart_init();

    while(1){

        sendstr("select the option R(Read) or W(Write) : ");

        //get the option as read or write
        char option = usart_receive();

        //receive the newline character
        usart_receive();

        if(option == 'W'){
            sendstr("Enter an Input String : ");

            //get the input and store it
            str = receivestr();
            
            //write the data to the eeprom starting from the address 0
            EEPROMwritestr(0 , str);

            sendstr("Successfully Written!");

            free(str);
        }
        else if(option == 'R'){

            //read the data from the eeprom from 0 to 1023
            str = EEPROMreadstr(0);

            //output the data read
            sendstr(str);

            free(str);
        }
        else{

            sendstr("Unknown Option!");
        }
    }

    return 0 ;
}