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
#include <time.h>

typedef struct large_number //estructura de datos utilizada
{
    long array_length, current_array_length;
    char *n;
} lnumber;

typedef struct aux_div 
{
    lnumber sum;
    char amount;
    int q_is_zero; 
} aux_div;

lnumber InitLargeNumber(char *num, int array_length, int current_array_length, int num_length);
void Usage(char *message);
void PrintNumber(lnumber number);
lnumber LargeRussianMult1(lnumber n1, lnumber n2, int free1, int free2);
lnumber LargeRussianMult2(lnumber n1, lnumber n2, int free1, int free2);
lnumber LargeDivByTwo(lnumber number);
lnumber LargeSum11(lnumber n1, lnumber n2, lnumber result);
lnumber LargeSum12(lnumber n1, lnumber n2, lnumber result);
lnumber LargeDivision(lnumber n1, lnumber n2);
char isNumber(char c);
int IsBigger(lnumber n1, lnumber n2);

//lnumber LargeDiff11(lnumber n1, lnumber n2, lnumber result);
lnumber LargeDiff11(lnumber n1, lnumber n2, char add_to_end);
lnumber LargeLongDivision(lnumber n1, lnumber n2);
lnumber NumberToDiv(lnumber n1, lnumber n2, lnumber result);
aux_div AuxLargeDivision(lnumber n1, lnumber n2);
int IsBiggerDiv(lnumber n1, lnumber n2);

/*
 *
 */
int main(int argc, char **argv) {

    lnumber n1, n2, result;
    long len1 = 0, len2 = 0, c, runs,i;
    double stime;

	if ( argc == 1 ) {

        c = getchar();
        while(c != '\n'){
            len1 = len1 + 1;
            c = getchar();
        }

        while(c != EOF){
            len2 = len2 + 1;
            c = getchar();
        }
        len2 = len2 - 1;

        rewind(stdin);

        char num1[len1];
        scanf("%s", num1); 
        //n1 = InitLargeNumber(num1, len1, len1, len1);

        char num2[len2];
        scanf("%s", num2);
        //n2 = InitLargeNumber(num2, len2, len2, len2);

        result = InitLargeNumber("0", n2.current_array_length, 1, 1);

        //printf("\n Large Long Division: \n");
        //result = LargeLongDivision(n1, n2);

        //PrintNumber(result);

        //printf("\n Large Sum Division: \n");
        //result = LargeDivision(n1, n2);

        //PrintNumber(result);
        //printf("\n\n%s \nx \n%s= \n ", n1.n, n2.n);
        runs = 10000;
        clock_t cl = clock();
        
        for(i = 0; i < runs; i++){
            n1 = InitLargeNumber(num1, len1, len1, len1);
            n2 = InitLargeNumber(num2, len2, len2, len2);
            result = LargeRussianMult2(n1, n2, 0, 0);
        }
        stime = (((double)clock()-cl)/CLOCKS_PER_SEC)/(double)runs;
        PrintNumber(result);
        printf("Tiempo transcurrido SMult: %lf\n", stime);
        //printf("\n");

        /*
        printf("\n****** Start Div by Two ****** \n");
        LargeDivByTwo(n1);

        printf("\n****** End Div by Two ****** \n");
        printf("\n****** Start Div Large ****** \n");
        LargeDivision(n1, n2);

        printf("\n****** End Div ****** \n");
        //PrintNumber(result);
        printf("\n");
        */
  	}
   	else
    	Usage(argv[0]);

    
}  

/*
 *
 */
char *ReadData(int n) {

    unsigned int i;
    char *number;
   
    number = calloc(n,sizeof(char)); // allocate memory

    for ( i = 0; i < n; i = i + 1 )
        scanf("%c", &number[i]);

   return number;
}

/*
 * 
 */
void Usage(char *message) {
  
    printf("\nUsage: %s < numbers.txt", message);
}  

lnumber InitLargeNumber(char *num, int array_length, int current_array_length, int num_length){
    
    int i, j, k = 0;
    lnumber number;
    number.n = calloc(array_length,sizeof(char)); // allocate memory
    number.array_length = array_length;
    number.current_array_length = current_array_length;

    for(i = number.array_length-1, j = num_length-1, k; k < current_array_length; i = i - 1, j = j - 1, k = k + 1)
            number.n[i] = num[j];

    return number;
}

void PrintNumber(lnumber number) {

    unsigned long i = number.array_length - number.current_array_length;
    
    printf("\nNumber: \n");

    for (i; i < number.array_length; i++)
        if (isNumber(number.n[i]) == '1'){
            printf("%c",number.n[i]);
        }
    
    printf("\n");
    printf("\nArray_length: %ld ", number.array_length);
    printf("\nCurrent_array_length: %ld \n\n", number.current_array_length);
}

/*
 * n1 >= n2 en digitos
 */

