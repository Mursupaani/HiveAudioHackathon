#pragma once
#include <vector>
#include <cmath>
#include <cstdint>
#include <limits>
#include <complex>

using namespace std::complex_literals;

#define TAU 6.283185f

const int SAMPLES = 4096;

/*
 * FAST FOURIER TRANSFORM FOR FUCK'S SAKE
 *
 * @in array of floats going in
 * @stride double to keep track of iterations
 * @out array of float of freqs going out
 * @n starts as sample amount and halves as stride doubles
 */
void fft_ffs(const std::complex<float> in[], std::size_t stride, std::complex<float> out[], std::size_t n);


template <typename T>
constexpr float normalize (T value) {
  return value < 0
    ? -static_cast<double>(value) / std::numeric_limits<T>::min()
    :  static_cast<double>(value) / std::numeric_limits<T>::max()
    ;
}

const std::vector<std::complex<float>> int16_normalize_float(const std::int16_t *samples);