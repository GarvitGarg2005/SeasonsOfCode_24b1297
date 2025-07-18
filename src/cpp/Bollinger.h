#pragma once
#include <vector>

// Returns:
// 0 → Price above upper band → SELL
// 1 → Price between bands → HOLD
// 2 → Price below lower band → BUY
int calculate_BollingerBands(const std::vector<double>& closes, int current_index, int period = 20, double num_std_dev = 2.0);
