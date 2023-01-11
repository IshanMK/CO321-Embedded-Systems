#include "lcd.c"
#include "keypad.c"
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "eeprom_basic.c"
#include "caesar_cipher.c"

#define DEFAULT_KEY '3'

int main(){
     /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON);

    //store the string
    char str[11] ;

    //write default key to address 0
    EEPROMwrite(0 , DEFAULT_KEY);

    //initialize usart
    usart_init();


    while(1){

        /* clear display and home cursor */
        lcd_clrscr();

        lcd_puts("Encrypt(A)\n");
        lcd_puts("Change(C)\n");

        readThePressedKey();
        char option = readThePressedKey();

        lcd_clrscr();

        if(option == 'A'){

            lcd_puts("Enter Plain Text : \n");

            //stop reading the already selected option
            readThePressedKey();
            unsigned int i = 0 ;
            //start reading the array of characters length of 10
            // lcd_gotoxy(0,1);

            while(i < 10){
                char lettter = readThePressedKey();
                lcd_putc(lettter);
                lcd_gotoxy(i , 1);
                str[i] = lettter;
                i++;
            }
            str[i] = '\0';

            lcd_clrscr();

            //read the key from eeprom
            int key = EEPROMread(0) - '0';

            char* encrypted = encrypt(str , key);
            // free(str);

            //send the result
            lcd_puts(encrypted);
            _delay_ms(2000);

            //remove the pointer
            free(encrypted);
            lcd_clrscr();
        }
        else if(option == 'C'){
            lcd_puts("Enter new Key : \n");

            //stop reading the already selected option
            readThePressedKey();

            char newKey = readThePressedKey();

            //write the new key to eeprom's 0th address
            //in future this will be used as the key
            EEPROMwrite(0 , newKey);

            lcd_clrscr();

            lcd_puts("Enter Plain Text : \n");

            //stop reading the already selected option
            readThePressedKey();

            unsigned int i = 0 ;
            //start reading the array of characters length of 10
            while(i < 10){
                char lettter = readThePressedKey();
                lcd_putc(lettter);
                lcd_gotoxy(i , 1);
                str[i] = lettter;
                i++;
            }
            str[i] = '\0';

            lcd_clrscr();
            
            //read the key from eeprom
            int secretKey = EEPROMread(0) - '0';

            char* encrypted = encrypt(str , secretKey);

            //send the result
            lcd_puts(encrypted);

            _delay_ms(2000);

            //remove the pointer
            free(encrypted);

            lcd_clrscr();

        }
        // lcd_putc(option);
        // _delay_ms(1000);

        lcd_clrscr();
    }
    return 0 ;
}
