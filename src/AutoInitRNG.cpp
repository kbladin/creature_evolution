#include "AutoInitRNG.h"

AutoInitRNG::AutoInitRNG() {
	mt_rng_.seed(time(0));
}
