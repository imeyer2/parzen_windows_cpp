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


template double StaticKernelFunctions<double>::calculate_StandardNormal(const std::vector<double>& x);
template double StaticKernelFunctions<double>::calculate_StandardSquare(const std::vector<double>& x);
