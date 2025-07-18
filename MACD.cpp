#incude <iostream>
#include <cmath>
#include <vector>
using namespace std;
double calculate_EMA(const vector<double> &closes, int current_index, int period = 10) {
    if(current_index==0) return closes[0];
    float alpha=(2.0/(period+1));
    double ema= alpha*closes[current_index-1] + (calculate_EMA(closes, current_index-1,period))*(1-alpha);
    return ema;
}
vector<double> calculate_MACD(const vector<double> &closes, int current_index, int period = 10) {
    vector<double> macd_line;
    for(int i = current_index - period + 1; i < current_index; ++i) {
        macd_line.push_back(calculate_EMA(closes,i,12)-calculate_EMA(closes,i,26));
    }
    return macd_line;
}
int run_MACD_strategy(const vector<double> &closes, int current_index, int period = 10){
    vector<double> macd_9_line,macd_line;
    for(int i = current_index - period + 1; i < current_index; ++i) {
        push_back(caluclate_EMA(closes,current_index,9));
    }
    macd_line=calculate_MACD(closes,current_index);
    for(int i = current_index - period + 1; i < current_index; ++i) {
        if(macd_line[i]==macd_9_line[i]) {
            if(macd_line[i+1]>macd_9_line[i+1]) return 2;
            else return 0;
        }
    }
}