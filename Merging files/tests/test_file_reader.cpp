#include "gtest/gtest.h"
#include <sstream>
#include "StreamMerger.h"

TEST(Base, FilledStreamsTest) {
    std::string in_s_1("1st row\n2nd row\n3rd row\n");
    std::string in_s_2("first row\nsecond row\nthird row\n");
    std::string correct_row = "1st row\nfirst row\n2nd row\nsecond row\n3rd row\nthird row\n";

    std::vector<std::unique_ptr<std::istream>> streams;
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_1));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_2));

    std::ostringstream out;
    StreamMerger::merge(streams, out);

    EXPECT_EQ(out.str(), correct_row);
}

TEST(Base, EmptyRowTest) {
    std::string in_s_1("1st row\n\n3rd row\n");
    std::string in_s_2("first row\nsecond row\nthird row\n");
    std::string correct_row = "1st row\nfirst row\n3rd row\nsecond row\nthird row\n";

    std::vector<std::unique_ptr<std::istream>> streams;
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_1));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_2));

    std::ostringstream out;
    StreamMerger::merge(streams, out);

    EXPECT_EQ(out.str(), correct_row);
}

TEST(Base, EmptyStreamTest) {
    std::string in_s_1;
    std::string in_s_2("first row\nsecond row\nthird row\n");

    std::vector<std::unique_ptr<std::istream>> streams;
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_1));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_2));

    std::ostringstream out;
    StreamMerger::merge(streams, out);

    EXPECT_EQ(out.str(), in_s_2);
}

TEST(Base, DifferentSizesTest) {
    std::string in_s_1("1st row\n");
    std::string in_s_2("first row\nsecond row\nthird row\n");

    std::vector<std::unique_ptr<std::istream>> streams;
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_1));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_2));

    std::ostringstream out;
    StreamMerger::merge(streams, out);

    std::string correct_row = "1st row\nfirst row\nsecond row\nthird row\n";
    EXPECT_EQ(out.str(), correct_row);
}

TEST(Base, EmptyStreamsVectorTest) {
    std::vector<std::unique_ptr<std::istream>> streams;
    std::ostringstream out;
    StreamMerger::merge(streams, out);

    std::string correct_row;
    EXPECT_EQ(out.str(), correct_row);
}

TEST(SingleStream, FilledTest) {
    std::string in_s_1("first row\nsecond row\nthird row\n");

    std::vector<std::unique_ptr<std::istream>> streams;
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_1));

    EXPECT_EQ(streams.size(), 1);

    std::ostringstream out;
    StreamMerger::merge(streams, out);

    EXPECT_EQ(out.str(), in_s_1);
}

TEST(SingleStream, EmptyTest) {
    std::string in_s_1;

    std::vector<std::unique_ptr<std::istream>> streams;
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_1));

    EXPECT_EQ(streams.size(), 1);

    std::ostringstream out;
    StreamMerger::merge(streams, out);

    EXPECT_EQ(out.str(), in_s_1);
}

TEST(SingleStream, OnlySpacesAndTabsTest) {
    std::string in_s_1("   \n       \n\t\t\n\n\n\n\n");
    std::string correct_row;

    std::vector<std::unique_ptr<std::istream>> streams;
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_1));

    EXPECT_EQ(streams.size(), 1);

    std::ostringstream out;
    StreamMerger::merge(streams, out);

    EXPECT_EQ(out.str(), correct_row);
}

TEST(SingleStream, ManyEmptyRowsTest) {
    std::string in_s_1("   \n       \n\t\t\n\n\n\n\nabc\n\n\n\n\n\nd");
    std::string correct_row("abc\nd\n");

    std::vector<std::unique_ptr<std::istream>> streams;
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_1));

    EXPECT_EQ(streams.size(), 1);

    std::ostringstream out;
    StreamMerger::merge(streams, out);

    EXPECT_EQ(out.str(), correct_row);
}

TEST(ManyStreams, FilledTest) {
    std::string in_s_1("1st row\n2nd row\n3rd row\n");
    std::string in_s_2("first row\nsecond row\nthird row\n");
    std::string in_s_3("A row\nB row\nC row\n");
    std::string in_s_4("First row\nSecond row\nThird row\n");
    std::string in_s_5("1\n2\n3\n");
    std::string in_s_6("first\nsecond\nthird\n");
    std::string correct_row = "1st row\nfirst row\nA row\nFirst row\n1\nfirst\n2nd row\nsecond row\nB row\nSecond row\n2\nsecond\n3rd row\nthird row\nC row\nThird row\n3\nthird\n";

    std::vector<std::unique_ptr<std::istream>> streams;
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_1));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_2));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_3));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_4));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_5));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_6));

    std::ostringstream out;
    StreamMerger::merge(streams, out);

    EXPECT_EQ(out.str(), correct_row);
}

TEST(ManyStreams, BrokenRowsTest) {
    std::string in_s_1("1st row\n2nd row\n3rd row\n");
    std::string in_s_2("\n\nfirst row\n");
    std::string in_s_3("       \n\t\t\nA row\n");
    std::string in_s_4("First row\nSecond row\nThird row\n");
    std::string in_s_5;
    std::string in_s_6("first\nsecond\nthird\n");
    std::string correct_row = "1st row\nfirst row\nA row\nFirst row\nfirst\n2nd row\nSecond row\nsecond\n3rd row\nThird row\nthird\n";

    std::vector<std::unique_ptr<std::istream>> streams;
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_1));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_2));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_3));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_4));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_5));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_6));

    std::ostringstream out;
    StreamMerger::merge(streams, out);

    EXPECT_EQ(out.str(), correct_row);
}

TEST(ManyStreams, EmptyRowsTest) {
    std::string in_s_1("\n\n\n\n\n");
    std::string in_s_2;
    std::string in_s_3("             ");
    std::string in_s_4("\t\t\t\t\t\t\t");
    std::string in_s_5("   \t");
    std::string in_s_6("\t\n\t\n\t\n");
    std::string correct_row;

    std::vector<std::unique_ptr<std::istream>> streams;
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_1));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_2));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_3));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_4));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_5));
    streams.emplace_back(std::make_unique<std::istringstream>(in_s_6));

    std::ostringstream out;
    StreamMerger::merge(streams, out);

    EXPECT_EQ(out.str(), correct_row);
}
