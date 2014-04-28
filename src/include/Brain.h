#ifndef BRAIN_H
#define BRAIN_H

//C++
#include <vector>
#include <cmath>
//Internal
#include "AutoInitRNG.h"
#include "SettingsManager.h"

typedef std::vector<float> f_vec;

class Brain {

public:
  Brain(){}
  Brain(int n_input, int n_output);
  f_vec CalculateOutput(const f_vec& input);

  void Mutate();
  std::vector<Brain> Crossover(Brain mate);

private:
  std::vector<f_vec> hidden_nodes_;
  std::vector<f_vec> output_nodes_;
  static AutoInitRNG rng_;

  float dot(const f_vec& x, const f_vec& y);
  float transfer(float x);
};

#endif //BRAIN_H
