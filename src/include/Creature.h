#ifndef CREATURE_H
#define CREATURE_H

// C++
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
// Internal
#include "Brain.h"
#include "Body.h"

struct SimData {
    float distance;
};

//! A definition of a creature.

/*!
A creature contains a brain and a body.
*/
class Creature {
public:
    Creature();
    ~Creature();

    std::vector<float> CalculateBrainOutput(std::vector<float>);
    void SetFitness(float fitness);
    float GetFitness() const;
    void Mutate();

    SimData GetSimData();
    void SetSimData(SimData);

private:
    float fitness_;
    Brain brain_;
    SimData simdata_;

};

//! Simple struct for creature comparison
struct CreatureLargerThan {
    bool operator()(const Creature& c1,const Creature& c2) const {
        float c1_fitness = c1.GetFitness();
        float c2_fitness = c2.GetFitness();

        return (c1_fitness > c2_fitness);
    }
};

#endif // CREATURE_H
