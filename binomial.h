#ifndef __BINOMIAL_H__
#define __BINOMIAL_H__

#include <stdlib.h>
#include <stdio.h>

// `binomial_fn` is the type of a function pointer accepting two longs
// and returning a long.
typedef long (*binomial_fn)(long n, long k);

// The slow binomial function is defined in binomial_slow.c.
binomial_fn get_binomial_slow();

// The fast binomial function is defined in binomial_fast.c.
binomial_fn get_binomial_fast();

// Only static functions may be defined (rather than declared) in header files.
// The linker does not care share static function definitions between
// compilation units.
static inline void error(const char * message) {
	printf("An error occurred: %s\n", message);
	exit(1);
}

#endif /*__BINOMIAL_H__*/
