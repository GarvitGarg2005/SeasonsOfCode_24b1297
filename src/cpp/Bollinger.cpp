#incude <iostream>
#include <cmath>
#include <vector>
using namespace std;
double calculate_SMA(const vector<double> &closes, int current_index, int period = 20) {
    if (current_index < period){
        throw "Not enough data";
    }
    double sum=0;
    for (int i = current_index - period + 1; i < current_index; ++i){
        sum+=closes[i];
    }
    return sum/period;
}
double calculate_SD(const vector<double> &closes, int current_index, int period = 20) {
    double x_i=calculate_SMA(closes,  current_index, period);
    double Sum=0;
    for (int i = current_index - period + 1; i < current_index; ++i){
        Sum+= pow(x_i-closes[i],2);
    }
    return pow((Sum/period),0.5);
}
int run_BB_strategy(const vector<double> &closes, int current_index, int period = 20) {
    double middle_band=calculate_SMA(closes,current_index, period);
    double upper_band= middle_band + 2*calculate_SD(closes,current_index, period);
    double lower_band= middle_band - 2*calculate_SD(closes,current_index, period);
    double close = closes[current_index];
    if(close<lower_band) {
        return 2;
    }
    else if(close>upper_band) {
        return 0;
    }
    else return 1;
}
