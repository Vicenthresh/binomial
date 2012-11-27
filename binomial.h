#ifndef __BINOMIAL_H__
#define __BINOMIAL_H__

#include <stdlib.h>
#include <stdio.h>

// `binomial_t` is the type of a binomial strategy.
class binomial_t {
public:
	virtual long binomial(long n, long k) = 0;

	// Base classes with virtual methods MUST have a virtual destructor.
	virtual ~binomial_t() {}
};

// The slow binomial strategy is defined in binomial_slow.cpp.
binomial_t * get_binomial_slow();

// The fast binomial strategy is defined in binomial_fast.cpp.
binomial_t * get_binomial_fast();

// Only static functions may be defined (rather than declared) in header files.
// The linker does not care share static function definitions between
// compilation units.
static inline void error(const char * message) {
	printf("An error occurred: %s\n", message);
	exit(1);
}

#endif /*__BINOMIAL_H__*/
