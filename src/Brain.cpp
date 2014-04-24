#include "Brain.h"
#include "SettingsManager.h"
#define M_PI 3.14159265359

#include <iostream>

AutoInitRNG Brain::rng_;

Brain::Brain(int n_input, int n_output) {
    std::uniform_real_distribution<float> r_w(-1.0f, 1.0f);

    int n_hidden = 20;
    hidden_nodes_ = std::vector<f_vec>(n_hidden, f_vec(n_input));
    output_nodes_ = std::vector<f_vec>(n_output, f_vec(n_hidden));

    //init random weights
    for(f_vec& v : hidden_nodes_) {
        for(float& w : v) {
            w = r_w(rng_.mt_rng_);
        }
    }

    for(f_vec& v : output_nodes_) {
        for(float& w : v) {
            w = r_w(rng_.mt_rng_);
        }
    }
}

std::vector<float> Brain::CalculateOutput(const f_vec& input){
    f_vec output(output_nodes_.size());
    std::vector<float> hidden_output(hidden_nodes_.size());

    std::vector<f_vec>::const_iterator h_node_iter = hidden_nodes_.begin();
    for(float& out : hidden_output) {
        out = transfer(dot(input,(*h_node_iter)));
        ++h_node_iter;
    }

    std::vector<f_vec>::const_iterator o_node_iter = output_nodes_.begin();
    for(float& out : output) {
        out = transfer(dot(hidden_output,(*o_node_iter)));
        ++o_node_iter;
    }

    return output;
}

void Brain::Mutate() {
    std::normal_distribution<float> normal_dist(
                0.0f,
                SettingsManager::Instance()->GetMutationSigma());
    std::uniform_real_distribution<float> int_dist(0.0f,1.0f);

    //mutate
    for(f_vec& v : hidden_nodes_) {
        for(float& w : v) {
            float should_mutate = int_dist(rng_.mt_rng_);
            if (SettingsManager::Instance()->GetMutationInternal() >= should_mutate){
                w += normal_dist(rng_.mt_rng_);
            }
        }
    }

    for(f_vec& v : output_nodes_) {
        for(float& w : v) {
            float should_mutate = int_dist(rng_.mt_rng_);
            if (SettingsManager::Instance()->GetMutationInternal() >= should_mutate){
                w += normal_dist(rng_.mt_rng_);
            }
        }
    }
}

std::vector<Brain> Brain::Crossover(Brain mate){
    std::vector<Brain> children;
    children.resize(2);
    children[0] = *this;
    children[1] = mate;
    return children;
}

float Brain::dot(const f_vec& x, const f_vec& y) {
    float dot_product = 0;
    f_vec::const_iterator x_iter = x.begin();
    for(float y_el : y) {
        dot_product += y_el*(*x_iter);
        ++x_iter;
    }
    return dot_product;
}

float Brain::transfer(float x) {
    float e_px = exp(x);
    float e_mx = exp(-x);
    return (e_px - e_mx)/(e_px + e_mx);
}
