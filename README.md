# Sorting logs using FFT

## Ubuntu 14.04.03 LTS x86_64

    apt-get install build-essential
    apt-get install libfftw3-dev
    make

## Usage

    $ ./fft_process -o 1 -n -c 4 < logfile

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

![R screenshot 1](https://raw.github.com/wllm-rbnt/fft_process/master/sc1.png)
![R screenshot 2](https://raw.github.com/wllm-rbnt/fft_process/master/sc2.png)

License
-------

This software is licensed under [GNU Affero General Public License version 3](http://www.gnu.org/licenses/agpl-3.0.html)

* Copyright (C) 2016 Conostix S.A.
* Copyright (C) 2016 William Robinet