lnumber LargeRussianMult2(lnumber n1, lnumber n2, int free1, int free2) {

    if (n1.current_array_length >= n2.current_array_length)
        return LargeRussianMult1(n1, n2, free1, free2);
    return LargeRussianMult1(n2, n1, free2, free1);
}

lnumber LargeRussianMult1(lnumber n1, lnumber n2, int free1, int free2) {
    lnumber result, n2_new; 
    int i, j;

    result = InitLargeNumber("0", n1.array_length + n2.array_length, 1, 1);

    n2_new = InitLargeNumber(n2.n, n1.array_length + n2.array_length, n2.current_array_length, n2.array_length);

    while ( n1.current_array_length > 0 ){
        if ((n1.n[n1.array_length-1] - '0') % 2 != 0)
            result = LargeSum12(result, n2_new, result);
        
        n2_new = LargeSum12(n2_new, n2_new, n2_new);

        n1 = LargeDivByTwo(n1);
    }

    if (free1 == 1)
        free(n1.n);

    if (free2 == 1)
        free(n2.n);

    //free(n2_new.n);

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

    //int index_number = 0, current_array_length = 0, flag = 0;
    int index_number = number.array_length - number.current_array_length, current_array_length = 0, flag = 0;
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
    number.array_length = number.array_length - number.current_array_length + current_array_length;
    number.current_array_length = current_array_length;

    // falta caso cuando el divisor es mas grande q number

    return number;
}

char isNumber(char c){
    if (c >= '0' && c <= '9')
        return '1';
    return '0';
}

/*
 * if n1 > n2 returns 1, else if n1 == n2 returns 0, else if n1 < n2 returns -1
 */
int IsBigger(lnumber n1, lnumber n2){

    if (n1.current_array_length > n2.current_array_length) 
        return 1;
    else if (n1.current_array_length < n2.current_array_length)
        return -1;
    else{ 
        unsigned int i, j;

        i = n1.array_length - n1.current_array_length;
        j = n2.array_length - n2.current_array_length;
                        
        for (i, j; i < n1.array_length; i = i + 1, j = j + 1) {
            if (n1.n[i] > n2.n[j])
                return 1;
            
            else if (n1.n[i] < n2.n[j])
                return -1;    
        }
    }

    return 0;
}


lnumber LargeDivision(lnumber n1, lnumber n2){

    lnumber result = InitLargeNumber("0", n1.current_array_length - n2.current_array_length + 1, 1, 1);
    lnumber large_one = InitLargeNumber("1", 1, 1, 1);
    lnumber n2_new = InitLargeNumber(n2.n, n1.current_array_length + 1, n2.current_array_length , n2.array_length);

    while (IsBigger(n1, n2_new) > -1){

        result = LargeSum12(result, large_one, result);

        n2_new = LargeSum12(n2_new, n2, n2_new);
    }

    free(n2_new.n);
    free(large_one.n);

    return result;
}


// n1 > n2
lnumber LargeDiff11(lnumber n1, lnumber n2, char add_to_end){

    long i = n1.array_length -1, j = n2.array_length-1, k, current_length = 0, p, count_zeros = 0;
    unsigned int flag = 0;
    lnumber result;
    
    if (add_to_end != 'n'){
        char s[] = {add_to_end};
        flag = 1;
        result = InitLargeNumber(s, n1.current_array_length + flag, 1, 1);

        //if (add_to_end == '0')
            //count_zeros = count_zeros + 1;
    }
    else
        result = InitLargeNumber("0", n1.current_array_length, 1, 1); 

    k = result.array_length-1-flag;

    char carry = '0', partial_diff;

    p = n2.array_length - n2.current_array_length;
    while (j >= p){
        partial_diff = (n1.n[i] - '0') - (n2.n[j] - '0') -  (carry - '0');

        if ( partial_diff < '0' - '0' ){
            partial_diff =  partial_diff + 10;
            carry = '1';
        }
        else
            carry = '0';


        result.n[k] = partial_diff + '0';

        if ( result.n[k] == '0' )
            count_zeros = count_zeros + 1;
        else
            count_zeros = 0;

        current_length = current_length + 1;


        i = i - 1;
        j = j - 1;
        k = k - 1;
    }

    p = n1.array_length - n1.current_array_length;
    while ( i >= p ){

        //partial_diff = n1.n[i] - '0' +  carry - '0';

        if (n1.n[i] == '0' && carry == '1')
            result.n[k] = '9';
        else{
            partial_diff = (n1.n[i] - '0') - (carry - '0');
            if ( i >= p || carry > '0')
                result.n[k] = partial_diff + '0';
            carry = '0';  
        }

        if ( result.n[k] == '0' )
            count_zeros = count_zeros + 1;
        else
            count_zeros = 0;

        current_length = current_length + 1;


        i = i - 1;
        k = k - 1;
    }

    if (current_length == count_zeros)
        result.current_array_length = 1;
    else
        result.current_array_length = current_length - count_zeros + flag;

    return result;
}

