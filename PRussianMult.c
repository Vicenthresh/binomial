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


struct Message {
    int myid, steps;
    long x, y, result; 
};


long RussianMult(long n, long k);
int Log2Ceil(long x);
void *PRussianMult(void *p);
void Usage(char *message);

/*
 *
 */
int main(int argc, char **argv) {
    
    int k, n, p, i, s, rem, j, flag = 0;
    int total_steps, last_steps = 0, acum_pow2, x_aux, y_aux;
    long result = 0, X, Y;

    pthread_t *thread;
    pthread_attr_t attribute;
    struct Message **m;
    void *exit_status; 
    
    if ( argc == 2 ) {

        p = atoi(argv[1]); // p is the number of threads
    
    //READ X AND Y TO COMPUTE X x Y
        scanf("%ld", &X);
        scanf("%ld", &Y);

        total_steps = Log2Ceil(X);

        if (total_steps < p) // special case when total_steps < threads
            p = total_steps;        
        
        thread = calloc(p, sizeof(pthread_t));
        m = calloc(p, sizeof(struct Message *)); // Initializing m 
        for ( i = 0; i < p; i = i + 1 )
            m[i] = calloc(1,sizeof(struct Message));
    
        pthread_attr_init(&attribute); 
        pthread_attr_setdetachstate(&attribute, PTHREAD_CREATE_JOINABLE);
        
        s = total_steps / p; 
        rem = total_steps % p;
        x_aux = X;
        y_aux = Y;

        for ( i = 0; i < p; i = i + 1 ) {
            
            m[i]->myid = i;

            if ( rem != 0 ) { 
                
                m[i]->steps = s + 1;
                rem = rem - 1;
            }
            else
                m[i]->steps = s;

            if (i == 0 ) {
                m[i]->x = x_aux;
                m[i]->y = y_aux;

                if (i + 1 < p ){
                    last_steps = m[i]->steps; 
                    acum_pow2 = pow(2, m[i]->steps); // 
                }

            }
            else {
                m[i]->x = x_aux / acum_pow2; // con restas sucesivas?
                x_aux = m[i]->x;
                m[i]->y = y_aux * acum_pow2; // cubierto
                y_aux = m[i]->y;
            }

            if (i + 1 < p && last_steps != m[i]->steps){

                last_steps = m[i]->steps; 
                acum_pow2 = acum_pow2 / 2; // cubierto
            }

            pthread_create(&thread[i], &attribute, PRussianMult, (void *) m[i]); // se crea el proceso
        }
        
        pthread_attr_destroy(&attribute);
        
        for ( i = 0; i < p; i = i + 1 ) {
            
            pthread_join(thread[i], &exit_status); // get back the results from the i-th thread 
            m[i] = (struct Message *) exit_status;
            result = result + m[i]->result;
        }

        printf("\n%ld x %ld = %ld\n", X, Y, result);
    }
   else
      Usage(argv[0]);
}  
     


long RussianMult(long n, long k){
    
    long sum = 0;

    while(k > 0){
        if(k % 2 == 1) 
            sum = sum + n;

        n = n << 1; // n = n x 2
        k = k >> 1; // k = floor(k/2)
    }

    return sum;
}

void *PRussianMult(void *p){
    
    long sum = 0;
    int i = 0;

    struct Message *m;
    m = (struct Message *) p;

    while(i < m->steps){
        if(m->x % 2 == 1) 
            sum = sum + m->y;

        m->y = m->y << 1; // n = n x 2
        m->x = m->x >> 1; // k = floor(k/2)
        i = i + 1;
    }

    m->result = sum;
    
    pthread_exit((void *) m);   
}

int Log2Ceil(long x){
    if (x == 2)
        return 2;
    else if ( x == 1 || x == 0)
        return 1;
    else
        return ceil(log(x)/log(2));
}

void Usage(char *message) {
  
   printf("\nUsage: %s p < datafile.txt", message);
   printf("\n\np is the number of threads\n\n");
} 