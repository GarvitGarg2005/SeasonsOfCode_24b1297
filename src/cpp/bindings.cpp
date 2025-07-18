// bindings.cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "rsi.h"
#include "macd.h"
#include "bollinger_bands.h"

namespace py = pybind11;

PYBIND11_MODULE(strategy_bindings, m) {
    m.def("calculate_RSI", &calculate_RSI, "RSI strategy",
          py::arg("closes"), py::arg("current_index"), py::arg("period") = 14);
    
    m.def("calculate_MACD", &calculate_MACD, "MACD strategy",
          py::arg("closes"), py::arg("current_index"), py::arg("short_period") = 12, py::arg("long_period") = 26, py::arg("signal_period") = 9);

    m.def("calculate_BB", &calculate_BB, "Bollinger Bands strategy",
          py::arg("closes"), py::arg("current_index"), py::arg("period") = 20, py::arg("num_std_dev") = 2.0);
}
