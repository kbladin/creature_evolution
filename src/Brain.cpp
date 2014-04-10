#include "Brain.h"

Brain::Brain() {
    for(int i=0; i<5; i++) {
        float w = (float)rng_.mt_rng_()/rng_.mt_rng_.max();
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
    for(int i=0; i<weights.size(); i++) {
        float out = sin(in+weights[i]*6.3);
        output.push_back(out);
    }
    return output;
}

void Brain::Mutate() {
    std::uniform_real_distribution<float> float_mutate(0.0f, 1.0f);
    std::uniform_int_distribution<int> weight_index(0, weights.size()-1);
    float mutation = ( ( (float)rng_.mt_rng_()/rng_.mt_rng_.max() ) - 0.5 ) * 0.6;
    weights[rng_.mt_rng_()%weights.size()] += mutation;

    // for(int i = 0; i < weights.size(); ++i) {
    //     float mutation = (float_mutate(rng_.mt_rng_) - 0.5f) * 0.6f;
    //     weights[i] += mutation;
    // }

}
