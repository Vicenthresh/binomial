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
#include <pthread.h>

typedef struct large_number //estructura de datos utilizada
{
    long array_length, current_array_length, free1, free2;
    char *n;
} lnumber;

struct Message {
    int myid, steps;
    lnumber x, y, result; 
};

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

void *PLargeRussianMult(void *p);

lnumber LargeDivByTwo(lnumber number);
lnumber LargeSum11(lnumber n1, lnumber n2, lnumber result);
lnumber LargeSum12(lnumber n1, lnumber n2, lnumber result);
lnumber LargeDivision(lnumber n1, lnumber n2);
//long LargeDivision(lnumber n1, lnumber n2);
lnumber LargeTwoPowerN(long n);
long TotalSteps(lnumber n1);
char isNumber(char c);

int IsBigger(lnumber n1, lnumber n2);


lnumber LargeDiff11(lnumber n1, lnumber n2, char add_to_end, int free1, int free2);
lnumber LargeLongDivision(lnumber n1, lnumber n2);
lnumber NumberToDiv(lnumber n1, lnumber n2, lnumber result);
aux_div AuxLargeDivision(lnumber n1, lnumber n2);
int IsBiggerDiv(lnumber n1, lnumber n2);

lnumber LargeTwoExpBySquaring(long n);
 /*
 *
 */
