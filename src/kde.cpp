#include "kde.hpp"
#include <algorithm>
#include <thread>
#include <atomic>

/**
 * @brief Computes one-dimensional Kernel Density Estimation (KDE) using Gaussian kernel.
 * 
 * This function estimates the probability density function of a random variable based on
 * a finite data sample using a Gaussian kernel. The implementation uses multithreading
 * to parallelize the computation across available CPU cores.
 * 
 * @param x Input sample points (data observations).
 * @param h Bandwidth parameter that controls the smoothness of the density estimate.
 * @param N Number of grid points to evaluate the density on.
 * @return Grid1D A grid containing the estimated density values at equally spaced points
 *         between the minimum and maximum of the input data.
 * 
 * @note The computation is parallelized using std::thread to utilize available CPU cores.
 * @note The Gaussian kernel function (gauss) is assumed to be defined elsewhere.
 */
Grid1D kde_1d(const std::vector<double>& x, double h, int N)
{
    double xmin = *std::min_element(x.begin(), x.end());
    double xmax = *std::max_element(x.begin(), x.end());
    const double dx = (xmax - xmin) / (N - 1);

    Grid1D dens(N, 0.0);

    unsigned nthreads = std::thread::hardware_concurrency();
    std::vector<std::thread> workers;
    std::atomic<int> next_idx{0};

    for (unsigned t = 0; t < nthreads; ++t) {
        workers.emplace_back([&, t]{
            int idx;
            while ((idx = next_idx.fetch_add(1)) < N) {
                double xi = xmin + idx * dx;
                double s = 0.0;
                for (double v : x) s += gauss(xi - v, h);
                dens[idx] = s / x.size();
            }
        });
    }
    for (auto& th : workers) th.join();
    return dens;
}

Grid2D kde_2d(const std::vector<double>& x,
              const std::vector<double>& y,
              const std::array<double,2>& h,
              int N)
{
    assert(x.size() == y.size());
    double xmin = *std::min_element(x.begin(), x.end());
    double xmax = *std::max_element(x.begin(), x.end());
    double ymin = *std::min_element(y.begin(), y.end());
    double ymax = *std::max_element(y.begin(), y.end());
    const double dx = (xmax - xmin) / (N - 1);
    const double dy = (ymax - ymin) / (N - 1);

    Grid2D z(N, N);

    unsigned nthreads = std::thread::hardware_concurrency();
    std::vector<std::thread> workers;
    std::atomic<int> next_row{0};

    for (unsigned t = 0; t < nthreads; ++t) {
        workers.emplace_back([&, t]{
            int row;
            while ((row = next_row.fetch_add(1)) < N) {
                double yi = ymin + row * dy;
                for (int col = 0; col < N; ++col) {
                    double xi = xmin + col * dx;
                    double s = 0.0;
                    for (size_t k = 0; k < x.size(); ++k) {
                        s += gauss(xi - x[k], h[0]) * gauss(yi - y[k], h[1]);
                    }
                    z(row, col) = s / x.size();
                }
            }
        });
    }
    for (auto& th : workers) th.join();
    return z;
}
