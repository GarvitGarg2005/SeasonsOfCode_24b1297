#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cmath>
#include <vector>

using namespace std;
namespace py = pybind11;

// ===== EMA Calculation =====
double calculate_EMA(const vector<double> &closes, int current_index, int period = 10) {
    if (current_index == 0) return closes[0];
    double alpha = 2.0 / (period + 1);
    return alpha * closes[current_index - 1] + calculate_EMA(closes, current_index - 1, period) * (1 - alpha);
}

// ===== RSI Strategy =====
int calculate_RSI(const vector<double> &closes, int current_index, int period = 14) {
    if (current_index < period)
        throw runtime_error("Not enough data for RSI");

    vector<double> gains, losses;
    for (int i = current_index - period + 1; i < current_index; ++i) {
        double diff = closes[i] - closes[i - 1];
        if (diff > 0)
            gains.push_back(diff);
        else
            losses.push_back(-diff);
    }

    double ema_gains = calculate_EMA(gains, gains.size());
    double ema_losses = calculate_EMA(losses, losses.size());
    if (ema_losses == 0) return 100;

    double rs = ema_gains / ema_losses;
    double rsi = 100.0 / (1 + rs);

    if (rsi > 70) return 0;
    else if (rsi < 30) return 2;
    else return 1;
}

// ===== Bollinger Band Strategy =====
double calculate_SMA(const vector<double> &closes, int current_index, int period = 20) {
    if (current_index < period)
        throw runtime_error("Not enough data for SMA");

    double sum = 0;
    for (int i = current_index - period + 1; i <= current_index; ++i)
        sum += closes[i];
    return sum / period;
}

double calculate_SD(const vector<double> &closes, int current_index, int period = 20) {
    double sma = calculate_SMA(closes, current_index, period);
    double sum = 0;
    for (int i = current_index - period + 1; i <= current_index; ++i)
        sum += pow(closes[i] - sma, 2);
    return sqrt(sum / period);
}

int run_BB_strategy(const vector<double> &closes, int current_index, int period = 20) {
    double middle = calculate_SMA(closes, current_index, period);
    double sd = calculate_SD(closes, current_index, period);
    double upper = middle + 2 * sd;
    double lower = middle - 2 * sd;

    if (closes[current_index] < lower) return 2;
    else if (closes[current_index] > upper) return 0;
    else return 1;
}

// ===== MACD Strategy =====
vector<double> calculate_MACD_line(const vector<double> &closes, int start, int end) {
    vector<double> macd_line;
    for (int i = start; i <= end; ++i)
        macd_line.push_back(calculate_EMA(closes, i, 12) - calculate_EMA(closes, i, 26));
    return macd_line;
}

int run_MACD_strategy(const vector<double> &closes, int current_index, int period = 10) {
    if (current_index < 26 + period)
        throw runtime_error("Not enough data for MACD");

    vector<double> macd_line = calculate_MACD_line(closes, current_index - period + 1, current_index);
    vector<double> signal_line;

    for (int i = 0; i < macd_line.size(); ++i)
        signal_line.push_back(calculate_EMA(macd_line, i, 9));

    if (macd_line.size() < 2 || signal_line.size() < 2)
        return 1;

    int i = macd_line.size() - 2;
    if (macd_line[i] < signal_line[i] && macd_line[i + 1] > signal_line[i + 1]) return 2;
    if (macd_line[i] > signal_line[i] && macd_line[i + 1] < signal_line[i + 1]) return 0;
    return 1;
}

// ===== PYBIND11 Binding =====
PYBIND11_MODULE(strategies, m) {
    m.def("calculate_RSI", &calculate_RSI);
    m.def("run_BB_strategy", &run_BB_strategy);
    m.def("run_MACD_strategy", &run_MACD_strategy);
}
