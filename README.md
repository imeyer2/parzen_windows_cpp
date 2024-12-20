# Parzen Windows in C++

### Generate probability density functions in real-time!

The [Parzen Window Method](https://projecteuclid.org/journals/annals-of-mathematical-statistics/volume-33/issue-3/On-Estimation-of-a-Probability-Density-Function-and-Mode/10.1214/aoms/1177704472.full) is a tried and true method for estimating the true probability density function for a random variable given its realized outcomes. 

In other words, given observations of a random variable, we can reconstruct the probability density function by sums of the following form 

$\hat{p}(x) = \frac{1}{N} \cdot \frac{1}{h^l} \sum_{i=1} ^N \phi(\frac{x_i - x}{h})$

where $\phi$ is a nonnegative function with $\int_X \phi \, dx = 1$ where $X$ is the entire space (typically of the form $\mathbb{R}^l$)
