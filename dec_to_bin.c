#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct large_number //estructura de datos utilizada
{
    unsigned int array_length, current_array_length;
    char *n;
} lnumber;

lnumber LargeDivByTwo(lnumber number);
void PrintNumber(lnumber number);
char isNumber(char c);

int main(){

    unsigned int len1 = 0, len2 = 0;
    lnumber d, bin;
    int i=0;

    char a[] = {"42"};
    len1 = strlen(a);
    d.n = a;
    d.array_length = len1;
    d.current_array_length = len1;

    len2 = ceil(len1*(log(10)/log(2))); //max number of bits a len1-digit number can have
    
    bin.n = calloc(len2,sizeof(char)); // allocate memory
    bin.array_length = len2;
    bin.n[bin.array_length-1] = '0';
    bin.current_array_length = 1;

    PrintNumber(d);
    
    while ( d.array_length > 0 ){
        bin.n[i] = (char)(d.n[d.array_length-1] - '0') % 2 ;
        d = LargeDivByTwo(d);
        i++;
    }

    PrintNumber(bin);


    return 0;
}

lnumber LargeDivByTwo(lnumber number){

    int index_number = 0, current_array_length = 0, flag = 0;
    int number_to_div = number.n[index_number] - '0';

    while ( number_to_div < 2) {
        flag = 1;
        index_number = index_number + 1;
        number_to_div = number_to_div * 10 + (number.n[index_number] - '0');
    }

    while (number.array_length > index_number) {

        number.n[index_number-flag] = (number_to_div / 2) + '0';
        current_array_length = current_array_length + 1;

        index_number = index_number + 1;

        number_to_div = (number_to_div % 2) * 10 + number.n[index_number] - '0';
    }

    number.array_length = current_array_length;
    // falta caso cuando el divisor es mas grande q number

    return number;
}

void PrintNumber(lnumber number) {

    unsigned int i, size = 0;
    
    //printf("\nNumber: ");

    for (i = 0; i < number.array_length; i++)
        if (isNumber(number.n[i]) == '1'){
            printf("%c", number.n[i]);
            //size = size + 1;
        }
    
    //printf("\nArray_length: %d \n\n", size);
}

char isNumber(char c){
    if (c >= '0' && c <= '9')
        return '1';
    return '0';
}