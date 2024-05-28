#include "Exporter.h"

Exporter::Exporter(std::ostream &output_stream) : output(output_stream) {}

void Exporter::export_histogram(const Histogram &ht) {
    for (const auto &elem: ht.data()) {
        output << elem.first << ": " << std::string((unsigned long) elem.second, '#') << std::endl;
    }
}
