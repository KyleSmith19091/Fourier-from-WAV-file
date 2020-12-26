#include <cstdint>
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <fstream>
using namespace std;

struct WAV_HEADER{
    // Riff
    uint8_t chunkID[4];
    uint32_t chunkSize;
    uint8_t format[4];
    // FMT
    uint8_t subchunk1ID[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t samepleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    // Data
    uint8_t subchunk2ID[4];
    uint32_t subchunk2Size;
};

vector<complex<double>> convertWavDataToComplexVector(vector<int16_t> d){
    vector<complex<double>> output;
    for(int16_t i : d){
        output.push_back(complex<double>(i,0));
    }
    return output;
}

vector<complex<double>> getDataFromWav(const std::string &file_path){
    ifstream wav(file_path);
    struct WAV_HEADER whr;

    if(!wav.is_open()){
        throw "File Could Not be Opened!";
    }
    
    // Riff
    wav.read((char*)&whr.chunkID, sizeof(whr.chunkID)); 
    wav.read((char*)&whr.chunkSize, sizeof(whr.chunkSize));
    wav.read((char*)&whr.format, sizeof(whr.format));

    // fmt
    wav.read((char*)&whr.subchunk1ID, sizeof(whr.subchunk1ID));
    wav.read((char*)&whr.subchunk1Size, sizeof(whr.subchunk1Size));
    wav.read((char*)&whr.audioFormat,sizeof(whr.audioFormat));
    wav.read((char*)&whr.numChannels,sizeof(whr.numChannels));
    wav.read((char*)&whr.samepleRate,sizeof(whr.samepleRate));
    wav.read((char*)&whr.byteRate,sizeof(whr.byteRate));
    wav.read((char*)&whr.blockAlign,sizeof(whr.blockAlign));
    wav.read((char*)&whr.bitsPerSample,sizeof(whr.bitsPerSample));

    // Data
    wav.read((char*)&whr.subchunk2ID,sizeof(whr.subchunk2ID));
    wav.read((char*)&whr.subchunk2Size,sizeof(whr.subchunk2Size));

    vector<int16_t> data(whr.subchunk2Size);
    
    for(int i = 0; i < whr.subchunk2Size; i++){
        wav.read((char*)&data[i],sizeof(data[i]));
    }

    // Read audio data
    wav.close();
    
    return convertWavDataToComplexVector(data);
}

void dft(vector<complex<double>> signal,vector<complex<double>>& output){
    for(int k = 0; k < signal.size(); k++){
        complex<double> ans(0,0);
        for(int t = 0; t < signal.size(); t++){
            double angle = (-2 * M_PI * t * k) / signal.size(); 	
            ans += signal[t] * exp(complex<double>(0,angle));
        }
        output.push_back(ans);
    }
}

constexpr int findNextPowerOfTwo(int N){
    N--;
    N |= N >> 1;
    N |= N >> 2;
    N |= N >> 4;
    N |= N >> 8;
    N |= N >> 16;
    N++;
    return N;
}

constexpr bool isPowerOfTwo(int N){
    return (N & (N-1)) == 0;
}

// Ensure that signal length is a power of two
void transformSignal(vector<complex<double>>& signal){
    int diff = isPowerOfTwo(signal.size()) ? 0 : findNextPowerOfTwo(signal.size()) - signal.size();
    if(diff == 0) {
        return;
    }else{
        for(int i = 0; i < diff; i++){
            signal.push_back(0);	
        }
    }
}

void fft(vector<complex<double>>& signal){
   transformSignal(signal);
   int N = signal.size();

   if(N == 1) return; // Base case
    
   vector<complex<double>> even(N/2), odd(N/2); 
   for(int i = 0; 2 * i < N; i++){
       even[i] = signal[2*i];
       odd[i] = signal[2*i+1];
   }

   fft(even);
   fft(odd);

   double angle = 2 * M_PI / N;
   complex<double> w_n(cos(angle),sin(angle));
   complex<double> w(1);
   for(int i = 0; 2 * i < N; i++){
        signal[i] = even[i] + w * odd[i];
        signal[i + N/2] = even[i] - w * odd[i];
        w *= w_n;
   } 
}

void plotOutputData(){
    system("python3 ./plotter.py");
}

void writeDataToCSVFile(const vector<complex<double>>& out, const string fileName = "coords.csv"){
    ofstream outFile(fileName);

    outFile << "x,y" << "\n";

    for(complex<double> i : out){
        outFile << i.real() << "," << i.imag() << "\n";
    }

    outFile.close();

    plotOutputData();
}

int main(int argc,const char** argv){
	cin.tie(0);
    vector<complex<double>> output = getDataFromWav("humb.wav");       
    fft(output);

    writeDataToCSVFile(output);

	return 0;
}
