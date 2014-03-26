
// External
#include "gtest/gtest.h"
#include "GL/glew.h"
#include "GL/glfw3.h"

// Internal
#include "ShaderManager.h"

class ShaderManagerTest : public ::testing::Test {
protected:
	ShaderManagerTest() {
	}

	virtual ~ShaderManagerTest() {
	}

	virtual void SetUp() {

	}

	virtual void TearDown() {

	}
};

TEST_F(ShaderManagerTest, shader_manager_test) {
  
  GLFWwindow* window;
  //Initialize the library
  if (!glfwInit())
    std::cout << "could not init glfw" << std::endl;
  
  // We want the newest version of OpenGL
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  // Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    std::cout << "could not create window" << std::endl;
  }
  
	// Make the window's context current
  glfwMakeContextCurrent(window);
  
  glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
    std::cout << "could not init glew" << std::endl;
	}

  ShaderManager::Instance();
  
}
