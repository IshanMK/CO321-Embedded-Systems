/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/

#include <stdlib.h>
#include "eeprom_basic.c"


//write data starting from the given address
void EEPROMwritestr(unsigned int address , char* data){
    int i = 0 ;

    while(data[i] != '\0'){
        EEPROMwrite(address + i , data[i]);
        i++;
    }
    EEPROMwrite(address + i , '\0');
}

//read 1024 bytes starting from the given address
char* EEPROMreadstr(unsigned int address){
    char* data = (char*)malloc(1024) ;
    int i = 0 ;
    while(i < 1024){
        char dataRead = EEPROMread(address + i);
        data[i] = dataRead;
        i++;
    }

    return data;
}