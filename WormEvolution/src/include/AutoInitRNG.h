#ifndef AUTOINITRNG_H
#define AUTOINITRNG_H

#include <random>
#include <ctime>

class AutoInitRNG {
public:
	std::mt19937 mt_rng_;
	AutoInitRNG();
};

#endif // AUTOINITRNG_H