#include <Box.h>
#include "gtest/gtest.h"
#include <Shape.h>

class ShapeTest : public ::testing::Test {
protected:
	ShapeTest() {
	}

	virtual ~ShapeTest() {
	}

	virtual void SetUp() {

	}

	virtual void TearDown() {

	}

	
};

TEST_F(ShapeTest, SetupShape) {
	Box box;
	box.DebugPrint();
}