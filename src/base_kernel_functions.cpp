/**
 * Description: Source file for the base_kernel_functions.hpp file
 */



#include "parzen_windows/base_kernel_functions.hpp"

/**
 * Helper function to determine if all 
 * components of a std::vector are between -0.5 and 0.5
 * 
 * @param vec std::vector<T> 
 */
template <typename T>
bool StaticKernelFunctions<T>::areAllComponentsValid(const std::vector<T>& vec) {
    // Check if all elements in the vector are within the range -0.5 to 0.5
    return std::all_of(vec.begin(), vec.end(), [](T x) {
        return x >= -0.5 && x <= 0.5; // Lambda function
    });
};


/**
 * Helper function to determine if all 
 * components of a std::vector are between -0.5 and 0.5
 * 
 * @param vec std::vector<T> 
 */
template <typename T>
bool StaticKernelFunctions<T>::testAllComponenets(const std::vector<T>& vec, double thresh) {
    // Check if all elements in the vector are within the range -0.5 to 0.5
    return std::all_of(vec.begin(), vec.end(), [](T x) {
        return x >= -1* thresh && x <= thresh; // Lambda function
    });
};

/**
 * Representing characteristics function
 * on a hypercube of length 1 centered at the origin. 
 * 
 * @param x std::vector<T> 
 * 
 */
template <typename T>
double StaticKernelFunctions<T>::calculate_StandardSquare(const std::vector<T>& x) {

    // If x is in the hypercube centered at origin, then return 1
    // else return 0
    if (areAllComponentsValid(x)) {
        return 1.0;
    }
    else {
        return 0.0;
    };
};




/**
 * Standard Normal Distribution N(0,1)
 * 
 * @param x std::vector<T>
 */
template <typename T>
double StaticKernelFunctions<T>::calculate_StandardNormal(const std::vector<T>& x) {
        double regularizing_coeff = 1/(std::pow(2*PI, x.size()/2));
        double exponent_value = (-0.5) * std::inner_product(x.begin(), x.end(), x.begin(), 0.0);
        return regularizing_coeff*std::pow(e, exponent_value);
    };





// Function to calculate Euclidean distance between two points
template <typename T>
double StaticKernelFunctions<T>::euclidean_distance(const std::vector<double>& point1, const std::vector<double>& point2) {
    if (point1.size() != point2.size()) {
        throw std::invalid_argument("Points must have the same number of dimensions.");
    }

    double distance_squared = 0.0;
    for (int i = 0; i < point1.size(); i++) {
        distance_squared += std::pow(point1[i] - point2[i], 2);
    }

    return std::sqrt(distance_squared);
}


template <typename T>
double StaticKernelFunctions<T>::calculate_StandardHyperSphere(const std::vector<T>& x) {


    // Find radius `r` such that volume of hypersphere is 1. r = (1/v_n)^(1/n)

    double volume_of_ndim_unit_ball;
    double radius = std::pow(1/volume_of_ndim_unit_ball, 1/x.size())

    if std::


};


template double StaticKernelFunctions<double>::calculate_StandardNormal(const std::vector<double>& x);
template double StaticKernelFunctions<double>::calculate_StandardSquare(const std::vector<double>& x);