lnumber NumberToDiv(lnumber n1, lnumber n2, lnumber result){
    long i = result.array_length - 1, k = result.array_length-1, p = 0;

    while (p < result.array_length){

        result.n[k] = n1.n[i];

        i = i - 1;
        k = k - 1;
        p = p + 1;    
    }

    result.current_array_length = result.array_length;//result.array_length;

    return result;
}

aux_div AuxLargeDivision(lnumber n1, lnumber n2){

    aux_div ad;

    lnumber n2_new = InitLargeNumber(n2.n, n1.current_array_length + 1, n2.current_array_length , n2.array_length);
    int r = 0, is_bigger;
    
    is_bigger = IsBigger(n1, n2_new);
    
    if (is_bigger == -1){
        ad.sum = InitLargeNumber("0", 1, 1, 1); 
        ad.amount = 0 + '0';
        ad.q_is_zero = 1;

        return ad;
    }

    //PrintNumber(n1);

    while ( is_bigger > 0){

        r = r + 1;
        n2_new = LargeSum12(n2_new, n2, n2_new);
        is_bigger = IsBigger(n1, n2_new);
    }

    if (is_bigger == 0){
        ad.q_is_zero = 1;
        r = r + 1;
    }
    else
        ad.q_is_zero = 0; 

    //printf("\nAmount %d\n", r);
    //free(n2_new.n);
    //free(large_one.n);
    //return r;

    ad.sum = n2_new;
    ad.amount = r + '0';


    return ad;
}

int IsBiggerDiv(lnumber n1, lnumber n2){

    unsigned int i, j;

    i = n1.array_length - n1.current_array_length;
    j = n2.array_length - n2.current_array_length;
                    
    for (i, j; j < n2.array_length; i = i + 1, j = j + 1) {
        if (n1.n[i] > n2.n[j])
            return 1;
        else if (n1.n[i] < n2.n[j])
            return -1;   
    }

    return 0;
}


lnumber LargeLongDivision(lnumber n1, lnumber n2){

    lnumber result = InitLargeNumber("0", n1.current_array_length - n2.current_array_length + 1, 1, 1), number_to_div;
    aux_div aux;
    long index_result = 0, index_n1, current_array_length = 0;

    long flag = 0;

    if ( IsBiggerDiv(n1, n2) == -1 )
        flag = 1;
    
    number_to_div = InitLargeNumber("0", n2.current_array_length + flag, 1, 1);
    number_to_div = NumberToDiv(n1, n2, number_to_div);

    index_n1 = n1.array_length - n1.current_array_length + number_to_div.current_array_length - 1;

    while (n1.array_length > index_n1) {

        aux = AuxLargeDivision(number_to_div, n2);

        result.n[index_result] = aux.amount;

        index_result = index_result + 1;

        if (aux.q_is_zero == 0)
            aux.sum = LargeDiff11(aux.sum, n2, 'n');


        index_n1 = index_n1 + 1;
        number_to_div = LargeDiff11(number_to_div, aux.sum, n1.n[index_n1]);

        current_array_length = current_array_length + 1;
    }


    result.array_length = current_array_length;
    result.current_array_length = current_array_length;

    // falta caso cuando el divisor es mas grande q number

    return result;
} 


/*


// n1 > n2
lnumber LargeDiff11(lnumber n1, lnumber n2, lnumber result){

    long i = n1.array_length -1, j = n2.array_length-1, k = result.array_length-1, current_length = 0, p, count_zeros = 0;
    char carry = '0', partial_diff;

    p = n2.array_length - n2.current_array_length;
    while (j >= p){
        partial_diff = (n1.n[i] - '0') - (n2.n[j] - '0') -  (carry - '0');

        if ( partial_diff < '0' - '0' ){
            partial_diff =  partial_diff + 10;
            carry = '1';
        }
        else
            carry = '0';


        result.n[k] = partial_diff + '0';

        if ( result.n[k] == '0' )
            count_zeros = count_zeros + 1;
        else
            count_zeros = 0;

        current_length = current_length + 1;


        i = i - 1;
        j = j - 1;
        k = k - 1;
    }

    p = n1.array_length - n1.current_array_length;
    while ( i >= p ){

        //partial_diff = n1.n[i] - '0' +  carry - '0';

        if (n1.n[i] == '0' && carry == '1')
            result.n[k] = '9';
        else{
            partial_diff = (n1.n[i] - '0') - (carry - '0');
            if ( i >= p || carry > '0')
                result.n[k] = partial_diff + '0';
            carry = '0';  
        }

        if ( result.n[k] == '0' )
            count_zeros = count_zeros + 1;
        else
            count_zeros = 0;

        current_length = current_length + 1;


        i = i - 1;
        k = k - 1;
    }

    if (current_length == count_zeros)
        result.current_array_length = 1;
    else
        result.current_array_length = current_length - count_zeros;

    return result;
}


*/