#include <math.h>
#include "all_header.h"

// Internal variables
static int phasevec_exist = 0;
static double complex phasevec[33];

// Public function
void dft(int log2point, double complex *xy_out, const double complex *xy_in) {
    int i;
    int point = 1<<log2point;
    double complex phaseXY = 1.;
    double complex phasediffXY;

    if (!phasevec_exist) {
	for (i=0; i<=32; i++) {
	    int point = 1<<i;
	    phasevec[i] = cos(-2*M_PI/point) + I*sin(-2*M_PI/point);
	}
	phasevec_exist = 1;
    }
    phasediffXY = phasevec[log2point];

    for (i = 0; i<point; i++) {
	int j;
	double complex vfoXY = 1.;

	xy_out[i] = 0.;
	for(j=0; j<point; j++) {
	    xy_out[i] += xy_in[j]*vfoXY;
	    vfoXY *= phaseXY;
	}
	phaseXY *= phasediffXY;
    }
}
