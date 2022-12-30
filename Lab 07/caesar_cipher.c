/*
E / 18 / 173
Kasthuripitiya K.A.I.M.
*/

char* encrypt(char *message, int key){
    int i = 0;
    while (message[i] != '\0'){

        //If it is a capital letter
        if ((message[i] >= 'A') && (message[i] <= 'Z')){
            message[i] = 65 + (message[i] + key - 65) % 26;
        }

        //if it is a simple letter
        else if ((message[i] >= 'a') && (message[i] <= 'z')){
            message[i] = 97 + (message[i] + key - 97) % 26;
        }
        i++;
    }

    message[i] = '\0';
    
    //return the encrypted message
    return message;
}
