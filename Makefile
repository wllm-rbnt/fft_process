# Yaaaaa
.PHONY: clean debug all
all:
	gcc -o fft_process fft_process.c -lfftw3

debug:
	gcc -o fft_process_debug fft_process.c -lfftw3 -g -ggdb3

clean:
	rm fft_process

