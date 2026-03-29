#include "FastFourierTransform.hpp"

/*
 * FAST FOURIER TRANSFORM FOR FUCK'S SAKE
 *
 * @in array of floats going in
 * @stride double to keep track of iterations
 * @out array of float of freqs going out
 * @n starts as sample amount and halves as stride doubles
 */
void fft_ffs(const std::complex<float> in[], std::size_t stride,
			 std::complex<float> out[], std::size_t n) {
	if (n == 1) {
		out[0] = in[0];
		return;
	}

	fft_ffs(in, stride * 2, out, n / 2);
	fft_ffs(in + stride, stride * 2, out + n / 2, n / 2);

	for (std::size_t k = 0; k < n / 2; k++) {
		float				t = (float)k / n;
		std::complex<float> v =
			exp(-TAU * (std::complex<float>)1i * t) * out[k + n / 2];
		std::complex<float> e = out[k];
		out[k] = e + v;
		out[k + n / 2] = e - v;
	}
}

const std::vector<std::complex<float>> int16_normalize_float(
	const std::int16_t *samples, std::size_t N) {
	std::vector<std::complex<float>> arr(SAMPLES);
	for (std::size_t i = 0; i < SAMPLES && i < N; i++) {
		arr[i] = static_cast<std::complex<float>>(normalize(samples[i]) *
												  flat_top_window(i, N));
	}
	return arr;
}
