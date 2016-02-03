# Classifying logs using FFT

## Idea

In order to classify logs, details can often simply be omitted.
For instance, a trained eye will see the following log line, coming from a
running GNU/Linux kernel, as a potential problem.

    ata0.00: end_request: I/O error, dev sda, sector 25373542

The brain of the system administrator recognises the shape of the log line
without (and before) seeing the details.

    ____.__: end_request: I/O error, dev ___, sector ________

Basically, the Fourier Transform of a function is a decomposition of this
function into the different frequencies that make it up (Source
https://en.wikipedia.org/wiki/Fourier_transform).
This decomposition is a sum of sinuses of different frequencies and amplitudes,
some of them (the lower frequencies) being more significant than others at
shaping the main characteristics of the original function.

Fast Fourier Transform (FFT) is an algorithm that applies a Fourier Transform
to discrete series.

A log line can be seen as a discrete series, a random function y = f(x) with x
being the offset of a char in that log line and y the value of this char
expressed as an integer.

The idea is to apply FFT to log lines and keep their most significant
components in order to identify and classify them.

Incoming log lines could then be matched against interesting pre-defined
regions of a n-dimensional space, n being the number of significant components
extracted from the FFT (i.e. a prefix of the resulting FFT, representing the
lower frequency components).

## Status

This is just an early idea, not even a proof of concept. The code lacks proper
error checking here and there and is probably not very efficient. Usefulness
of this has yet to be demonstrated.

## Compilation

Tested under Ubuntu 14.04.03 LTS x86_64:

    apt-get install build-essential
    apt-get install libfftw3-dev
    make

## Usage

    $ ./fft_process -h
    Usage: ./fft_process [-h] [-n] [-i] [-l max_input_length] [-o output_offset] [-c output_count]
        -h      Show this help
        -n      Prefix output with line number
        -l      Maximum input length for each line in chars (defaults to 120)
        -o      Output offset in chars (defaults to 0)
        -c      Output count (defaults to 3)
        -i      Output imaginary part instead of the real part for each output value (defaults to real)

    $ ./fft_process -o 1 -n -c 4 < logfile
    0 1933 641 -278 -307 
    1 1984 71 -544 67 
    2 1877 494 -392 -287 
    ...

## Screenshots

Graph representation of some data generated from typical log files on a GNU/Linux system.

    $ ./fft_process -o 1 -c 6 < /var/log/messages > r_input.data
    $ R
    ...
    > library(rgl)
    > data <- read.table('r_input.data', col.names=c("V1", "V2", "V3", "V4", "V5", "V6"))
    > plot3d(data$V1, data$V2, data$V3,
        col=rgb(abs(data$V4/max(abs(data$V4))),
                abs(data$V5/max(abs(data$V5))),
                abs(data$V6/max(abs(data$V6))), 0)) 

Clusters of points in a 3-dimensional space (+ color as a 4th dimension)
representing the most significant parts of the decomposition of some random
system logs:
![R screenshot 1](https://raw.github.com/wllm-rbnt/fft_process/master/sc1.png)

Let's zoom in:
![R screenshot 2](https://raw.github.com/wllm-rbnt/fft_process/master/sc2.png)

## Further work

...
 
## License

This software is licensed under [GNU Affero General Public License version 3](http://www.gnu.org/licenses/agpl-3.0.html)

* Copyright (C) 2016 Conostix S.A.
* Copyright (C) 2016 William Robinet

