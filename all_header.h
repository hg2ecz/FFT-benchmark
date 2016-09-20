#include <complex.h>

// step: N*N
void dft(int log2point, double complex *xy_out, const double complex *xy_in);

// step: N*log2(N)
void fft    (int log2point, double complex *xy_out, const double complex *xy_in);
void fftw   (int log2point, double complex *xy_out, /*const*/ double complex *xy_in, int fft_repeat);
