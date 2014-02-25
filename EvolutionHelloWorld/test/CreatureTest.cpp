#include <iostream>

#include "gtest/gtest.h"
#include "Creature.h"

/* *
* Test class for Creature
*/
class CreatureTest : public ::testing::Test {
protected:
	CreatureTest() {

	}

	virtual ~CreatureTest() {

	}

	virtual void SetUp() {

	}

	virtual void TearDown() {

	}
	
	Creature c;
};

TEST_F(CreatureTest, TestFitnessFunction_PerfectMatch) {
	Creature c_target("Hello, world!");
	EXPECT_EQ(0,c_target.GetFitness());
}

TEST_F(CreatureTest, TestFitnessFunction_OneOff) {
	Creature c_one_off_target("Hdllo, world!");
	EXPECT_EQ(1,c_one_off_target.GetFitness());
}

TEST_F(CreatureTest, TestFitnessFunction_TwoOff) {
	Creature c_two_off_target("Hcllo, world!");
	EXPECT_EQ(2,c_two_off_target.GetFitness());
}

TEST_F(CreatureTest, PrintMutation) {
	Creature mutated = c.Mutate();
	std::cout << mutated.GetGene() << std::endl;
}

TEST_F(CreatureTest, PrintMating) {
	Creature mutated = c.Mutate();
	std::vector<Creature> children = c.Mate(mutated);

	std::cout << "Original: " << c.GetGene() << std::endl;
	std::cout << "Mutated: " << mutated.GetGene() << std::endl;

	std::cout << "Child 1: " << children[0].GetGene() << std::endl;
	std::cout << "Child 2: " << children[1].GetGene() << std::endl;
}

TEST_F(CreatureTest, PrintRandomCreature) {
	Creature random_Creature = Creature::random();
	std::cout << "Random Creature: " << random_Creature.GetGene() << std::endl;
}

TEST_F(CreatureTest, PrintThreeRandomCreature) {
	Creature random_Creature1 = Creature::random();
	std::cout << "Random Creature: " << random_Creature1.GetGene() << std::endl;
	Creature random_Creature2 = Creature::random();
	std::cout << "Random Creature: " << random_Creature2.GetGene() << std::endl;
	Creature random_Creature3 = Creature::random();
	std::cout << "Random Creature: " << random_Creature3.GetGene() << std::endl;
}

TEST_F(CreatureTest, TestMixedMating) {
	Creature c1 = Creature::random();
	Creature c2 = Creature::random();

	Creature child = c1.MixMate(c2);

	std::cout << "Mom : " << c1.GetGene() << std::endl;
	std::cout << "Dad : " << c2.GetGene() << std::endl;
	std::cout << "Child : " << child.GetGene() << std::endl;
}