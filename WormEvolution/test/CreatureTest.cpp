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

TEST_F(CreatureTest, NothingTest) {
	std::cout << "Testing Nothing!";
	int val = 0;
	EXPECT_EQ(0,val);
}