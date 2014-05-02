#ifndef CREATURE_H
#define CREATURE_H

#include <QObject>
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
#include "AutoInitRNG.h"
#include "SettingsManager.h"

// TO DO : ändra SimData så den sparar värden som vi vill mäta!

struct SimData {
    float distance_forward;
    float max_height;
    float held_height;
    float deviation_x;
    float energy_efficiency;

    SimData() {
        distance_forward = 0.0f;
        max_height = 0.0f;
        held_height = 0.0f;
        deviation_x = 0.0f;
        energy_efficiency = 0.0f;
    }
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
    Brain GetBrain();
    Body GetBody();
    void Mutate();

    SimData GetSimData();
    void SetSimData(SimData);
    void UpdateDeviationX(float deviationx);
    void UpdateDistanceForward(float dist);
    void UpdateMaxHeight(float height);
    void UpdateEnergy(float energy);

    std::vector<Creature> Crossover(Creature mate);

private:
    float fitness_;
    Brain brain_;
    Body body_;
    SimData simdata_;

    static AutoInitRNG rng_;

};
Q_DECLARE_METATYPE(Creature);

//! Simple struct for creature comparison
struct CreatureLargerThan {
    bool operator()(const Creature& c1,const Creature& c2) const {
        float c1_fitness = c1.GetFitness();
        float c2_fitness = c2.GetFitness();

        return (c1_fitness > c2_fitness);
    }
};

#endif // CREATURE_H
