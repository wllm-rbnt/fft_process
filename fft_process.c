#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<fftw3.h>

#define MAX_LENGTH 120
#define OFFSET 0
#define COUNT 3

void usage() {
    printf("Usage: ./fft_process [-h] [-n] [-i] [-l max_input_length] [-o output_offset] [-c output_count] < log_file\n");
    printf("\t-h\tShow this help\n");
    printf("\t-n\tPrefix output with line number\n");
    printf("\t-l\tMaximum input length in chars for each line (defaults to 120)\n");
    printf("\t-o\tOutput offset in chars (defaults to 0)\n");
    printf("\t-c\tOutput count (defaults to 3)\n");
    printf("\t-i\tOutput imaginary part instead of the real part for each output value (defaults to real)\n");
}

int main(int argc, char* argv[]) {

    int max_length = MAX_LENGTH,
        offset = OFFSET,
        count = COUNT,
        show_line_number = 0,
        imaginary_output = 0,
        opt;

    while((opt = getopt(argc, argv, "l:o:c:hni")) > 0) {

        switch (opt) {
            case 'l':
                max_length = atoi(optarg);
                break;

            case 'o':
                offset = atoi(optarg);
                break;
         
            case 'c':
                count = atoi(optarg);
                break;

            case 'n':
                show_line_number = 1;
                break;

            case 'i':
                imaginary_output = 1;
                break;

            case 'h':
                usage();
                exit(0);
        }
    }     

    double *in;
    fftw_complex *out;
    fftw_plan p;

    ssize_t bytes_read;
    size_t nbytes = 0;
    char *line = NULL;

    int N = max_length + 1,
        Nc = (N / 2) + 1,
        line_num = 0,
        i,
        max;
    double current_value = 0;

    in = (double*) fftw_malloc(sizeof(double) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * Nc);
    p = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);

    while((bytes_read = getline (&line, &nbytes, stdin)) != -1) {

        max = bytes_read < N ? bytes_read : N;

        for(i = 0; i < max; i++) {
            in[i] = line[i];
        }

        for(; i < N; i++) {
            in[i] = 0;
        }

        fftw_execute(p);

        if(show_line_number) {
            printf("%d ", line_num);
        }
        for(i = offset; i < offset + count; i++) {
            if(imaginary_output) {
                current_value = out[i][1];
            } else {
                current_value = out[i][0];
            }
            if(isnan(current_value)) {
                current_value = 0;
            }
            printf( "%.f ", current_value);
        }

        printf("\n");

        line_num++;
    }
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);

    return 0;
}

