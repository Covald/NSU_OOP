#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <fstream>

class Parser {
private:
    std::istream &input;
public:
    explicit Parser(std::istream &input_stream);

    std::vector<std::string> parse();
};

#endif //PARSER_H