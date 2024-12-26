/**
 * Description: Kernel Function Classes and Methods
 */




#ifndef KERN_FUNCS_H
#define KERN_FUNCS_H

#include <iostream>
#include <numeric>  // Include for std::inner_product
#include <algorithm> // For std::transform
#include <functional>
#include <vector>

#define PI 3.14159265358979323846
#define e 2.71828182845904523536

template <typename T> class StaticKernelFunctions {
public:

    /**
     * Constructors and Destructors
     */
    StaticKernelFunctions() {};
    ~StaticKernelFunctions() {};


    /**
     * Standard Normal Distribution N(0,1)
     * 
     * @param x std::vector<T>
     */
    static double calculate_StandardNormal(const std::vector<T>& x);


    /**
     * Helper function to determine if all 
     * components of a std::vector are between -0.5 and 0.5
     * 
     * @param vec std::vector<T> 
     */
    static bool areAllComponentsValid(const std::vector<T>& vec);


    double euclidean_distance(const std::vector<double>& point1, const std::vector<double>& point2);
    
    
    /**
     * Representing characteristics function
     * on a hypercube of length 1 centered at the origin. 
     * 
     * @param x std::vector<T> 
     * 
     */
    static double calculate_StandardSquare(const std::vector<T>& x);


    static double calculate_StandardHyperSphere(const std::vector<T>& x);

};

#endif