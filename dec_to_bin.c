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

int main(){

    unsigned int len1 = 0, len2 = 0;
    lnumber d, b;

    char a[] = {"100"};
    len1 = strlen(a);
    d.n = a;
    d.array_length = len1;
    d.current_array_length = len1;

    len2 = ceil(len1*(log(10)/log(2))); //max number of bits a len1-digit number can have

    printf("%s \n\n", d.n);

    d = LargeDivByTwo(d);

    printf("%s \n\n", d.n);

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