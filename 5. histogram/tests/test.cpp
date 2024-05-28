#include <gtest/gtest.h>
#include "Histogram.hpp"
#include "Exporter.h"
#include "Parser.h"

TEST(Constructors, Default) {
    std::map<std::string, int> mp;
    Histogram ht;
    EXPECT_EQ(mp, ht.data());
}

TEST(Constructors, EmptyVector) {
    std::map<std::string, int> mp;
    std::vector<std::string> words{};
    Histogram ht(words);
    EXPECT_EQ(mp, ht.data());
}

TEST(Constructors, VectorOfEmptyStrings) {
    std::map<std::string, int> mp;
    std::vector<std::string> words{"", "", ""};
    Histogram ht(words);
    EXPECT_EQ(mp, ht.data());
}

TEST(Constructors, VectorSimpleStrings) {
    std::map<std::string, int> mp{{"1", 1},
                                  {"2", 2},
                                  {"3", 3}};
    std::vector<std::string> v = {"1", "2", "2", "3", "3", "3"};
    Histogram ht(v);
    EXPECT_EQ(mp, ht.data());
}

TEST(Constructors, CopyConstructor) {
    std::map<std::string, int> mp{{"1", 1},
                                  {"2", 2},
                                  {"3", 3}};
    std::vector<std::string> v = {"1", "2", "2", "3", "3", "3"};
    Histogram ht(v);
    Histogram ht_copy(ht);
    EXPECT_EQ(mp, ht_copy.data());
}

TEST(Constructors, Assgiment) {
    std::map<std::string, int> mp{{"1", 1},
                                  {"2", 2},
                                  {"3", 3}};
    std::vector<std::string> v = {"1", "2", "2", "3", "3", "3"};
    Histogram ht(v);
    Histogram ht_copy = ht;
    EXPECT_EQ(mp, ht_copy.data());
}

TEST(Constructors, AssigmentEmpty) {
    std::map<std::string, int> mp;
    Histogram ht;
    Histogram ht_copy = ht;
    EXPECT_EQ(mp, ht_copy.data());
}

TEST(Operators, AddingEmptyHist) {
    std::map<std::string, int> mp{{"1", 1},
                                  {"2", 2},
                                  {"3", 3}};
    std::vector<std::string> v = {"1", "2", "2", "3", "3", "3"};
    Histogram ht(v);
    Histogram h = ht + Histogram();
    EXPECT_EQ(mp, h.data());
}

TEST(Operators, AddingHist) {
    std::map<std::string, int> mp_res{{"1", 2},
                                      {"2", 4},
                                      {"3", 6}};
    std::vector<std::string> v = {"1", "2", "2", "3", "3", "3"};
    Histogram ht(v);
    Histogram h = ht + ht;
    EXPECT_EQ(mp_res, h.data());
}

TEST(Operators, SubstructEmptyHist) {
    std::map<std::string, int> mp{{"1", 1},
                                  {"2", 2},
                                  {"3", 3}};
    std::vector<std::string> v = {"1", "2", "2", "3", "3", "3"};
    Histogram h(v);
    Histogram res = h - Histogram();
    EXPECT_EQ(mp, res.data());
}

TEST(Operators, SubstructSameHist) {
    std::map<std::string, int> mp_res;
    std::vector<std::string> v = {"1", "2", "2", "3", "3", "3"};
    Histogram h(v);
    Histogram res = h - h;
    EXPECT_EQ(mp_res, res.data());
}

TEST(Operators, SubstructHistToMinus) {
    std::map<std::string, int> mp_res;
    std::vector<std::string> v = {"1", "2", "2", "3", "3", "3"};
    std::vector<std::string> v2 = {"1", "1", "2", "2", "2", "3", "3", "3", "3"};
    Histogram h(v);
    Histogram h2(v2);
    Histogram res = h - h2;
    EXPECT_EQ(mp_res, res.data());
}

TEST(Operators, NotEqualHist) {
    std::vector<std::string> v1 = {"1", "2", "3"};
    std::vector<std::string> v2 = {"1", "2", "3", "4"};
    Histogram h1(v1);
    Histogram h2(v2);
    EXPECT_NE(h1, h2);
}

TEST(Operators, EqualHists) {
    std::vector<std::string> v1 = {"1", "2", "3"};
    std::vector<std::string> v2 = {"1", "2", "3"};
    Histogram h1(v1);
    Histogram h2(v2);
    EXPECT_EQ(h1, h1);
}

TEST(Operators, EqualEmptyHists) {
    Histogram h1;
    Histogram h2;
    EXPECT_EQ(h1, h2);
}

TEST(Operators, EqualCopyHist) {
    std::vector<std::string> v1 = {"1", "2", "3"};
    Histogram h1(v1);
    Histogram h2(h1);
    EXPECT_EQ(h1, h2);
}

TEST(Iterators, BeginEnd) {
    std::vector<std::string> v = {"1", "2", "2", "3", "3", "3"};
    Histogram ht(v);
    auto it = ht.begin();
    auto it_end = ht.end();
    EXPECT_EQ(ht.data().begin(), it);
    EXPECT_EQ(ht.data().end(), it_end);
    for (const auto &elem: ht.data()) {
        EXPECT_EQ(elem, *it);
        ++it;
    }
}

TEST(Parser, ParseWords) {
    std::istringstream input("a a b b c c c b b b a a a a a");

    Parser parser(input);
    std::vector<std::string> words = parser.parse();

    std::vector<std::string> expected_words = {"a", "a", "b", "b", "c", "c", "c", "b", "b", "b", "a", "a", "a", "a",
                                               "a"};
    EXPECT_EQ(expected_words, words);
}

TEST(Exporter, ExportHistogram) {
    std::map<std::string, int> mp{{"1", 1},
                                  {"2", 2},
                                  {"3", 3}};
    std::vector<std::string> v = {"1", "2", "2", "3", "3", "3"};
    Histogram ht(v);

    std::ostringstream output{};
    Exporter exporter(output);
    exporter.export_histogram(ht);

    std::string expected_result = "1: #\n2: ##\n3: ###\n";
    EXPECT_EQ(expected_result, output.str());
}