#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "AutoInitRNG.h"
#include <iostream>
#include <string>

class Chromosome {
public:
	Chromosome(std::string gene_code);
private:
	std::string gene_code_;
};

#endif // CHROMOSOME_H