#ifndef BRAIN_H
#define BRAIN_H

#include <vector>

class Brain {
public:
  Brain();
  //void SetInputs(int);
  //void SetOutputs(int);
  std::vector<float> CalculateOutput(std::vector<float>);

private:
 std::vector<float> weights;

};

#endif //BRAIN_H
