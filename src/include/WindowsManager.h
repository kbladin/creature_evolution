#ifndef WINDOWSMANAGER_H
#define WINDOWSMANAGER_H
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "CreatureEvolution.h"
#include "ShaderManager.h"

class WindowsManager {
private:
	
	GLFWwindow* glfw_window_;
	CreatureEvolution* ce_;

public:
	WindowsManager(int width, int height, CreatureEvolution* ce);
	~WindowsManager(void); 

	void setVariables();
	void GLEWInit();
	void DisplayAndRender();


};


#endif // WINDOWSMANAGER_H