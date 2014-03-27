#include "SettingsManager.h"

SettingsManager* SettingsManager::instance_ = NULL;

SettingsManager* SettingsManager::Instance() {
  if (!instance_) // only allow one instance of class to be generated
    instance_ = new SettingsManager();
  return instance_;
}

//! Constructor
SettingsManager::SettingsManager(){
  // set default values
  population_size_ = 10;
  max_generations_ = 5;
  crossover_ratio_ = 0.8;
  elitism_ratio_ = 0.2;
  mutation_ratio_ = 0.8;
}

//! Destructor
SettingsManager::~SettingsManager(void){
  delete instance_;
}

int SettingsManager::GetPopulationSize(){
  return population_size_;
}
int SettingsManager::GetMaxGenerations(){
  return max_generations_;
}
float SettingsManager::GetCrossover(){
  return crossover_ratio_;
}
float SettingsManager::GetElitism(){
  return elitism_ratio_;
}
float SettingsManager::GetMutation(){
  return mutation_ratio_;
}

// where should the control of all the variables lie?
// ex not smaller than 0 and some variables must med 0->1.
void SettingsManager::SetPopulationSize(int population_size){
  if(population_size <= 0){
    population_size_ = 1;
    std::cout << "WARNING: population size clamped to 1!" << std::endl;
  }
  else
    population_size_ = population_size; 
}
void SettingsManager::SetMaxGenerations(int max_generations){
  if(max_generations <= 0){
    max_generations_ = 1;
    std::cout << "WARNING: max genereations clamped to 1!" << std::endl;
  }
  else
    max_generations_ = max_generations; 
}
void SettingsManager::SetCrossover(float crossover_ratio){
  if(crossover_ratio < 0.0f || crossover_ratio > 1.0f){
    crossover_ratio_ = glm::clamp(crossover_ratio, 0.0f,1.0f);
    std::cout << "WARNING: crossover ratio clamped to " << crossover_ratio_ <<
      "!" << std::endl;
  }
  else
    crossover_ratio_ = crossover_ratio;
}
void SettingsManager::SetElitism(float elitism_ratio){
  if(elitism_ratio < 0.0f || elitism_ratio > 1.0f){
    elitism_ratio_ = glm::clamp(elitism_ratio, 0.0f,1.0f);
    std::cout << "WARNING: elitism ratio clamped to " << elitism_ratio_ <<
      "!" << std::endl;
  }
  else
    elitism_ratio_ = elitism_ratio;
}
void SettingsManager::SetMutation(float mutation_ratio){
  if(mutation_ratio < 0.0f || mutation_ratio > 1.0f){
    mutation_ratio_ = glm::clamp(mutation_ratio, 0.0f,1.0f);
    std::cout << "WARNING: mutation ratio clamped to " << mutation_ratio_ <<
      "!" << std::endl;
  }
  else
    mutation_ratio_ = mutation_ratio;
}
