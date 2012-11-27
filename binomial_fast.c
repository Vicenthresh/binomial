#include "binomial.h"

// A static function is not visible in other compilation units.
static long binomial(long n, long k) {
	if (k == 0 || n == k) return 1;

	if (n > k && k > 0) return binomial(n, k-1)*(n-k+1)/k;

	return 0;
}

binomial_fn get_binomial_fast() {
	// Even though the `binomial` function is not directly
	// visible in other compilation units, we can still
	// return a pointer to the function (actually a pointer
	// to the code).
	return binomial;
}
