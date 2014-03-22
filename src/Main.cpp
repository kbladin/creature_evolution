
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

int main() {

	// SettingsManager::Instance()->setMaxGenerations(2);
	// SettingsManager::Instance()->setPopulationSize(2);
	// SettingsManager::Instance()->setCrossover(0.8f);
	// SettingsManager::Instance()->setElitism(0.2f);
	// SettingsManager::Instance()->setMutation(0.8f);

	CreatureEvolution* CE = new CreatureEvolution();
	WindowsManager* WM = new WindowsManager(640,480, CE);
	
	WM->setVariables();
	CE->Run();
	WM->DisplayAndRender();

	delete CE;
	delete WM;


	return 0;
}