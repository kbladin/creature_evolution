#include "Brain.h"
#include "SettingsManager.h"
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

AutoInitRNG Brain::rng_;

//! The constructor of the Brain creates a brain with number of inputs and number of outputs defined.
/*!
  The number of hidden nodes in the neural network is currently hard coded to
  5*n_input/n_output. all weights in the neural network gets random values
  between -1.0 and 1.0.
\param n_input is the number of inputs to the network.
\param n_output is the number of outputs from the network (should match the
number of Joints for the creatures body.)
*/
Brain::Brain(int n_input, int n_output) {
  std::uniform_real_distribution<float> r_w(-1.0f, 1.0f);
  int n_hidden = 5*n_input/n_output;
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

//! Calculating the output of the neural network
/*!
  If the number of nodes are not the right size, the brain is re-initialized
  to batch the number of inputs. 
  \param An std::vector of floats which corresponds to the input.
  \return An std::vector of floats which corresponds to the output.
*/
std::vector<float> Brain::CalculateOutput(const f_vec& input){
  if(hidden_nodes_[0].size() != input.size()) { //reset brain with right size
    std::uniform_real_distribution<float> r_w(-1.0f, 1.0f);
    int n_input = input.size();
    int n_output = output_nodes_.size();
    int n_hidden = n_input+n_output; // Va??
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
    // What should be done about this?
    //std::cout << "WRONG INITAL INPUT SIZE TO BRAIN!";
  }

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

//! Brains own definition of mutation.
/*!
  This function uses mutation ratio and mutation strength defined in
  SettingsManager. Mutation strength is used to define a uniform float
  distribution with which to change the values of the weights in the neural
  network of the Brain. The bigger value of mutation strength, the bigger the
  span is for the values to be changed to. Mutation ratio is used to determine
  the chance of a specific weight to mutate.
*/
void Brain::Mutate() {
  std::uniform_real_distribution<float> int_dist(0.0f,1.0f);

  float mutationStrength = SettingsManager::Instance()->GetMutationSigma();
  std::uniform_real_distribution<float> mut_val(-1.0f*mutationStrength, 1.0f*mutationStrength);

  //mutate
  for(f_vec& v : hidden_nodes_) {
    for(float& w : v) {
      float should_mutate = int_dist(rng_.mt_rng_);
      if (SettingsManager::Instance()->GetMutationInternal() >= should_mutate){
        w += mut_val(rng_.mt_rng_);
      }
    }
  }

  for(f_vec& v : output_nodes_) {
    for(float& w : v) {
      float should_mutate = int_dist(rng_.mt_rng_);
      if (SettingsManager::Instance()->GetMutationInternal() >= should_mutate){
        w += mut_val(rng_.mt_rng_);
      }
    }
  }
}

//! This function is currently not implemented for the NN-Brain
/*!
  Crossover should return two children from two parents. For the neural
  network-Brain there is not necessarily a meaningful way to do this.
  Currently this function returns back the two parents.
  \param Another Brain with which to crossover this Brain.
  \return An std::vector of two Brains. Currently these are the same as the
  parents.
*/
std::vector<Brain> Brain::Crossover(Brain mate){
  std::vector<Brain> children;
  children.resize(2);
  children[0] = *this;
  children[1] = mate;
  return children;
}

//! Internal function used for calculating the output of the Brain.
/*!
  Normal dot product for multi-dimensional vectors. In this case the ones
  that are used as connections between nodes (lists of weights). These vectors
  should be of the same dimension.
  \param x is the first input vector.
  \param y is the second input vector.
  \return The dot product between the two input vectors.
*/
float Brain::dot(const f_vec& x, const f_vec& y) {
  float dot_product = 0;
  f_vec::const_iterator x_iter = x.begin();
  for(float y_el : y) {
    dot_product += y_el*(*x_iter);
    ++x_iter;
  }
  return dot_product;
}

//! Apply the transfer function to a float value.
/*!
  This transfer function is a sigmoid function.
  \param x is the input value of the transfer function
  \return The output value of the transfter function.
*/
float Brain::transfer(float x) {
  float e_px = exp(x);
  float e_mx = exp(-x);
  return (e_px - e_mx)/(e_px + e_mx);
}