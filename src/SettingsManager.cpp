#include "SettingsManager.h"

SettingsManager* SettingsManager::m_pInstance = nullptr;

SettingsManager* SettingsManager::Instance() {
	if (!m_pInstance) // only allow one instance of class to be generated
		m_pInstance = new SettingsManager();

	return m_pInstance;
}

//! Constructor
SettingsManager::SettingsManager(){
	// just set default values or nothing at the moment
	/*population_size_ = 10;
	max_generations_ = 5;
	crossover_ratio_ = 0.8;
	elitism_ratio_ = 0.2;
	mutation_ratio_ = 0.8;*/
}

//! Destructor
SettingsManager::~SettingsManager(void){
	delete m_pInstance;
}

// where should the control of all the variables lie? 
// ex not smaller than 0 and some variables must med 0->1.
void SettingsManager::setPopulationSize(int population_size){
	population_size_ = population_size; 
}
void SettingsManager::setMaxGenerations(int max_generations){
	max_generations_ = max_generations;
}
void SettingsManager::setCrossover(float crossover_ratio){
	crossover_ratio_ = crossover_ratio;
}
void SettingsManager::setElitism(float elitism_ratio){
	elitism_ratio_ = elitism_ratio;
}
void SettingsManager::setMutation(float mutation_ratio){
	mutation_ratio_ = mutation_ratio;
}

int SettingsManager::getPopulationSize(){
	return population_size_;
}
int SettingsManager::getMaxGenerations(){
	return max_generations_;
}
float SettingsManager::getCrossover(){
	return crossover_ratio_;
}
float SettingsManager::getElitism(){
	return elitism_ratio_;
}
float SettingsManager::getMutation(){
	return mutation_ratio_;
}