#ifndef WINDOWSMANAGER_H
#define WINDOWSMANAGER_H
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SettingsManager.h"
#include "Simulation.h"
#include "Renderer.h"
#include "SceneManager.h"

class WindowsManager {
private:

	// storlek och upplösning sparas hör

public:
	WindowsManager(int width, int height);
	~WindowsManager(void); 

	void setVariables();
	void GLEWInit();
	void DisplayAndRender(Simulation* sim_world,
			SceneManager* scene, Renderer* renderer);

	GLFWwindow* glfw_window_;

};


#endif // WINDOWSMANAGER_H