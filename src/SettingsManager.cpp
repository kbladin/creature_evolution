#include "SettingsManager.h"

SettingsManager* SettingsManager::instance_ = NULL;

SettingsManager* SettingsManager::Instance() {
  if (!instance_) // only allow one instance of class to be generated
    instance_ = new SettingsManager();
  return instance_;
}

//! Constructor
SettingsManager::SettingsManager(){

  rotation_sensitivity_ = M_PI * 2.0f;
  // set default values
  population_size_ = 10;
  max_generations_ = 20;
  crossover_ratio_ = 0.8;
  elitism_ratio_ = 0.2;

  mutation_ratio_ = 0.8;
  mutation_ratio_internal_ = 0.2;
  mutation_sigma_ = 0.1;
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
float SettingsManager::GetMutationInternal(){
  return mutation_ratio_internal_;
}
float SettingsManager::GetMutationSigma(){
  return mutation_sigma_;
}
int SettingsManager::GetFrameWidth(){
  return frame_width_;
}
int SettingsManager::GetFrameHeight(){
  return frame_height_;
}
float SettingsManager::GetRotationSensitivity(){
  return rotation_sensitivity_;
}
Vec3 SettingsManager::GetMainBodyDimension(){
  return main_body_dim_;
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
void SettingsManager::SetMutationInternal(float mutation_ratio_internal){
  if(mutation_ratio_internal < 0.0f || mutation_ratio_internal > 1.0f){
    mutation_ratio_internal_ = glm::clamp(mutation_ratio_internal, 0.0f,1.0f);
    std::cout << "WARNING: internal mutation ratio clamped to " << mutation_ratio_internal_ <<
      "!" << std::endl;
  }
  else
    mutation_ratio_internal_ = mutation_ratio_internal;
}
void SettingsManager::SetMutationSigma(float mutation_sigma){
  if(mutation_sigma < 0.0f || mutation_sigma > 1.0f){
    mutation_sigma_ = glm::clamp(mutation_sigma, 0.0f,1.0f);
    std::cout << "WARNING: mutation sigma ratio clamped to " << mutation_sigma_ <<
      "!" << std::endl;
  }
  else
    mutation_sigma_ = mutation_sigma;
}
void SettingsManager::SetFrameWidth(int frame_width){
  frame_width_ = frame_width;
}
void SettingsManager::SetFrameHeight(int frame_height){
  frame_height_ = frame_height;
}
void SettingsManager::SetRotationSensitivity(float sense){
  rotation_sensitivity_ = sense;
}

void SettingsManager::SetCreatureType(int creature){
  creature_type_ = creature; 

}
int SettingsManager::GetCreatureType(){
  return creature_type_; 
}

void SettingsManager::SetFitnessDistanceForward(float dist){
  fitness_distance_forward_ = dist;
}

float SettingsManager::GetFitnessDistanceForward(){
  return fitness_distance_forward_; 
}

void SettingsManager::SetFitnessMaxHeight(float height){
  fitness_max_height_ = height;
}

float SettingsManager::GetFitnessMaxHeight(){
  return fitness_max_height_; 
}

void SettingsManager::SetFitnessEnergy(float energy){
  fitness_energy_ = energy;
}

float SettingsManager::GetFitnessEnergy(){
  return fitness_energy_; 
}

// void SettingsManager::AddBestCreature(Creature creature) {
//   best_creatures_.push_back(creature);
// }

// Creature SettingsManager::GetBestCreature() {
//   return best_creatures_.back();
// }

// std::vector<Creature> SettingsManager::GetAllBestCreatures() {
//   return best_creatures_;
// }

void SettingsManager::SetMainBodyDimension(Vec3 vec){
  main_body_dim_ = vec;
}

