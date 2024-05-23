#include <gtest/gtest.h>
#include "Histogram.hpp"

using namespace std;

TEST(Constructors, EmptyVector) {
    map<string, size_t> mp;

    vector<string> words{};

    Histogram ht(words);
    EXPECT_EQ(mp, ht.data());
}

TEST(Constructors, VectorOfEmptyStrings) {
    map<string, size_t> mp;

    vector<string> words{"", "", ""};

    Histogram ht(words);
    EXPECT_EQ(mp, ht.data());
}

TEST(Constructors, VectorSimpleStrings) {
    map<string, size_t> mp;
    mp["1"] = 1;
    mp["2"] = 2;
    mp["3"] = 3;

    vector<string> v = {"1", "2", "2", "3", "3", "3"};

    Histogram ht(v);
    EXPECT_EQ(mp, ht.data());
}

TEST(Operators, AddingEmptyHist) {
    map<string, size_t> mp;
    mp["1"] = 1;
    mp["2"] = 2;
    mp["3"] = 3;

    vector<string> v = {"1", "2", "2", "3", "3", "3"};

    Histogram ht(v);
    Histogram h = ht + Histogram();
    EXPECT_EQ(mp, h.data());
}

TEST(Operators, AddingHist) {
    map<string, size_t> mp;
    mp["1"] = 1;
    mp["2"] = 2;
    mp["3"] = 3;

    map<string, size_t> mp_res;
    mp_res["1"] = 2;
    mp_res["2"] = 4;
    mp_res["3"] = 6;

    vector<string> v = {"1", "2", "2", "3", "3", "3"};

    Histogram ht(v);
    Histogram h = ht + ht;
    EXPECT_EQ(mp_res, h.data());
}

TEST(Operators, MinusEmptyHist) {
    map<string, size_t> mp;
    mp["1"] = 1;
    mp["2"] = 2;
    mp["3"] = 3;

    vector<string> v = {"1", "2", "2", "3", "3", "3"};
    Histogram h(v);
    Histogram res = h - Histogram();
    EXPECT_EQ(mp, res.data());
}

TEST(Operators, MinusSameHist) {
    map<string, size_t> mp;
    map<string, size_t> mp_res;
    mp["1"] = 1;
    mp["2"] = 2;
    mp["3"] = 3;


    vector<string> v = {"1", "2", "2", "3", "3", "3"};
    Histogram h(v);
    Histogram res = h - h;
    EXPECT_EQ(mp_res, res.data());
}

TEST(Operators, MinusHistToMinus) {
    map<string, size_t> mp;
    map<string, size_t> mp_res;

    vector<string> v = {"1", "2", "2", "3", "3", "3"};
    vector<string> v2 = {"1", "1", "2", "2", "2", "3", "3", "3", "3"};
    Histogram h(v);
    Histogram h2(v2);
    Histogram res = h - h2;
    EXPECT_EQ(mp_res, res.data());
}