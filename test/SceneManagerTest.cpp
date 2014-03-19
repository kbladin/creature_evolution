#include <iostream>
#include <vector>

#include "gtest/gtest.h"
#include "SceneManager.h"

class SceneManagerTest : public ::testing::Test {
protected:
	SceneManagerTest() {
		scene = new SceneManager(NULL);
	}

	virtual ~SceneManagerTest() {
		delete scene;
	}

	virtual void SetUp() {

	}

	virtual void TearDown() {

	}
	
	SceneManager* scene;
};

TEST_F(SceneManagerTest, SetupNoPhysicsTest) {
	EXPECT_EQ(NULL, scene->GetPhysicsWorld());
}