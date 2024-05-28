#include "Parser.h"

Parser::Parser(std::istream &input_stream) : input(input_stream) {}

std::vector<std::string> Parser::parse() {
    std::vector<std::string> words;
    std::string word;
    while (input >> word) {
        words.push_back(word);
    }
    return words;
}
