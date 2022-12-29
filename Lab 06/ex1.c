#include <avr/io.h>

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

unsigned char usart_receive(){
	while(!(UCSRA & (1<<RXC)));
		return UDR;
}


int main(){
    return 0;
}