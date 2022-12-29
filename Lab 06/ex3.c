/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/
#include <avr/io.h>
#include <stdlib.h>

void usart_init(){
    //Set baud rate to 9600
    // bps = 16Mhz/ (16(X + 1)) ==> X = 103.16 in decimal
    UBRR0L = 0x67;     			//low byte

	//Enable Transmitter and Receiver and Interrupt on receive complete
    UCSR0B |= (1 << TXEN0);
    
    //Set data frame format: asynchronous mode,no parity, 1 stop bit, 8 bit size
    UCSR0C |= (1 << UCSZ01)|(1 << UCSZ00);
}

void usart_send(char MSG){
    UCSR0B |= (1 << TXEN0);             // enables USART transmitter
    while (!(UCSR0A & (1 << UDRE0)));   // checks UDRE0 bit
    UDR0 = MSG;                           // writes the character byte to be transferred, to UDR0
}

char usart_receive(){
    UCSR0B |= (1 << RXEN0);             // enables USART receiver
    while(!(UCSR0A & (1<<RXC0)));
    char c = UDR0;
    return c;
    
}

void sendstr(char line[]){
	int i = 0;
    while (line[i] != '\n')             // sends each char of the string until the end of line
    {
        usart_send(line[i]);
        i++;
    }
    usart_send('\n');                   // sends a new line char at end
}

char* receivestr(){

    char *line = (char*)malloc(1000);   // to hold chars of the receiving line
    char c;
    int i = 0;
    while (1)                           // receives each char of the string until the end of line
    {
        c = usart_receive();
        if (c != '\n') {
          line[i] = c;
        }  
        else {
          line[i] = '\n';
           break;
        }
        i++;
    }
    return line;
}

int main(){

    //initialize usart
   usart_init();
   
    char* line , encoded;
    while (1)
    {
        line = receivestr();           // receives a line of characters
        int i = 0;
        while (line[i])                 // implements caesar cipher until the end of line
        {
            if ((line[i] >= 'A') && (line[i] <= 'Z')) line[i] = 65 + (line[i] + 3 - 65) % 26;
            else if ((line[i] >= 'a') && (line[i] <= 'z')) line[i] = 97 + (line[i] + 3 - 97) % 26;
            i++;
        }

        sendstr(line);                 // sends a line of characters
        free(line);
    }
   return 0;
}


