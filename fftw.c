#include <complex.h>
#include <fftw3.h>
#include "all_header.h"

// Public function
void fftw(int log2point, double complex *xy_out, /*const*/ double complex *xy_in, int fft_repeat) {
    int i;
    int point = 1<<log2point;
    fftw_plan plan_forward;
    plan_forward = fftw_plan_dft_1d(point, xy_in, xy_out, FFTW_FORWARD, FFTW_ESTIMATE );
    // only fft_execure repeated
    for (i=0; i<fft_repeat; i++) fftw_execute ( plan_forward );
    fftw_destroy_plan ( plan_forward );
}
