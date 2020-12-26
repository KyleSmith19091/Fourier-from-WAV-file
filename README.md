# Fourier Transform from WAV file
The goal of this project was to learn a little about the fourier transform operation and how to implement it programatically.
The project has two implementations regarding the Fourier Transform one that is derived from the following formula:

$X(k) = \displaystyle\sum_{t=0}^{n-1} x(t) e^{-2 π i t k / n}$

and the other is an implmentation of the Fast Fourier Transform algorithm.
The effiecency of the two algorithms is described as follows DFT => $O(n^2)$ and FFT $O(nlogn)$ where n is the length 
of the input.

The input for this project I decided to be a .wav file. Provided a wav file the program parses the file extracting the 
necessary data and then converts it to a vector of complex double numbers. The FFT algorithm is designed in such a way that
it can only run on data with a length that is a power of 2, so additional logic was added to pad the length of the data vector
in the case that the data is not a power of 2.

Finally once the output vector is computed from the input vector I wrote a simple python program to graph the output on the x-y plane
and one for magnitude-frequency. I realize that plotting the output on the Argand plane would be beter but it was outside the scope of
the project. The graphs are presented once done and saved as png files in the project directory.

