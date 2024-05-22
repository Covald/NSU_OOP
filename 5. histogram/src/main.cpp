#include <iostream>
#include <sstream>
#include "Histogram.hpp"

int main(int argc, char *argv[]) {
    if (argc > 3) {
        std::cout << "Usage: ./HistogramPlusPlus [input_file] [output_file]" << std::endl;
        std::cout << "or ./HistogramPlusPlus" << std::endl;
        return 0;
    }

    if (argc == 3) {
        std::ifstream in_ss(argv[1]);
        std::ofstream out_ss(argv[2]);
        Histogram hist(in_ss);
        for (const auto &elem: hist) {
            out_ss << elem.first << ": " << std::string((unsigned long) elem.second, '#') << std::endl;
        }
        in_ss.close();
        out_ss.close();
    }
    std::string input;
    std::cout << "Enter a string: ";
    getline(std::cin, input);
    Histogram ht(input);
    for (const auto &elem: ht) {
        std::cout << elem.first << ": " << std::string((unsigned long) elem.second, '#') << std::endl;
    }

    return 0;
}