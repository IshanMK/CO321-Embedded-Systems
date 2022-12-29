/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/

#include <avr/io.h>

void EEPROMwrite(unsigned int address , char data){

    //wait till previous write operation is finished
    while(EECR & (1 << EEPE));

    //set up address and the data registers
    EEAR = address;
    EEDR = data;

    //enable the master write enable by setting it to logical 1
    EECR |= (1 << EEMPE);

    //start eeprom write 
    EECR |= (1 << EEPE);
}

char EEPROMread(unsigned int address){

    //wait till previous write operation is finished
    while(EECR & (1 << EEPE));

    //set up address and the data registers
    EEAR = address;

    //enable read operation
    EECR |= (1 << EERE);

    //return the data read
    return EEDR;
}
