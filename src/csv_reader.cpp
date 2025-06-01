#include "csv_reader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

static std::vector<std::string> split_line(const std::string& line, char sep=',')
{
    std::vector<std::string> out;
    std::string cell;
    std::stringstream ss(line);
    while (std::getline(ss, cell, sep)) out.push_back(cell);
    // handle trailing comma
    if (!line.empty() && line.back() == sep) out.emplace_back("");
    return out;
}

CsvData load_numeric_csv(const std::string& path, bool skip_first_col)
{
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Cannot open " + path);

    std::string line;
    CsvData data;

    /* ---- read header row ---- */
    if (!std::getline(in, line)) return data;          // empty file
    data.headers = split_line(line);
    std::size_t ncols_total = data.headers.size();
    std::size_t start       = skip_first_col ? 1 : 0;

    data.numeric_cols.resize(ncols_total - start);

    /* ---- read data rows ---- */
    while (std::getline(in, line)) {
        auto cells = split_line(line);
        // pad short rows
        cells.resize(ncols_total);

        for (std::size_t c = start; c < ncols_total; ++c) {
            try {
                double v = std::stod(cells[c]);
                data.numeric_cols[c - start].push_back(v);
            } catch (...) {
                /* non‑numeric cell => skip */
            }
        }
    }
    return data;
}
