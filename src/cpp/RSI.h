#pragma once
#include <vector>

// Returns:
// 0 → Overbought (RSI > 70)
// 1 → Neutral
// 2 → Oversold (RSI < 30)
int calculate_RSI(const std::vector<double>& closes, int current_index, int period = 14);
