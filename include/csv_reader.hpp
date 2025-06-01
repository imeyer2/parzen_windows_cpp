#pragma once
#include <vector>
#include <string>

struct CsvData {
    std::vector<std::string>           headers;
    std::vector<std::vector<double>>   numeric_cols;   // col‑major
    std::size_t n_rows() const { return numeric_cols.empty() ? 0 : numeric_cols[0].size(); }
    std::vector<std::string> headers_numeric() const {
        std::vector<std::string> h;
        for (std::size_t i = 0; i < numeric_cols.size(); ++i) h.push_back(headers[i+1]); // skip index
        return h;
    }
};

CsvData load_numeric_csv(const std::string& path, bool skip_first_col);
