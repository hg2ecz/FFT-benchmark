CC=gcc

CFLAGS =-Wall -Ofast -funroll-loops
CFLAGS+=-mcpu=cortex-a5 -mfpu=neon-fp16

# LOG2FFTSIZE=10 --> 1024 pt FFT,
# DFTNUM and FFTNUM --> greater = precise elapsed time measurement
CFLAGS+=-DLOG2FFTSIZE=12
CFLAGS+=-DDFT_REPEAT=1
CFLAGS+=-DFFT_REPEAT=1000

LDFLAGS=-lm -lfftw3 -s
OBJS=dft.o dft_odd_even.o fft.o fftw.o benchmark-fft.o

TARGET=benchmark-fft

all: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET)
