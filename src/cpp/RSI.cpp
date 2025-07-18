#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
double calculate_EMA(const vector<double> &closes, int current_index, int period = 10) {
    if(current_index==0) return closes[0];
    float alpha=(2.0/(period+1));
    double ema= alpha*closes[current_index-1] + (calculate_EMA(closes, current_index-1,period))*(1-alpha);
    return ema;
}
double calculate_RSI(const vector<double> &closes, int current_index, int period = 14) {
    if (current_index < period){ 
        throw "Not enough data";
    }
    vector<double> gains,losses;
    int k=0;
    for (int i = current_index - period + 1; i < current_index; ++i){
        if(closes[i]-closes[i-1]>0){
            gains.push_back(closes[i]-closes[i-1]);
        }
        else {
            losses.push_back(-closes[i]+closes[i-1]);
        }
        k++;
    }
    double ema_gains = calculate_EMA(gains, gains.size());
    double ema_losses = calculate_EMA(losses, losses.size());
    if (ema_losses == 0) return 100; 
    double RS = ema_gains / ema_losses;
    double RSI= 100.0/(1+RS);
    if(RSI>70) return 0;
    else if (RSI<30) return 2;
    else return 1;
}