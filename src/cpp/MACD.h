#pragma once
#include <vector>

// Returns:
// 0 → Bearish crossover (signal > macd) → SELL
// 1 → Neutral
// 2 → Bullish crossover (macd > signal) → BUY
int calculate_MACD(const std::vector<double>& closes, int current_index,
                   int short_period = 12, int long_period = 26, int signal_period = 9);
