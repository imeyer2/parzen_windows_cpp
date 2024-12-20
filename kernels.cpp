/*
    Description: Source file for kernel classes
*/

#include <iostream>
#include <numeric>  // Include for std::inner_product
#include <algorithm> // For std::transform

#define PI = 3.14159265358979323846
#define e = 2.71828182845904523536



#ifndef KENREL_C
#define KERNEL_C

/**
 * Base class for all probability
 * density function generators
 * 
 * @param trainingDatapoints std::vector
 * 
 */
template <typename T> class BasePDFGenerator{
public:

    // Required datapoints to "train" the generator

    std::vector<std::vector<T>> trainingDatapoints;


    // Constructors & Destructor

    BasePDFGenerator(std::vector<std::vector<T>>  td) : trainingDatapoints(td) {};
    BasePDFGenerator(const BasePDFGenerator<T>& source) : trainingDatapoints(source.trainingDatapoints) {};
    ~BasePDFGenerator() {};
    
    

    // Assignment operator
    BasePDFGenerator<T>& BasePDFGenerator<T>::operator = (const BasePDFGenerator<T>& source) {
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
    double StandardNormal(std::vector<T> x) {

        double regularizing_coeff = 1/(std::pow(2*PI, x.size()/2));

        double exponent_value = (-0.5) * std::inner_product(x, x);

        return regularizing_coeff*std::pow(e, exponent_value)

    };



    /**
     * Given new, unseen data, determine its 
     * probability density value
     * 
     * @param new_datapoint
     * @param window_size
     */
    double GaussianWindowPrediction(std::vector<T> new_datapoint, float window_size) {

        double ans = 0.0;


        for (std::vector<T> trainingDatapoint : trainingDatapoints){
            
            std::vector<T> subtracted;

            std::transform(trainingDatapoint.begin(), trainingDatapoint.end(), 
            new_datapoint.begin(), std::back_inserter(subtracted),std::minus<T>());


            std::transform(subtracted.begin(), subtracted.end(), subtracted.begin(),
                   [window_size](double value) { return value / window_size; });


            ans = ans + StandardNormal(subtracted)
        }


        return ans;
    };




// GaussianWindowPrediction
// SquareWindowPrediction
// GeneralWindowPrediction


};

#endif