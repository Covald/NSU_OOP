#include <iostream>
#include <sstream>
#include "Histogram.hpp"
#include "Parser.h"
#include "Exporter.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./HistogramPlusPlus [input_file] [output_file]" << std::endl;
        std::cout << "or ./HistogramPlusPlus" << std::endl;
        return 0;
    }

    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);
    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Error opening files" << std::endl;
        return 1;
    }

    Parser parser(input);
    Histogram ht(parser.parse());
    Exporter exporter(output);
    exporter.export_histogram(ht);

    return 0;
}