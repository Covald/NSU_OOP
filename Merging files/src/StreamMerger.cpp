#include <iostream>
#include <sstream>
#include <string>
#include "StreamMerger.h"

namespace {
    bool is_line_empty(const std::string &line) {
        return line.find_first_not_of(" \t") == std::string::npos;
    }

    bool read_line(std::istream &input_stream, std::string &temp) {
        while (std::getline(input_stream, temp)) {
            if (!is_line_empty(temp)) {
                return true;
            }
        }
        return false;
    }
}

void StreamMerger::merge(std::vector<std::unique_ptr<std::istream>> &input_streams,
                         std::ostream &output_stream) {
    bool is_any_stream_has_data = true;
    while (is_any_stream_has_data) {
        is_any_stream_has_data = false;
        for (auto &stream: input_streams) {
            std::string temp;
            if (read_line(*stream, temp)) { // Todo
                is_any_stream_has_data = true;
                output_stream << temp << std::endl;
            }
        }
    }
}