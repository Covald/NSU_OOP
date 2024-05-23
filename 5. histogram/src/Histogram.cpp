#include <algorithm>
#include "Histogram.hpp"

Histogram::Histogram(const std::vector<std::string> &v) {
    for (const auto &str: v) {
        if (!str.empty())
            _map[str]++;
    }
}

Histogram Histogram::operator+(const Histogram &another) const {
    Histogram new_ht(*this);
    for (const auto &elem: another._map) {
        new_ht._map[elem.first] += elem.second;
    }
    return new_ht;
}

Histogram Histogram::operator-(const Histogram &another) const {
    Histogram new_ht(*this);
    for (const auto &elem: another._map) {
        int tmp = new_ht._map[elem.first] - elem.second;
        if (tmp <= 0)
            new_ht._map.erase(elem.first);
        else
            new_ht._map[elem.first] = tmp;
    }
    return new_ht;
}

bool Histogram::operator==(const Histogram &another) const {
    return _map == another._map;
}

std::map<std::string, size_t> Histogram::data() const {
    return _map;
}


Histogram::iterator Histogram::begin() {
    return _map.begin();
}


Histogram::iterator Histogram::end() {
    return _map.end();
}

std::map<std::string, size_t>::const_iterator Histogram::cbegin() const {
    return _map.cbegin();
}

std::map<std::string, size_t>::const_iterator Histogram::cend() const {
    return _map.cend();
}


