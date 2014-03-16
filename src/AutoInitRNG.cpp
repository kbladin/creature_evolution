#include "AutoInitRNG.h"
#include <ctime>

AutoInitRNG::AutoInitRNG() {
	mt_rng_.seed(time(0));
}
