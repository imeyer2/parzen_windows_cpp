/**
 * Description: Example script for Parzen Window Functionality
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


#include <matplot>
#include "parzen_windows/base_pdf_generator.hpp"
#include "parzen_windows/base_kernel_functions.hpp"

/// @brief Loads data from .csv files 
/// @param filename 
/// @return std::vector<std::vector<double>>
std::vector<std::vector<double>> load_csv(const std::string& filename) {
    std::vector<std::vector<double>> data;
    std::ifstream file(filename);
    std::string line;
    bool firstLine = true;

    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false; // Skip the first line assuming it's the header
            continue;
        }
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<double> parsedRow;
        while (std::getline(lineStream, cell, ',')) {
            try {
                parsedRow.push_back(std::stod(cell));
            } catch (const std::invalid_argument& ia) {
                // Handle the case where the conversion failed
                std::cerr << "Invalid argument: " << ia.what() << '\n';
                parsedRow.push_back(0.0); // Insert a default value or handle it as needed
            }
        }
        data.push_back(parsedRow);
    }


    std::cout << "Printing records" << std::endl;
    // Print the data to verify it's loaded correctly
    for (const auto& row : data) {
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    return data;
}

int main(void) {
    std::string filename = "../src/data/funky_data.csv"; // Adjust the path as needed
    std::vector<std::vector<double>> data = load_csv(filename);

    BasePDFGenerator<double> pdf_gen(data);

    // Generate a grid of points in R^2 to then find the pdf of to plot in R^3
    // Define the grid size
    int num_points = 11; 

    // Create a 2D vector to store the grid points
    std::vector<std::vector<double>> grid(num_points, std::vector<double>(data[0].size()));

    // Generate coordinates for the grid
    double step_size = 2.0 / (num_points - 1); 
    for (int i = 0; i < num_points; ++i) {
        for (int j = 0; j < num_points; ++j) {
            grid[i][j] = -1.0 + i * step_size; // x-coordinate
            grid[j][i] = -1.0 + j * step_size; // y-coordinate
        }
    }

    // Print the grid points 
    for (const std::vector<double>& row : grid) {
        for (const double& point : row) {
            std::cout << point << " ";
        }
        std::cout << std::endl;
    }

    std::vector<double> result_pdf_values;
    StaticKernelFunctions<double> obj;
    std::function<double(const std::vector<double>&)> myFunc = [&obj](const std::vector<double>& v) {
        return obj.calculate_StandardNormal(v);
    };

    std::cout << pdf_gen.WindowPrediction(input_datapoint, 0.4, myFunc) << std::endl;

    return 0;
}
