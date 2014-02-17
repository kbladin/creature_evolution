#include <iostream>

#include "gtest/gtest.h"
#include "../src/Chromosome.h"
#include "../src/Population.h"
/* *
* Test class for Chromosome
*/
class PopulationTest : public ::testing::Test {
protected:
	PopulationTest() {

	}

	virtual ~PopulationTest() {

	}

	virtual void SetUp() {

	}

	virtual void TearDown() {

	}

};

TEST_F(PopulationTest, PrintSortedFitness) {
	Population p(20,10,5,50);
	std::vector<Chromosome> chromosomes = p.GetChromosomes();
	for(int i = 0; i < chromosomes.size(); ++i) {
		std::cout << chromosomes[i].GetFitness() << std::endl;
	}
}