#ifndef __BINOMIAL_H__
#define __BINOMIAL_H__

#include <cstdlib>
#include <cstdio>

// The `binomial` concept.
// A class that implements the `binomial` concept shall define a static method
// named `binomial` with the signature
//     static long binomial(long n, long k);

// The slow binomial strategy is defined in binomial_slow.hpp.
// Implements the `binomial` concept.
class binomial_slow;

// The fast binomial strategy is defined in binomial_fast.hpp.
// Implements the `binomial` concept.
class binomial_fast;

#endif /*__BINOMIAL_H__*/
