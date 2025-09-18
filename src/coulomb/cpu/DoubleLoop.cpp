#include <iostream>
#include <limits>

#include "DoubleLoop.h"

template <typename T>
DoubleLoop<T>::DoubleLoop(int N_particles, int N_samples, const T* Q, const T* X, T* G) 
: N_particles(N_particles), N_samples(N_samples), X(X), Q(Q), G(G){};

template <typename T>
bool almost_zero(T x) {
    return std::abs(x) < 1e-6;
}

template <typename T>
T DoubleLoop<T>::compute_potential(int sample){
  T potential = 0;
  int start = 3*this->N_particles*sample;
  for(int i = 0; i < this->N_particles; i++){
    T qi = this->Q[i];
    int pos_i = start + 3*i;
    T xi = this->X[pos_i];
    T yi = this->X[pos_i+1];
    T zi = this->X[pos_i+2];
    for(int j = i+1; j < this->N_particles; j++){
      T qj = this->Q[j];
      int pos_j = start + 3*j;
      T xj = this->X[pos_j];
      T yj = this->X[pos_j+1];
      T zj = this->X[pos_j+2];

      T qij = qi*qj;
      T dx = xj - xi;
      T dy = yj - yi;
      T dz = zj - zi;
      T rij = sqrt(dx*dx + dy*dy + dz*dz);
      if(almost_zero(rij)){ continue; }

      T rinv = ((T)1.0) / rij;
      T Uij = qij*rinv;
      potential += Uij;
    }
  }
  return potential;
}

template <typename T>
void DoubleLoop<T>::run(int N_particles, int N_samples, const T* Q, const T* X, T* G) {
  DoubleLoop method(N_particles, N_samples, Q, X, G); 
  for(int i = 0; i < N_samples; i++){
    T potential = method.compute_potential(i);
    std::cout << "Structure " << i << " potential energy: " << potential << std::endl;
  }
}

template class DoubleLoop<float>;
template class DoubleLoop<double>;