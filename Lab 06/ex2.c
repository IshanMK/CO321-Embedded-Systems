/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/
#include <avr/io.h>
#include <util/delay.h>

void usart_init(){
    //Set baud rate to 9600
    // bps = 16Mhz/ (16(X + 1)) ==> X = 103.16 in decimal
    UBRR0L = 0x67;     			//low byte

	//Enable Transmitter and Receiver and Interrupt on receive complete
    UCSR0B |= (1 << TXEN0);
    
    //Set data frame format: asynchronous mode,no parity, 1 stop bit, 8 bit size
    UCSR0C |= (1 << UCSZ01)|(1 << UCSZ00);
}

void usart_send(unsigned char MSG){
    // Wait if a byte is being transmitted
    while((UCSR0A&(1<<UDRE0)) == 0);
    // Transmit data
    UDR0 = MSG;  

}

unsigned char usart_receive(void){
	while(!(UCSR0A & (1<<RXC0)));
		return UDR0;
}

void sendstr(unsigned char *s){
	unsigned char i = 0;
	while(s[i] != '\0'){
        usart_send(s[i]);
        i++;
	}
    usart_send('\n');
}

int main(){

    //initialize usart
   usart_init();

   sendstr("E/18/173 Ishan Kasthuripitiya");
   sendstr("E/18/375 Akitha Pathirana");
   return 0;
}