#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "StreamMerger.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <output_filename> <input_filename1> <input_filename2> ..." << std::endl;
        return 1;
    }

    std::ofstream out_file(argv[1]);

    std::vector<std::unique_ptr<std::istream>> streams;
    streams.reserve(argc);
    for (size_t i = 2; i < argc; ++i) {
        if (std::filesystem::exists(argv[i])) {
            streams.push_back(std::move(std::make_unique<std::ifstream>(argv[i])));
        } else {
            std::cerr << "Can't open file - " << argv[i] << std::endl;
        }
    }

    StreamMerger::merge(streams, out_file);

    return 0;
}
