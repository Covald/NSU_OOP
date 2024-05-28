#ifndef EXPORTER_H
#define EXPORTER_H


#include <iostream>
#include <fstream>
#include "Histogram.hpp"

class Exporter {
private:
    std::ostream &output;
public:
    explicit Exporter(std::ostream &output_stream);

    void export_histogram(const Histogram &ht);
};


#endif //EXPORTER_H
