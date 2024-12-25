/*
    Description: Source file for kernel classes
*/


#ifndef BPG_H
#define BPG_H

#include <iostream>
#include <numeric>  // Include for std::inner_product
#include <algorithm> // For std::transform
#include <functional>
#include <vector>
#include "parzen_windows/base_kernel_functions.hpp"


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
    /**
     * Constructor
     * 
     * @param td std::vector<std::vector<T>>
     */
    // BasePDFGenerator() : trainingDatapoints({{0}}) {}; // This consructor only exists to instantiate at the bottom of base_pdf_generator.cpp
    BasePDFGenerator(std::vector<std::vector<T>>  td) : trainingDatapoints(td) {
        std::cout << "Constructor called with " << trainingDatapoints.size() << " training points." << std::endl; // Verify population of the `trainingDatapoints` variable
    };
    
    BasePDFGenerator(const BasePDFGenerator<T>& source) : trainingDatapoints(source.trainingDatapoints) {};
    ~BasePDFGenerator() {};
    
    

    // Assignment operator
    BasePDFGenerator<T>& operator=(const BasePDFGenerator<T>& source);


    /**
     * Given new, unseen data, determine its 
     * probability density value
     * 
     * @param new_datapoint
     * @param window_size
     */
    double WindowPrediction(const std::vector<T>& new_datapoint, 
                            float window_size, 
                            std::function<double(const std::vector<T>&)> func);

};

#endif