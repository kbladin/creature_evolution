#include <iostream>
#include <vector>

#include "gtest/gtest.h"
#include "Chromosome.h"



/* *
* Test class for Creature
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

TEST_F(ChromosomeTest, CrossOverTest) {

	std::vector<float> v1(Chromosome::GENE_LENGTH);
	std::vector<float> v2(Chromosome::GENE_LENGTH);

	for (int i = 0; i < v1.size(); ++i){
		v1[i] = i;
		v2[i] = -i;
	}

	Chromosome c1(v1);
	Chromosome c2(v2);

	std::vector<Chromosome> children = c1.CrossOverMate(c2);

	std::cout << "Mom: " << c1 << std::endl;
	std::cout << "Dad: " << c2 << std::endl;

	std::cout << "Child 1: " << children[0] << std::endl;
	std::cout << "Child 2: " << children[1] << std::endl;

	//EXPECT_EQ(0,0);
}

TEST_F(ChromosomeTest, MutateTest) {
	std::cout << "Choromosome: " << c << std::endl;
	c.Mutate(1);
	std::cout << "Mutation: " << c << std::endl;

}

TEST_F(ChromosomeTest, GetGeneTest) {

	std::vector<float> v(10);

	for (int i = 0; i < v.size(); ++i){
		v[i] = i;
	}

	Chromosome c1(v);		

	std::cout << "Vector v: " << v << std::endl;
	std::cout << "Choromosome: " << c1 << std::endl;
	std::cout << "GetGene(): " << c1.GetGene() << std::endl;

	//EXPECT_EQ(0,0);
}