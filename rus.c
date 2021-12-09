#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

int main(/*int argc, char ** argv*/) {
    while(1){
        long res, n, k, i;
        bool overflow = false;
		printf("Input n: ");
		if (scanf("%ld", &n) != 1) {
			printf("Bye.\n");
			break;
		}
		printf("Input k: ");
		if (scanf("%ld", &k) != 1) {
			printf("Bye.\n");
			break;
		}

        res = 0;
        i = 0;

        while(k > 0){
            if(k % 2 == 1) {
                if(res > LONG_MAX - n){
                    printf("Integer overflow\n\n");
                    overflow = true;
                    goto end;
                }
                res = res + n;
            }

            i++;

            n = n << 1;
            k = k >> 1;
        }
        
        end:
        if(!overflow)
            printf("%ld\n\n", res);
    }

    return 0;
}