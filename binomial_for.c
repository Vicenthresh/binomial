#include <limits.h>
#include "binomial.h"

static long binomial(long n, long k) {
  long c = 1, i;
  
  if (k > n-k) // take advantage of symmetry
    k = n-k;
  
  for (i = 1; i <= k; i++, n--) {
    if (c/i >= ULONG_MAX/n) // return 0 on potential overflow
      return 0;
      
    c = c / i * n + c % i * n / i;  // split c * n / i into (c / i * i + c % i) * n / i
  }
  
  return c;
}

binomial_fn get_binomial_for() {
	// Even though the `binomial` function is not directly
	// visible in other compilation units, we can still
	// return a pointer to the function (actually a pointer
	// to the code).
	return binomial;
}