
// 🐢
#include "WindowsManager.h"
#include "SettingsManager.h"
#include "Evolution.h"
#include "Creature.h"
#include <iostream>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "WindowsManager.h"
#include "CreatureEvolution.h"
#include "ShaderManager.cpp"

int main() {

	CreatureEvolution* CE = new CreatureEvolution();
	WindowsManager* WM = new WindowsManager(640,480, CE);
	
  //Compile Shaders
  ShaderManager::Instance();
  
	WM->setVariables();
	CE->Run();
	WM->DisplayAndRender();

	delete CE;
	delete WM;

	return 0;
}