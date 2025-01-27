/*
    Description: Source file for kernel classes
*/

#include <iostream>
#include <numeric>  // Include for std::inner_product
#include <algorithm> // For std::transform
#include <functional>

#include "parzen_windows/base_pdf_generator.hpp"
#include "parzen_windows/base_kernel_functions.hpp"


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
 * Given new, unseen data, determine its 
 * probability density value
 * 
 * @param new_datapoint
 * @param window_size
 */
template <typename T>
double BasePDFGenerator<T>::WindowPrediction(const std::vector<T>& new_datapoint, 
                        float window_size, 
                        std::function<double(const std::vector<T>&)> func) {

    double ans = 0.0;
    for (const std::vector<T>& trainingDatapoint : trainingDatapoints) {
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

// // In base_pdf_generator.cpp
// template class BasePDFGenerator<double>;
// // Explicitly instantiate the method if used outside the class definition scope
template double BasePDFGenerator<double>::WindowPrediction(const std::vector<double>&, float, std::function<double(const std::vector<double>&)>);
