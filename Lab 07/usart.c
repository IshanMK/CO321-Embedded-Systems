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
  // sends each char of the string until the end of line
    while (line[i] != '\0'){
        usart_send(line[i]);
        i++;
    }
    // usart_send('\0');                   // sends a new line char at end
    usart_send('\r');
    usart_send('\n');

}

char* receivestr(){

    char *line = (char*)malloc(1000);   // to hold chars of the receiving line
    char c;
    int i = 0;
    // receives each char of the string until the end of line
    while (1){                           
      c = usart_receive();
      if (c == '\n' || c == '\r' || c == '\0') {
        break;
      }  
      else {
        line[i] = c;
      }
      i++;
    }

    line[i] = '\0';
    // line[++i] = '\0';

    return line;
}


