/*******************************************************************
 *
 * Nombre
 *
 * Programmer : 
 *
 * Fecha
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct large_number //estructura de datos utilizada
{
    unsigned int array_length, current_array_length;
    char *n;
} lnumber;

char *ReadData(int n);
void Usage(char *message);
void PrintNumber(lnumber number);
lnumber LargeRussianMult(lnumber n1, lnumber n2);
lnumber LargeDivByTwo(lnumber number);
lnumber LargeSum11(lnumber n1, lnumber n2, lnumber result);
lnumber LargeSum12(lnumber n1, lnumber n2, lnumber result);
char isNumber(char c);

/*
 *
 */
int main(int argc, char **argv) {

    unsigned int len1, len2;
    lnumber n1, n2, result;

	if ( argc == 1 ) {

        scanf("%d",&len1);
        n1.array_length = len1;
        n1.current_array_length = len1;
        char num1[len1];
        scanf("%s", num1); 
        n1.n = num1;

        scanf("%d",&len2);
        n2.array_length = len2;
        n2.current_array_length = len2;
        char num2[len2];
        scanf("%s", num2); 
        n2.n = num2;

        printf("\n\n%s x %s =  ", n1.n, n2.n);
        result = LargeRussianMult(n1, n2);
        PrintNumber(result);
        printf("\n\n");
  	}
   	else
    	Usage(argv[0]);

    
}  

/*
 * 
 */
void Usage(char *message) {
  
    printf("\nUsage: %s < numbers.txt", message);
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

/*
 * n1 >= n2 en digitos
 */
lnumber LargeRussianMult(lnumber n1, lnumber n2) {
    lnumber result; 
    int i, j;

    result.n = calloc(n1.array_length + n2.array_length,sizeof(char)); // allocate memory
    result.array_length = n1.array_length + n2.array_length;
    result.n[result.array_length-1] = '0';
    result.current_array_length = 1;

    char *n2_new;
    n2_new = calloc(n1.array_length + n2.array_length,sizeof(char));

    for(i = n2.array_length-1, j = n1.array_length + n2.array_length - 1; i >= 0; i--, j--){
        n2_new[j] = n2.n[i];
    }

    n2.n = n2_new;
    n2.current_array_length = n2.array_length;
    n2.array_length = n1.array_length + n2.array_length;

    while ( n1.array_length > 0 ){

        if ((n1.n[n1.array_length-1] - '0') % 2 != 0)
            result = LargeSum12(result, n2, result);
        
        n2 = LargeSum12(n2, n2, n2);

        n1 = LargeDivByTwo(n1);
    }

    return result;
}

lnumber LargeSum12(lnumber n1, lnumber n2, lnumber result) {

    if (n1.current_array_length >= n2.current_array_length)
        return LargeSum11(n1, n2, result);
    return LargeSum11(n2, n1, result);

}


lnumber LargeSum11(lnumber n1, lnumber n2, lnumber result){

    int i = n1.array_length -1, j = n2.array_length-1, k = result.array_length-1, current_length = 0, p;
    char carry = '0', partial_sum;

    p = n2.array_length - n2.current_array_length;
    while (j >= p){
        partial_sum = n1.n[i] - '0' + n2.n[j] - '0' +  carry - '0';

        if ( partial_sum <= '9' - '0' )
            carry = '0';
        else{
            partial_sum = partial_sum % 10;
            carry = '1';
        }

        result.n[k] = partial_sum + '0';
        current_length = current_length + 1;


        i = i - 1;
        j = j - 1;
        k = k - 1;
    }

    p = n1.array_length - n1.current_array_length;
    while ( i >= p ){

        partial_sum = n1.n[i] - '0' +  carry - '0';

        if ( partial_sum <= '9' - '0' )
            carry = '0';
        else{
            partial_sum =  partial_sum % 10;
            carry = '1';
        }

        //printf("\n %d %d\n", k, i);
        result.n[k] = partial_sum + '0';
        current_length = current_length + 1;


        i = i - 1;
        k = k - 1;
    }
    
    if ( carry == '1' ){
        result.n[k] = carry;
        current_length = current_length + 1;
    }

    result.current_array_length = current_length;

    return result;
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

char isNumber(char c){
    if (c >= '0' && c <= '9')
        return '1';
    return '0';
}


