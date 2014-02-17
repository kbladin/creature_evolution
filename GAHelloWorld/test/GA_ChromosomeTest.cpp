#include <iostream>

#include "gtest/gtest.h"
#include "../src/Chromosome.h"
#include "../src/Population.h"
/* *
* Test class for Chromosome
*/
class ChromosomeTest : public ::testing::Test {
protected:
	ChromosomeTest() {

	}

	virtual ~ChromosomeTest() {

	}

	virtual void SetUp() {

	}

	virtual void TearDown() {

	}
	
	Chromosome c;
};

TEST_F(ChromosomeTest, TestFitnessFunction_PerfectMatch) {
	Chromosome c_target("Hello, world!");
	EXPECT_EQ(0,c_target.GetFitness());
}

TEST_F(ChromosomeTest, TestFitnessFunction_OneOff) {
	Chromosome c_one_off_target("Hdllo, world!");
	EXPECT_EQ(1,c_one_off_target.GetFitness());
}

TEST_F(ChromosomeTest, TestFitnessFunction_TwoOff) {
	Chromosome c_two_off_target("Hcllo, world!");
	EXPECT_EQ(2,c_two_off_target.GetFitness());
}

TEST_F(ChromosomeTest, PrintMutation) {
	Chromosome mutated = c.Mutate();
	std::cout << mutated.GetGene() << std::endl;
}

TEST_F(ChromosomeTest, PrintMating) {
	Chromosome mutated = c.Mutate();
	std::vector<Chromosome> children = c.Mate(mutated);

	std::cout << "Original: " << c.GetGene() << std::endl;
	std::cout << "Mutated: " << mutated.GetGene() << std::endl;

	std::cout << "Child 1: " << children[0].GetGene() << std::endl;
	std::cout << "Child 2: " << children[1].GetGene() << std::endl;
}

TEST_F(ChromosomeTest, PrintRandomChromosome) {
	Chromosome random_chromosome = Chromosome::random();
	std::cout << "Random chromosome: " << random_chromosome.GetGene() << std::endl;
}

TEST_F(ChromosomeTest, PrintThreeRandomChromosome) {
	Chromosome random_chromosome1 = Chromosome::random();
	std::cout << "Random chromosome: " << random_chromosome1.GetGene() << std::endl;
	Chromosome random_chromosome2 = Chromosome::random();
	std::cout << "Random chromosome: " << random_chromosome2.GetGene() << std::endl;
	Chromosome random_chromosome3 = Chromosome::random();
	std::cout << "Random chromosome: " << random_chromosome3.GetGene() << std::endl;
}