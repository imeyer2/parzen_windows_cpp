#pragma once
#include <vector>
#include <cmath>

/// Scott’s rule of thumb bandwidth per dimension.
/// cols = column‑major numeric data (each inner vector is one column)

// inline because we want to avoid the overhead of a function call. Speed matters
inline std::vector<double> scott_bandwidth(const std::vector<std::vector<double>>& cols)
{
    const double n = static_cast<double>(cols.front().size());
    const int     d = static_cast<int>(cols.size());
    const double  factor = std::pow(n, -1.0 / (d + 4));

    std::vector<double> h;
    h.reserve(d);
    for (auto& col : cols) {
        // compute sample std‑dev
        double mean = 0.0;
        for (double v : col) mean += v;
        mean /= n;
        double var = 0.0;
        for (double v : col) { double diff = v - mean; var += diff * diff; }
        var /= (n - 1.0);
        h.push_back(std::sqrt(var) * factor);
    }
    return h;
}
