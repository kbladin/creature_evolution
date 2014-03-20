#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <Creature.h>
#include "SettingsManager.h"

class Population {
private:
	std::vector<Creature> pop_; 
	int population_size_;

public:
	Population();
	Population(int pivot, const Population &oldPopulation);
	
	void Sort() ;

	Creature Get(int index) const;
	Creature GetBest() const; 
	int size() const;
	
	void Add(int index, Creature c);
};


#endif // POPULATION_H