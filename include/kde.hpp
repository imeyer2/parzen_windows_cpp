#pragma once
#include <vector>
#include <array>
#include <cmath>
#include <cassert>

// ---------- lightweight grids ----------

using Grid1D = std::vector<double>;               // size = N
struct Grid2D {                                   // size = rows × cols
    int rows = 0, cols = 0;
    std::vector<double> data;                     // row‑major
    Grid2D() = default;
    Grid2D(int r, int c) : rows(r), cols(c), data(r * c, 0.0) {}
    double&       operator()(int r,int c)       { return data[r*cols + c]; }
    const double& operator()(int r,int c) const { return data[r*cols + c]; }
};

// ---------- helpers ----------

inline double gauss(double x, double h)
{
    const double u = x / h;
    return std::exp(-0.5 * u * u) / (std::sqrt(2 * M_PI) * h);
}

// ---------- KDE APIs ----------

Grid1D kde_1d(const std::vector<double>& x,
              double h,
              int gridsize = 512);

Grid2D kde_2d(const std::vector<double>& x,
              const std::vector<double>& y,
              const std::array<double,2>& h,
              int gridsize = 128);
