#pragma once

#include <cstddef>  // for size_t

template <typename T>
class DoubleLoop {
public:
  explicit DoubleLoop(int N_particle, int N_samples, const T* Q, const T* X, T* G);
  static void run(int N_particle, int N_samples, const T* Q, const T* X, T* G);
private:
  int N_particles;
  int N_samples;
  const T* Q;
  const T* X;
  T* G;
  T compute_potential(int sample);
};