#include <algorithm>
#include "Histogram.hpp"

using namespace std;

Histogram::Histogram(std::istream &is) {
    string word;
    while (is >> word) {
        _map[word]++;
    }
}

Histogram::Histogram(const string &str) {
    string word;
    istringstream ss(str);
    while (ss >> word) {
        _map[word]++;
    }
}

Histogram::Histogram(const vector<string> &v) {
    for (const auto &str: v) {
        _map[str]++;
    }
}

Histogram Histogram::operator+(const Histogram &another) const {
    Histogram new_ht(*this);
    for (const auto &elem: another._map) {
        new_ht._map[elem.first] += elem.second;
        if (new_ht._map[elem.first] == 0) {
            new_ht._map.erase(elem.first);
        }
    }
    return new_ht;
}

Histogram Histogram::operator-(const Histogram &another) const {
    Histogram new_ht(*this);
    for (const auto &elem: another._map) {
        new_ht._map[elem.first] -= elem.second;
        if (new_ht._map[elem.first] == 0) {
            new_ht._map.erase(elem.first);
        }
    }
    return new_ht;
}

bool Histogram::operator==(const Histogram &another) const {
    if (_map.size() != another._map.size()) return false;

    return std::equal(cbegin(), cend(), another.cbegin());
}

const std::map<std::string, int> &Histogram::data() const {
    return _map;
}


Histogram::iterator Histogram::begin() {
    return _map.begin();
}


Histogram::iterator Histogram::end() {
    return _map.end();
}

std::map<std::string, int>::const_iterator Histogram::cbegin() const {
    return _map.cbegin();
}

std::map<std::string, int>::const_iterator Histogram::cend() const {
    return _map.cend();
}


