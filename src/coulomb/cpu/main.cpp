#include <iostream>
#include <random>

#include "DoubleLoop.h"

#ifdef USE_FLOAT
using real = float;
#else
using real = double;
#endif

int main() {
  int N_particles = 10;
  int N_samples = 1;
  real step_size = 1e-2;
  std::cout << "Calculating potential & forces between " << N_samples
            << " randomly placed (x, y, z) points [0, 100], with random charges [-1, 1]. " 
            << "Also evaluated at " << N_samples << " random perturbations sized " << step_size << "." << std::endl;

  std::mt19937 gen(12345);  // fixed seed for reproducibility
  std::uniform_real_distribution<real> dist_pos(0.0, 100.0);
  std::uniform_real_distribution<real> dist_charge(-1.0, 1.0);
  std::uniform_real_distribution<real> dist_step(-step_size, step_size);
  real* Q = new real[N_particles];
  real* X = new real[3*N_particles*N_samples];
  real* G = new real[3*N_particles*N_samples];
  // First sample
  for(int i = 0; i < N_particles; i++){
    Q[i] = dist_charge(gen);
    int pos = 3*i;
    X[pos] = dist_pos(gen); 
    X[pos+1] = dist_pos(gen); 
    X[pos+2] = dist_pos(gen); 
  }
  // Subsequent samples
  for(int i = 1; i < N_samples; i++){
    int sample_start = 3*N_particles*i;
    for(int j = 0; j < N_particles; j++){
      int pos = sample_start + 3*j;
      int init_pos = 3*j;
      X[pos] = X[init_pos] + dist_step(gen); 
      X[pos+1] = X[init_pos+1] + dist_step(gen);
      X[pos+2] = X[init_pos+2] + dist_step(gen);
    }
  }

  // Run N^2 algorithm
  std::cout << "Running N_particles^2 double-loop algorithm:" << std::endl;
  if (N_particles < 1000){
    DoubleLoop<real>::run(N_particles, N_samples, Q, X, G);
  } else {
    std::cout << "N_particles is too large to use naive algorithm!" << std::endl;
  }

  // Run N
  free(Q);
  free(X);
  free(G);
  return 0;
}
