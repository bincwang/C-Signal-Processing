#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "correlation.h"
//Use Matlab signal processing I wrote ealier. To put the 0.01s chirp into a file called Chirp.wav
//To put the 25 seconds audio + chirp into a file called Mix.wav
//Then use this C++ program to do correlation, so we can detect the chirp
int main(){
	int fs = 44100;
	double max_corr = 0;
	double frame_duration = 0.01;
	double frame_len = frame_duration * fs;
	std::ifstream Mix;
	Mix.open("Mix.wav");

	std::ifstream Chirp;
	Chirp.open("Chirp.wav");
	//check for error
	if (Mix.fail()){
		std::cerr << "Brother, there is an Error Opening Mix File" <<std::endl;
		exit(1);
	}

	if (Chirp.fail()){
		std::cerr << "Brother, There is an error Opening Chirp File" <<std::endl;
		exit(1);
	}

	int time_ = 25; 
	//Important, here, my Mix.wav only has 25 seconds. However, I don't know how to use formula to describe the
	//length of wav file. But I'll change soon
	int N = time_ * fs;
	int num_frames = floor(N/frame_len);
	double max_frame = 0.0;	
	std::vector<float> temp1;
	for(int i = 0; i < num_frames; i++){
		auto begin = i * frame_len + 1;
		auto end = frame_len*(i+1);
		for(; begin != end; begin++){
			temp1.push_back(Mix[begin]);			
		}
		auto frame = xcorr(temp1, Chirp);
		if (std::max(frame) >= max_frame){
			max_frame = std::max(frame);
		}
		temp1.clear();
	}
	std::cout<< "max coefficient after cross-correlation is" << max_frame << std::endl;
	int count = 0;
	int t = 0;
	std::vector<double> temp;//need to add destructor
	for(int i = 0; i < num_frames; i++){
		auto begin = i * frame_len + 1;
		auto end = frame_len*(i+1);
		for(; begin != end; begin++){
			temp.push_back(Mix[begin]);			
		}
		count+=1;
		auto frame = xcorr(temp, Chirp);
		temp.clear();

		if (max_frame == frame){
			max_frame = std::max(frame);
			t = count;
		}
	}
	return t;
}
