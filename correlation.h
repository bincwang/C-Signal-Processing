#ifndef H_correlation
#define H_correlation
#include <cmath>
#include <vector>
template <typename T>
auto xcorr(T & chirp, T & signal){
	double x_sum = 0;
	double y_sum = 0;
	for (int i = 0; i < chirp.size(); i++){
		//chirp and signal_segment have the same length.
		x_sum += chirp[i];
		y_sum += signal[i];
	}
	auto avg_x = x_sum/(chirp.size());
	auto avg_y = y_sum/(signal.size());
	
	double formula_top;
	double formula_bottom_left;
	double formula_bottom_right;
	for (int i = 0; i < chirp.size(); i++){
		formula_top += ((chirp[i] - avg_x) * (signal[i] - avg_y));
		formula_bottom_left += std::sqrt(std::pow(chirp[i] - avg_x));
		formula_bottom_right += std::sqrt(std::pow(signal[i] - avg_y));
	}
	auto formula_bottom = formula_bottom_left * formula_bottom_right;
	return formula_top/formula_bottom;
};










#endif
