/*
    Description: Source file for kernel classes
*/

#include <iostream>
#include <numeric>  // Include for std::inner_product
#include <algorithm> // For std::transform
#include <functional>

#include "parzen_windows/base_pdf_generator.hpp"

// Assignment operator
template <typename T>
BasePDFGenerator<T>& BasePDFGenerator<T>::operator=(const BasePDFGenerator<T>& source) {
    // Check self assignemnt
    if (this == &source){
        return *this;
    };

    // Transfer over variables
    trainingDatapoints = source.trainingDatapoints;

    return *this;
};


/**
 * Standard Normal Distribution N(0,1)
 * 
 * @param x std::vector<T>
 */
template <typename T>
double BasePDFGenerator<T>::calculate_StandardNormal(const std::vector<T>& x) {
        double regularizing_coeff = 1/(std::pow(2*PI, x.size()/2));
        double exponent_value = (-0.5) * std::inner_product(x.begin(), x.end(), x.begin(), 0.0);
        return regularizing_coeff*std::pow(e, exponent_value);
    };


/**
 * Helper function to determine if all 
 * components of a std::vector are between -0.5 and 0.5
 * 
 * @param vec std::vector<T> 
 */
template <typename T>
bool BasePDFGenerator<T>::areAllComponentsValid(const std::vector<T>& vec) {
    // Check if all elements in the vector are within the range -0.5 to 0.5
    return std::all_of(vec.begin(), vec.end(), [](T x) {
        return x >= -0.5 && x <= 0.5; // Lambda function
    });
}

/**
 * Representing characteristics function
 * on a hypercube of length 1 centered at the origin. 
 * 
 * @param x std::vector<T> 
 * 
 */
template <typename T>
double BasePDFGenerator<T>::calculate_StandardSquare(const std::vector<T>& x) {

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
 * Given new, unseen data, determine its 
 * probability density value
 * 
 * @param new_datapoint
 * @param window_size
 */
template <typename T>
double BasePDFGenerator<T>::WindowPrediction(const std::vector<T>& new_datapoint, 
                        float window_size, 
                        Method method) {

    // Perform binding
    std::function<double(const std::vector<T>&)> func;

    // Create lambda functions of our implementations. 
    // The use of the **this** pointer is necessary to call the methods
    switch (method) {
        case Method::StandardNormal:
            func = [this](const std::vector<T>& dp) { return this->calculate_StandardNormal(dp); };
            break;
        case Method::StandardSquare:
            func = [this](const std::vector<T>& dp) { return this->calculate_StandardSquare(dp); };
            break;
    };


    double ans = 0.0;
    for (std::vector<T> trainingDatapoint : trainingDatapoints){
        std::vector<T> subtracted;
        std::transform(trainingDatapoint.begin(), trainingDatapoint.end(), 
                        new_datapoint.begin(), std::back_inserter(subtracted),std::minus<T>());

        std::transform(subtracted.begin(), subtracted.end(), subtracted.begin(),
                        [window_size](double value) { return value / window_size; });

        ans += func(subtracted);
    }

    ans = ans / (trainingDatapoints.size() * std::pow(window_size, new_datapoint.size()));

    return ans;
};

