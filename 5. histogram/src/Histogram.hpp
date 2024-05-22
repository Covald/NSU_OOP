#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>

class Histogram {
private:
    std::map<std::string, int> _map;
public:

    Histogram() = default;

    explicit Histogram(const std::string &str);

    explicit Histogram(std::istream &is);

    explicit Histogram(const std::vector<std::string> &v);

    Histogram(const Histogram &another) = default;

    ~Histogram() = default;

    Histogram &operator=(const Histogram &another) = default;

    Histogram operator+(const Histogram &another) const;

    Histogram operator-(const Histogram &another) const;

    bool operator==(const Histogram &another) const;

    const std::map<std::string, int> &data() const;

    using iterator = std::map<std::string, int>::iterator;
    using const_iterator = std::map<std::string, int>::const_iterator;

    iterator begin();

    iterator end();

    const_iterator cbegin() const;

    const_iterator cend() const;
};