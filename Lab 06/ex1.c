#include <avr/io.h>

void usart_init(){
    //Set baud rate
	UBRR0H = (unsigned char)(UBRRVAL >> 8);   //high byte
    UBRR0L = (unsigned char)UBRRVAL;     			//low byte

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
	while(!(UCSRA & (1<<RXC)));
		return UDR;
}


int main(){
    return 0;
}