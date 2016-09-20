#include <stdio.h>
#include "all_header.h"

#include <time.h>
#include <math.h>
static struct timespec gstart;

static void timestart() {
    int i;
    for (i=0; i<1000000; i++) {
	i+=10*sin(M_PI/i);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
}

static double timeend() {
    struct timespec gend;
    unsigned long long nsec;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);

    nsec = 1000ULL*1000*1000*(gend.tv_sec - gstart.tv_sec) + gend.tv_nsec - gstart.tv_nsec;
    return nsec/1000./1000.;
}

void printres(int i, double complex *d, char *txt) {
    printf("%3d %16.9f %16.9f %16.9f (%s)\n", i, creal(d[i]), cimag(d[i]), cabs(d[i]), txt);
}

#define SIZE (1<<LOG2FFTSIZE)

double complex xy[SIZE];
double complex xy_out_dft[SIZE];
double complex xy_out_dft_oddeven[SIZE];
double complex xy_out_fft[SIZE];
double complex xy_out_fftw[SIZE];

// dft_ LOGSIZE --> dft_12
//#define FUNCTION_NAME_MAKE(name, num)  name ## num
//#define FUNCTION_NAME(name, num)  FUNCTION_NAME_MAKE(name, num)

int main() {
    int i;
    double eltime, eltime_fft;
    printf("\n");

    for(i=0; i<SIZE/2; i++) xy[i]= 1.;
    for(   ; i<SIZE  ; i++) xy[i]=-1.;


// DFT
    timestart();
    for (i=0; i<DFT_REPEAT; i++) dft(LOG2FFTSIZE, xy_out_dft, xy); // dft_init(LOG2FFTSIZE) után 19,75 ms 1024 pt darabja
    eltime = timeend();
    printf("--> CPU wake up; (%2d piece of %d pt DFT;  %9.5f ms/piece)\n\n", DFT_REPEAT, 1<<LOG2FFTSIZE, eltime/DFT_REPEAT);

// DFT
    timestart();
    for (i=0; i<DFT_REPEAT; i++) dft(LOG2FFTSIZE, xy_out_dft, xy); // dft_init(LOG2FFTSIZE) után 19,75 ms 1024 pt darabja
    eltime = timeend();
    printf("%6d piece of %d pt DFT;  %9.5f ms/piece\n", DFT_REPEAT, 1<<LOG2FFTSIZE, eltime/DFT_REPEAT);

// DFT odd even
    timestart();
    for (i=0; i<DFT_REPEAT; i++) dft_odd_even(LOG2FFTSIZE, xy_out_dft_oddeven, xy); // dft_init(LOG2FFTSIZE) után 19,75 ms 1024 pt darabja
    eltime = timeend();
    printf("%6d piece of %d pt DFT;  %9.5f ms/piece (odd-even version)\n", DFT_REPEAT, 1<<LOG2FFTSIZE, eltime/DFT_REPEAT);

// FFT
    timestart();
    for (i=0; i<FFT_REPEAT; i++) fft(LOG2FFTSIZE, xy_out_fft, xy);
    eltime = timeend();
    printf("%6d piece of %d pt FFT;  %9.5f ms/piece\n", FFT_REPEAT, 1<<LOG2FFTSIZE, eltime/FFT_REPEAT);
    eltime_fft = eltime;

// libfftw3
    timestart();
    fftw(LOG2FFTSIZE, xy_out_fftw, xy, FFT_REPEAT); // repeated inside FFT_func
    eltime = timeend();
    printf("%6d piece of %d pt FFTW; %9.5f ms/piece (libfftw3) - libFFT3 is %.3fx faster than optimized FFT\n\n", FFT_REPEAT, 1<<LOG2FFTSIZE, eltime/FFT_REPEAT, eltime_fft/eltime);


    for(i=0; i<6; i++) {
	printres(i, xy_out_dft, "dft");
	printres(i, xy_out_dft_oddeven, "dft - odd even");
	printres(i, xy_out_fft, "fft");
	printres(i, xy_out_fftw, "fftw");

	printf("\n");
    }
    return 0;
}
