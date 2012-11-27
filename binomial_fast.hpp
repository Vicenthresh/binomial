#include "binomial.h"

class binomial_fast {
public:
// In a class, the static keyword means the same as in Java: the method should
// not be called on an instance of the class, but rather on the class itself.
static long binomial(long n, long k) {
	if (k == 0 || n == k) return 1;

	if (n > k && k > 0) return binomial(n, k-1)*(n-k+1)/k;

	return 0;
}

};
