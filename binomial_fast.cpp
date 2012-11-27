#include "binomial.h"

// The unnamed namespace is not visible in other compilation units.
namespace {

class binomial_impl : public binomial_t {
public:
// The virtual keyword is implied since the base class has a corresponding
// virtual method, so it is not necessary, but may be used for clarity.
// The override keyword (C++11 feature) is not supported by all mainstream
// compilers, so you might want to comment it out until it does get mainstream
// support.
virtual long binomial(long n, long k) /*override*/ {
	if (k == 0 || n == k) return 1;

	if (n > k && k > 0) return binomial(n, k-1)*(n-k+1)/k;

	return 0;
}

// The following definition is redundant, since our base class already defines
// a virtual destructor, meaning we have a default virtual destructor as well.
// The virtual keyword is implied as above.

//virtual ~binomial_impl() {
//}

};

} // unnamed namespace

binomial_t * get_binomial_fast() {
	// Even though the `binomial_impl` class is not directly
	// visible in other compilation units, we can still
	// instantiate it in here and have other compilation units
	// destruct it due to the virtual destructor.
	return new binomial_impl();
}
