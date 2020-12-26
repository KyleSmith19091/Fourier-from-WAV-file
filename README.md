# Fourier Transform from WAV file
The goal of this project was to learn a little about the fourier transform operation and how to implement it programatically.
The project has two implementations regarding the Fourier Transform one that is derived from the following formula:

![equation](https://latex.codecogs.com/gif.latex?X%28k%29%20%3D%20%5Cdisplaystyle%5Csum_%7Bt%3D0%7D%5E%7Bn-1%7D%20x%28t%29%20e%5E%7B-2%20%5CPi%20i%20t%20k%20/%20n%7D)

and the other is an implmentation of the Fast Fourier Transform algorithm.
The effiecency of the two algorithms is described as follows DFT => ![equation](https://latex.codecogs.com/gif.latex?O%28n%5E2%29) and FFT ![equation](https://latex.codecogs.com/gif.latex?O%28nlogn%29) where n is the length 
of the input.

The input for this project I decided to be a .wav file. Provided a wav file the program parses the file extracting the 
necessary data and then converts it to a vector of complex double numbers. The FFT algorithm is designed in such a way that
it can only run on data with a length that is a power of 2, so additional logic was added to pad the length of the data vector
in the case that the data is not a power of 2.

Finally once the output vector is computed from the input vector I wrote a simple python program to graph the output on the x-y plane
and one for magnitude-frequency. I realize that plotting the output on the Argand plane would be beter but it was outside the scope of
the project. The graphs are presented once done and saved as png files in the project directory.

