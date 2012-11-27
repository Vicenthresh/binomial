#include "binomial.h"
#include "binomial_fast.hpp"
#include "binomial_slow.hpp"

// The Binomial template argument must be a class that implements the
// `binomial` concept. See binomial.h.
template <typename Binomial>
bool go() {
	long n, k;
	printf("Input n: ");
	if (scanf("%ld", &n) != 1) {
		printf("Bye.\n");
		return false;
	}
	printf("Input k: ");
	if (scanf("%ld", &k) != 1) {
		printf("Bye.\n");
		return false;
	}
	printf("Result: ");
	printf("%ld\n\n", Binomial::binomial(n, k));
	return true;
}

int main(/*int argc, char ** argv*/) {
	while (1) {
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
			if (!go<binomial_slow>()) break;
		} else if (strat == 2) {
			if (!go<binomial_fast>()) break;
		} else {
			printf("Unknown strategy.\n");
		}
	}
	return 0;
}
