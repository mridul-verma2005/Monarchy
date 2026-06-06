char* int_to_string(int number){
    int digit;
    static char value[3];
    value[2] = '\0';
    value[1] = ' ';
    value[0] = ' ';
    if(number == 0){
        value[0] = '0';
        value[1] = '0';
        return value;
    }
        
    else{
        int i = 1;
        while(number > 0 && i >= 0){
            digit = number % 10;
            value[i] = '0' + digit;
            number /= 10;
            i--;
        }
    }
    if(value[0] == ' '){
        value[0] = '0';
    }
    
    return value;
}


int strlen_d(char* msg){
    int i = 0;
    while(msg[i] != '\0'){
        i++;
    }
    return i;
}



void concaternate(char* string_1 , char* string_2 ,char * result){
    int size_1 = strlen_d(string_1);
    int size_2 = strlen_d(string_2);
    int i = 0;
    int j = 0;
    while(string_1[i] != '\0'){
        result[i] = string_1[i];
        i++;
    }
    result[i]= ' '; 
    while(string_2[j] != '\0'){
        result[i + j + 1] = string_2[j];
        j++;
    }
    result[size_1 + size_2 + 1] = '\0';

}





