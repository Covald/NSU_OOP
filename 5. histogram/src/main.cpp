#include <iostream>
#include <sstream>
#include "Histogram.hpp"

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

    std::vector<std::string> words;
    std::string word;
    while (input >> word) {
        words.push_back(word);
    }
    Histogram ht(words);
    for (const auto &elem: ht.data()) {
        output << elem.first << ": " << std::string((unsigned long)elem.second, '#') << std::endl;
    }
    return 0;
}