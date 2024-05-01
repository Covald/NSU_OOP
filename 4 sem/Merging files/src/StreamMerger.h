#ifndef MERGING_FILES_STREAMMERGER_H
#define MERGING_FILES_STREAMMERGER_H

#include <fstream>
#include <vector>
#include <memory>

namespace StreamMerger {
    void merge(std::vector<std::unique_ptr<std::istream>> &input_streams, std::ostream &output_stream);
}

#endif
