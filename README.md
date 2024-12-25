# Parzen Windows in C++

### Generate probability density functions in real-time!

The [Parzen Window Method](https://projecteuclid.org/journals/annals-of-mathematical-statistics/volume-33/issue-3/On-Estimation-of-a-Probability-Density-Function-and-Mode/10.1214/aoms/1177704472.full) is a tried and true method for estimating the true probability density function for a random variable given its realized outcomes. 

In other words, given observations of a random variable, we can reconstruct the probability density function by sums of the following form (where $N$ is the number of observed datapoints and $l$ is the dimensionality of the problem)

$\hat{p}(x) = \frac{1}{N} \cdot \frac{1}{h^l} \sum_{i=1} ^N \phi(\frac{x_i - x}{h})$

where $\phi$ is a nonnegative function with $\int_X \phi \, dx = 1$ where $X$ is the entire space (typically of the form $\mathbb{R}^l$).

Hyperparameters
- $h$ : The window size. Smaller values of $h$ (near 0, around 0.1, 0.2) will yield spikier, more jagged estimates for the underlying probability density function, larger values (0.8,0.9,1) will smooth this out, but may lose some more granular details.

- $phi$ : The actual kernel function. The method requires that \phi$ is a nonnegative function with $\int_X \phi \, dx = 1$. The typical choices are the `calculate_StandardSquare` or `calculate_StandardNormal` methods within the `StaticKernelFunctions` class.

Future ideas:
- Incorporation of real-time visualization
- More kernel functions