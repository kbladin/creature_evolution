#include "Brain.h"
#define M_PI 3.14159265359

AutoInitRNG Brain::rng_;

Brain::Brain() {
    std::uniform_real_distribution<float> float_mutate(-1.0f, 1.0f);

    for(int i=0; i<(9*3); i++) {
        float w = (float_mutate(rng_.mt_rng_));
        weights.push_back(w);
    }
}

void Brain::ResizeInput(int n){
    //only one input allowed for this brain
}

void Brain::ResizeOutput(int n){
    weights.resize(n);
}

std::vector<float> Brain::CalculateOutput(std::vector<float> input){
    float in = input.front();
    std::vector<float> output;
    for(int i=0; i<(weights.size() / 3); i++) {
        int n_freqs = 10;
        float max_freq = 2/3.0f;
        //float freq = floor(weights[i*3] * n_freqs) * max_freq; 
        float freq = pow(2, ceil(log(abs(1 / weights[i*3]) + 0.001f)/log(2)));  // 1,2,4,8...
        float amp = weights[i*3+1];
        float phase = weights[i*3+2]*M_PI*2;
        float out = amp * sin(freq*in + phase);
        output.push_back(out);
    }
    return output;
}

void Brain::Mutate() {
    std::uniform_real_distribution<float> float_mutate(-0.3f, 0.3f);
    std::uniform_int_distribution<int> weight_index(0, weights.size()-1);

    float mutation = (float_mutate(rng_.mt_rng_));
    int random_index = weight_index(rng_.mt_rng_);

    //float mutation = ( ( (float)rng_.mt_rng_()/rng_.mt_rng_.max() ) - 0.5 ) * 0.6;
//    weights[random_index] += mutation;

    for(int i = 0; i < weights.size(); ++i) {
        weights[i] += mutation;
        weights[i] = (weights[i] < -1.0f) ? -1.0f : ((weights[i] > 1.0f) ? 1.0f : weights[i]);
    }

}

std::vector<float> Brain::GetWeights(){
    return weights;
}

std::vector<Brain> Brain::Crossover(Brain mate){
    std::vector<Brain> children;
    children.resize(2);

    // get two pivot points
    std::uniform_int_distribution<int> dist_index_first(0,weights.size()-1);
    //std::uniform_int_distribution<int> dist_index_second(0,mate.GetWeights().size()-1);
    int pivot_point_first = dist_index_first(rng_.mt_rng_);
    //int pivot_point_second = dist_index_second(rng_.mt_rng_);

    // TODO: change so not use for-loops!!
    for(int i=0; i<pivot_point_first; i++)
        children[0].weights[i] = weights[i];
    for(int j=pivot_point_first; j<weights.size(); j++)
        children[0].weights[j] = mate.GetWeights()[j];
    for(int i=0; i<pivot_point_first; i++)
        children[1].weights[i] = mate.GetWeights()[i];
    for(int j=pivot_point_first; j<weights.size(); j++)
        children[1].weights[j] = weights[j];


    // TODO: use crossover-ratio. if should be done or not.


    return children;
}

