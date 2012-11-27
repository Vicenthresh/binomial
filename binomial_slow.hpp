#include "binomial.h"

class binomial_slow {
public:
// In a class, the static keyword means the same as in Java: the method should
// not be called on an instance of the class, but rather on the class itself.
static long binomial(long n, long k) {
	if (k == 0 || n == k) return 1;

	if (n > k && k > 0) return binomial(n-1, k) + binomial(n-1, k-1);

	return 0;
}

};
