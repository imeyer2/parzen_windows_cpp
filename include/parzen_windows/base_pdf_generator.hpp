/*
    Description: Source file for kernel classes
*/

#include <iostream>
#include <numeric>  // Include for std::inner_product
#include <algorithm> // For std::transform
#include <functional>


#ifndef BPG_H
#define BPG_H

#define PI 3.14159265358979323846
#define e 2.71828182845904523536


/**
 * Base class for all probability
 * density function generators
 * 
 * @param trainingDatapoints std::vector
 * 
 */
template <typename T> class BasePDFGenerator{
public:

    enum class Method {
        StandardNormal,
        StandardSquare
    };


    // Required datapoints to "train" the generator
    std::vector<std::vector<T>> trainingDatapoints;


    // Constructors & Destructor
    /**
     * Constructor
     * 
     * @param td std::vector<std::vector<T>>
     */
    BasePDFGenerator(std::vector<std::vector<T>>  td) : trainingDatapoints(td) {};
    BasePDFGenerator(const BasePDFGenerator<T>& source) : trainingDatapoints(source.trainingDatapoints) {};
    ~BasePDFGenerator() {};
    
    

    // Assignment operator
    BasePDFGenerator<T>& operator=(const BasePDFGenerator<T>& source);

    /**
     * Standard Normal Distribution N(0,1)
     * 
     * @param x std::vector<T>
     */
    double calculate_StandardNormal(const std::vector<T>& x);


    /**
     * Helper function to determine if all 
     * components of a std::vector are between -0.5 and 0.5
     * 
     * @param vec std::vector<T> 
     */
    bool areAllComponentsValid(const std::vector<T>& vec);

    /**
     * Representing characteristics function
     * on a hypercube of length 1 centered at the origin. 
     * 
     * @param x std::vector<T> 
     * 
     */
    double calculate_StandardSquare(const std::vector<T>& x);


    /**
     * Given new, unseen data, determine its 
     * probability density value
     * 
     * @param new_datapoint
     * @param window_size
     */
    double WindowPrediction(const std::vector<T>& new_datapoint, 
                            float window_size, 
                            Method method);


};

#endif