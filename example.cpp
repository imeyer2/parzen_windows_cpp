/**
 * Description: Example script for Parzen Window Functionality
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "kernels.cpp"

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

        // Print the data to verify it's loaded correctly
    for (const auto& row : data) {
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    return data;
}

int main() {
    std::string filename = "SampleData.csv"; // Adjust the path as needed
    std::vector<std::vector<double>> data = load_csv(filename);

    BasePDFGenerator<double> pdf_gen(data);


    std::vector<double> input_datapoint = { 0.4332, 0.3904, 0.4479, 0.5892, 0.3689};


    std::cout << pdf_gen.WindowPrediction(input_datapoint, 0.4, BasePDFGenerator<double>::Method::StandardNormal) << std::endl;

    return 0;
}
