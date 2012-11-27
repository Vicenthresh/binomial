#include "binomial.h"

int main(/*int argc, char ** argv*/) {
	while (1) {
		binomial_fn fn;
		printf("Choose a binomial implementation.\n"
		       "1. Slow\n"
		       "2. Fast\n"
		       "Input [12]: ");
		int strat;
		if (scanf("%d", &strat) != 1) {
			printf("Bye.\n");
			break;
		}
		if (strat == 1) {
			fn = get_binomial_slow();
		} else if (strat == 2) {
			fn = get_binomial_fast();
		} else {
			printf("Unknown strategy.\n");
			continue;
		}
		long n, k;
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
		printf("Result: ");
		printf("%ld\n\n", fn(n, k));
	}
	return 0;
}
