#include "Population.h"
#include <algorithm>
#include <cmath>
#include <iterator>
AutoInitRNG Population::rng_;

Population::Population(int size, float crossover_ratio, float elitism_ratio,
					   float mutation_rate) {
	crossover_ = crossover_ratio;
	elitism_ = elitism_ratio;
	mutation_ = mutation_rate;

	chromosome_population_.resize(size);

	for(int i = 0; i < size; ++i)
	{
		chromosome_population_[i] = Chromosome::random();
	}

	//sort chromosomes
	std::sort(chromosome_population_.begin(), chromosome_population_.end(),
				ChromosomeLessThan());
}

Population::~Population(void)
{
}

std::vector<Chromosome> Population::GetChromosomes() {
	return chromosome_population_;
}

float Population::GetElitism() {
	return elitism_;
}
float Population::GetCrossover() {
	return crossover_;
}
float Population::GetMutation() {
	return mutation_;
}

void Population::Evolve() {
	//std::vector<Chromosome> buffer;
	//buffer.resize(chromosome_population_.size());
	std::uniform_real_distribution<float> crossover_decider(0,1);
	//buffer.resize(chromosome_population_.size());
	int top_candidates_pivot = (int) (chromosome_population_.size() * elitism_);

	std::vector<Chromosome>::const_iterator first = 
			chromosome_population_.begin();
	std::vector<Chromosome>::const_iterator last = 
			chromosome_population_.begin() + top_candidates_pivot;
	std::vector<Chromosome> buffer(&chromosome_population_[0],
			&chromosome_population_[top_candidates_pivot]);
	buffer.resize(chromosome_population_.size());
	//buffer(first,last);

	//std::copy(chromosome_population_.begin(),chromosome_population_.begin() + 
		//		top_candidates_pivot, std::back_inserter(buffer));

	while(top_candidates_pivot < buffer.size()-1) {
		if(crossover_decider(rng_.mt_rng_) <= crossover_) {
			std::vector<Chromosome> parents = SelectParents();
			std::vector<Chromosome> children = parents[0].Mate(parents[1]);

			if(crossover_decider(rng_.mt_rng_) <= mutation_) {
				buffer[top_candidates_pivot+1] = children[0].Mutate();
			} else {
				buffer[top_candidates_pivot+1] = children[0];
			}

			if(top_candidates_pivot < buffer.size()) {
				if(crossover_decider(rng_.mt_rng_) <= mutation_) {
					buffer[top_candidates_pivot] = children[1].Mutate();
				} else {
					buffer[top_candidates_pivot] = children[1];
				}
			}
		} else {
			if(crossover_decider(rng_.mt_rng_) <= mutation_) {
				buffer[top_candidates_pivot] = 
						chromosome_population_[1].Mutate();
			} else {
				buffer[top_candidates_pivot] = chromosome_population_[1];
			}
		}

		++top_candidates_pivot;
	}

	std::sort(buffer.begin(), buffer.end(), ChromosomeLessThan());

	chromosome_population_= buffer;
}

std::vector<Chromosome> Population::SelectParents() {
	std::vector<Chromosome> parents;
	parents.resize(2);
	std::uniform_int_distribution<int> int_dist_index_(0,
						chromosome_population_.size()-1);

	for (int i = 0; i < 2; ++i) {
		parents[i] = chromosome_population_[int_dist_index_(rng_.mt_rng_)];
		for (int j = 0; j < TOURNAMENT_SIZE_; ++j) {
			int idx = int_dist_index_(rng_.mt_rng_);
			if(chromosome_population_[idx].GetFitness() < 
										parents[i].GetFitness()) {
				parents[i] = chromosome_population_[idx];
			}
		}
	}

	return parents;
}