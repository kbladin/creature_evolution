#ifndef BRAIN_H
#define BRAIN_H

//C++
#include <vector>
#include <cmath>
//Internal
#include "AutoInitRNG.h"

class Brain {
public:
  Brain();
  virtual void ResizeInput(int);
  virtual void ResizeOutput(int);
  virtual std::vector<float> CalculateOutput(std::vector<float> input);
  virtual void Mutate();

  std::vector<float> GetWeights();
  std::vector<Brain> Crossover(Brain mate);

private:
  std::vector<float> weights;
  static AutoInitRNG rng_;
};

#endif //BRAIN_H