int main(int argc, char **argv) {
    
    long k, n, p, i, s, rem, j, flag = 0;
    long total_steps, last_steps = 0;

    long len1 = 0, len2 = 0, c;
    lnumber n1, n2, result, result2, x_aux, y_aux, acum_pow2;

    pthread_t *thread;
    pthread_attr_t attribute;
    struct Message **m;
    void *exit_status; 
    
    if ( argc == 2 ) {

        p = atoi(argv[1]); // p is the number of threads
    
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
        n1 = InitLargeNumber(num1, len1, len1, len1);

        char num2[len2];
        scanf("%s", num2);
        n2 = InitLargeNumber(num2, len2, len2, len2);

        total_steps = TotalSteps(n1);

        if (total_steps < p) // special case when total_steps < threads
            p = total_steps; 


        //printf("\nTotal Steps: %ld\n", total_steps);
        //result = LargeTwoExpBySquaring(total_steps);       

        
        thread = calloc(p, sizeof(pthread_t));
        m = calloc(p, sizeof(struct Message *)); // Initializing m 
        for ( i = 0; i < p; i = i + 1 )
            m[i] = calloc(1,sizeof(struct Message));
    
        pthread_attr_init(&attribute); 
        pthread_attr_setdetachstate(&attribute, PTHREAD_CREATE_JOINABLE);
        
        s = total_steps / p; 
        rem = total_steps % p;
        x_aux = InitLargeNumber(n1.n, n1.array_length, n1.current_array_length, n1.current_array_length);
        y_aux = InitLargeNumber(n2.n, n2.array_length, n2.current_array_length, n2.current_array_length);


        for ( i = 0; i < p; i = i + 1 ) {
            //printf("\n****** Start Process: %ld  ******\n", i);
            
            m[i]->myid = i;

            if ( rem != 0 ) { 
                
                m[i]->steps = s + 1;
                rem = rem - 1;
            }
            else
                m[i]->steps = s;

            if (i == 0 ) {
                m[i]->x = InitLargeNumber(n1.n, n1.array_length, n1.current_array_length, n1.current_array_length);
                m[i]->y = InitLargeNumber(n2.n, n2.array_length, n2.current_array_length, n2.current_array_length);


                if (i + 1 < p ){
                    last_steps = m[i]->steps; 
                    //printf("\nStart Pow Process: %ld  \n", i);
                    acum_pow2 = LargeTwoPowerN(m[i]->steps);
                    //printf("\nEnd Pow Process: %ld  \n", i);
                }

            }
            else {

                //printf("\nStart Division Process: %ld  \n", i);
                m[i]->x = LargeLongDivision(x_aux, acum_pow2);
                //m[i]->x = LargeDivision(x_aux, acum_pow2);
                //printf("\nEnd Division Process: %ld  \n", i);
                x_aux = InitLargeNumber(m[i]->x.n, m[i]->x.array_length, m[i]->x.current_array_length, m[i]->x.array_length);


                m[i]->y = LargeRussianMult2(y_aux, acum_pow2, 0, 0); // cubierto
                y_aux = InitLargeNumber(m[i]->y.n, m[i]->y.array_length, m[i]->y.current_array_length, m[i]->y.array_length);
            }

            if (i + 1 < p && last_steps != m[i]->steps){

                last_steps = m[i]->steps; 
                acum_pow2 = LargeDivByTwo(acum_pow2); // cubierto
            }

            //printf("\n****** End Process: %ld ******\n", i);
            pthread_create(&thread[i], &attribute, PLargeRussianMult, (void *) m[i]); // se crea el proceso
        }
        
        pthread_attr_destroy(&attribute);
        
        result = InitLargeNumber("0", n1.array_length + n2.array_length, 1, 1);
        for ( i = 0; i < p; i = i + 1 ) {

            pthread_join(thread[i], &exit_status); // get back the results from the i-th thread 
            m[i] = (struct Message *) exit_status;
            //PrintNumber(m[i]->result);
            result = LargeSum12(result, m[i]->result, result);
            free(m[i]->result.n);
        }
        
        PrintNumber(result);
    }
   else
      Usage(argv[0]);
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

/*
 * 
 */
void Usage(char *message) {
  
    printf("\nUsage: %s < numbers.txt \n", message);
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

    //PrintNumber(n1);
    //PrintNumber(n2);

    lnumber result, n2_new; 

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
    //PrintNumber(result);
    return result;
}




void *PLargeRussianMult(void *p) {

    struct Message *m;
    m = (struct Message *) p;

    lnumber result, n2_new; 
    int i = 0, j;

    result = InitLargeNumber("0", m->x.array_length + m->y.array_length, 1, 1);
    n2_new = InitLargeNumber(m->y.n, m->x.array_length + m->y.array_length, m->y.current_array_length, m->y.array_length);

    while ( i <  m->steps ){
        if ((m->x.n[m->x.array_length-1] - '0') % 2 != 0)
            result = LargeSum12(result, n2_new, result);
        
        n2_new = LargeSum12(n2_new, n2_new, n2_new);

        m->x = LargeDivByTwo(m->x);
        i = i + 1;
    }

    free(m->x.n);
    free(m->y.n);

    m->result = result;

    //free(n2_new.n);

    pthread_exit((void *) m); 
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


// lnumber LargeDivision(lnumber n1, lnumber n2){
//long LargeDivision(lnumber n1, lnumber n2){
lnumber LargeDivision(lnumber n1, lnumber n2){

    lnumber result = InitLargeNumber("0", n1.current_array_length - n2.current_array_length + 1, 1, 1);
    lnumber large_one = InitLargeNumber("1", 1, 1, 1);
    lnumber n2_new = InitLargeNumber(n2.n, n1.current_array_length + 1, n2.current_array_length , n2.array_length);
    //long r = 0;

    while (IsBigger(n1, n2_new) > -1){

        result = LargeSum12(result, large_one, result);

        n2_new = LargeSum12(n2_new, n2, n2_new);
    }

    free(n2_new.n);
    free(large_one.n);
    //return r;
    return result;
}


lnumber LargeTwoPowerN(long n){ //liberar memoria

    lnumber result = InitLargeNumber("1", 1, 1, 1);
    lnumber large_two = InitLargeNumber("2", 1, 1, 1);
    unsigned long i = 0;

    while (i < n){
        
        result = LargeRussianMult2(result, large_two, 1, 0);

        i = i + 1;
    }

    return result;
}

long TotalSteps(lnumber n1) {

    lnumber n1_aux; 
    long steps = 0;

    n1_aux = InitLargeNumber(n1.n, n1.array_length, n1.current_array_length, n1.current_array_length);

    while ( n1_aux.current_array_length > 0 ){
        steps = steps + 1;
        n1_aux = LargeDivByTwo(n1_aux);
    }

    //free(n1_aux.n);

    return steps;
}


// n1 > n2
lnumber LargeDiff11(lnumber n1, lnumber n2, char add_to_end, int free1, int free2){

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

    if (free1 == 1)
        free(n1.n);

    if (free2 == 1)
        free(n2.n);

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
            aux.sum = LargeDiff11(aux.sum, n2, 'n', 1, 0);

        index_n1 = index_n1 + 1;
        number_to_div = LargeDiff11(number_to_div, aux.sum, n1.n[index_n1], 1, 0);

        current_array_length = current_array_length + 1;
    }


    result.array_length = current_array_length;
    result.current_array_length = current_array_length;

    free(number_to_div.n); // lo creo
    // falta caso cuando el divisor es mas grande q number

    return result;
} 

/*
lnumber LargeTwoExpBySquaring(long n){

    lnumber x, y;

    if (n == 0)
        return InitLargeNumber("1", 1, 1, 1);
    
    x = InitLargeNumber("2", 1, 1, 1);
    y = InitLargeNumber("1", 1, 1, 1);

    while (n > 1) {
        if ( n % 2 == 0){
            x = LargeRussianMult2(x, x, 0, 0);

            n = n / 2;
        }
        else{

            y = LargeRussianMult2(x, y, 0, 0);
            x = LargeRussianMult2(x, x, 0, 0);

            n = (n-1) / 2;
        }
    }

    return LargeRussianMult2(x, y, 0, 0);
}

lnumber LargeTwoExpBySquaring(long n){

    lnumber x, y;

    if (n == 0)
        return InitLargeNumber("1", 1, 1, 1);
    
    x = InitLargeNumber("2", 1, 1, 1); // base
    y = InitLargeNumber("1", 1, 1, 1); // ans

    while (n > 0) {
        if ( n % 2 != 0){
            y = LargeRussianMult2(y, x, 0, 0);

            n = n - 1;
        }
        else{

            x = LargeRussianMult2(x, x, 0, 0);
            //x = LargeRussianMult2(x, x, 0, 0);

            n = n / 2;
        }
    }

    return y;
}
*/