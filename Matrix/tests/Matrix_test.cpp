#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "stdexcept"
#include <iostream>
#include <cmath>
#include "vector"

using namespace std;

namespace {
    void set_matrix_by_vector(Matrix &mtx, const vector<double> &array) {
        if (mtx.rows() * mtx.cols() != array.size())
            return;
        memcpy(mtx.data(), array.data(), mtx.rows() * mtx.cols() * sizeof(double));
    }
}

bool operator==(const Matrix &m1, const Matrix &m2) {
    if (m1.rows() == m2.rows() && m1.cols() == m2.cols())
        return memcmp(m1.data(), m2.data(), m1.rows() * m1.cols() * sizeof(double)) == 0;
    else
        return false;
}

bool operator==(const Matrix &m, vector<double> array) {
    if (m.rows() * m.cols() == array.size()) {
        return memcmp(m.data(), array.data(), m.rows() * m.cols() * sizeof(double)) == 0;
    } else {
        return false;
    }
}


TEST(Constructors, default_constructor) {
    Matrix m;
    ASSERT_EQ(m.rows(), 0);
    ASSERT_EQ(m.cols(), 0);
    ASSERT_EQ(m.data(), nullptr);
    ASSERT_FALSE(m.isValid());
}

TEST(Constructors, two_arguments) {
    Matrix m(3, 3);
    vector<double> a({0, 0, 0, 0, 0, 0, 0, 0, 0});
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_TRUE(m.isValid());
    ASSERT_EQ(m, a);
}

TEST(Constructors, two_bad_arguments) {
    Matrix m(0, 0);
    ASSERT_EQ(m.rows(), 0);
    ASSERT_EQ(m.cols(), 0);
    ASSERT_EQ(m.data(), nullptr);
    ASSERT_FALSE(m.isValid());
}

TEST(Constructors, one_argument) {
    Matrix m(3);
    vector<double> a({0, 0, 0});
    ASSERT_EQ(m.rows(), 1);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_TRUE(m.isValid());
    ASSERT_EQ(m, a);
}

TEST(Constructors, one_bad_argument) {
    Matrix m(0);
    ASSERT_EQ(m.rows(), 0);
    ASSERT_EQ(m.cols(), 0);
    ASSERT_FALSE(m.isValid());
}

TEST(Constructors, copy) {
    Matrix m1(3, 3);
    vector<double> array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    set_matrix_by_vector(m1, array);

    Matrix m2 = m1;
    ASSERT_EQ(m2.rows(), m1.rows());
    ASSERT_EQ(m2.cols(), m1.cols());
    ASSERT_TRUE(m2.data());
    ASSERT_TRUE(m2.isValid());
    ASSERT_EQ(m1, m2);

    Matrix m3{};
    Matrix m4 = m3;
    ASSERT_EQ(m3.rows(), m4.rows());
    ASSERT_EQ(m3.cols(), m4.cols());
    ASSERT_EQ(m3.isValid(), m4.isValid());
}

TEST(BaseFunctions, resize) {
    Matrix m(3, 3);
    m.resize(1, 1);
    ASSERT_EQ(m.rows(), 1);
    ASSERT_EQ(m.cols(), 1);
    ASSERT_TRUE(m.isValid());
    ASSERT_TRUE(m.data());
    ASSERT_EQ(m.coeffRef(0, 0), 0);
}

TEST(BaseFunctions, coeff_ref) {
    Matrix m(3, 3);
    m.coeffRef(0, 0) = 1;
    ASSERT_EQ(m.coeffRef(0, 0), 1);
    const Matrix m2 = m;
    ASSERT_EQ(m2.coeffRef(0, 0), 1);
}

TEST(BaseFunctions, bad_coeff_ref) {
    Matrix m(3, 3);
    ASSERT_THROW(m.coeffRef(2, 3), std::out_of_range);
    ASSERT_THROW(m.coeffRef(3, 2), std::out_of_range);

    const Matrix m2(3, 3);
    ASSERT_THROW(m2.coeffRef(2, 3), std::out_of_range);
    ASSERT_THROW(m2.coeffRef(3, 2), std::out_of_range);

    Matrix m3{};
    ASSERT_THROW(m3.coeffRef(0, 0), std::out_of_range);

}

TEST(BaseFunctions, set_identity) {
    Matrix m = Matrix::identity(3, 3);
    vector<double> array({1, 0, 0, 0, 1, 0, 0, 0, 1});
    ASSERT_EQ(m, array);
}

TEST(BaseFunctions, set_constants) {
    Matrix m = Matrix::constants(3, 3, 3);
    vector<double> array({3, 3, 3, 3, 3, 3, 3, 3, 3});
    ASSERT_EQ(m, array);
}

TEST(Operators, self_assigment) {
    Matrix m(3, 3);
    vector<double> array({3, 3, 3, 3, 3, 3, 3, 3, 3});
    m.setConstants(3.0);
    m = m;
    ASSERT_EQ(m, array);
}

TEST(Operators, differnet_size_assigment) {
    Matrix mat1(2, 2);
    vector<double> array({3, 3, 3, 3, 3, 3, 3, 3, 3});
    mat1.setConstants(2.0);
    Matrix mat2(3, 3);
    mat2.setConstants(3.0);
    mat1 = mat2;
    ASSERT_EQ(mat1.rows(), 3);
    ASSERT_EQ(mat1.cols(), 3);

    ASSERT_EQ(mat1, array);
}

TEST(Operators, assigment) {
    Matrix m1(3, 3);
    vector<double> array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    set_matrix_by_vector(m1, array);
    Matrix m2(3, 3);
    m2 = m1;
    ASSERT_EQ(m2.rows(), m1.rows());
    ASSERT_EQ(m2.cols(), m1.cols());
    ASSERT_TRUE(m2.isValid());
    ASSERT_EQ(m1, m2);
}

TEST(Operators, assigment_default_matrix) {
    Matrix m1{};
    Matrix m2{};
    m1 = m2;
    ASSERT_EQ(m2.rows(), m1.rows());
    ASSERT_EQ(m2.cols(), m1.cols());
    ASSERT_FALSE(m2.isValid());
    ASSERT_EQ(m1, m2);
}

TEST(Operators, multiply_mat) {
    Matrix m1(3, 2);
    Matrix m2(2, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6});
    vector<double> m2_array({1, 2, 3, 4, 5, 6});
    set_matrix_by_vector(m1, m1_array);
    set_matrix_by_vector(m2, m2_array);
    Matrix m3 = m1 * m2;
    ASSERT_EQ(m3.rows(), m1.rows());
    ASSERT_EQ(m3.cols(), m2.cols());
    ASSERT_TRUE(m3.isValid());
    vector<double> m3_array({9, 12, 15, 19, 26, 33, 29, 40, 51});
    ASSERT_EQ(m3, m3_array);
}

TEST(Operators, multiply_mat_with_assigment) {
    Matrix m1(3, 2);
    Matrix m2(2, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6});
    vector<double> m2_array({1, 2, 3, 4, 5, 6});
    set_matrix_by_vector(m1, m1_array);
    set_matrix_by_vector(m2, m2_array);
    m1 *= m2;
    ASSERT_EQ(m1.rows(), m1.rows());
    ASSERT_EQ(m1.cols(), m2.cols());
    ASSERT_TRUE(m1.isValid());
    vector<double> m3_array({9, 12, 15, 19, 26, 33, 29, 40, 51});
    ASSERT_EQ(m1, m3_array);
}

TEST(Operators, addition_mat) {
    Matrix m1(3, 3);
    Matrix m2(3, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    vector<double> m2_array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    vector<double> m3_array({2, 4, 6, 8, 10, 12, 14, 16, 18});
    set_matrix_by_vector(m1, m1_array);
    set_matrix_by_vector(m2, m2_array);
    Matrix m3 = m1 + m2;
    ASSERT_EQ(m3, m3_array);
}

TEST(Operators, bad_addition_mat) {
    Matrix m1(3, 2);
    Matrix m2(2, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6});
    vector<double> m2_array({1, 2, 3, 4, 5, 6});
    set_matrix_by_vector(m1, m1_array);
    set_matrix_by_vector(m2, m2_array);
    Matrix m3 = m1 + m2;
    ASSERT_FALSE(m3.isValid());
}

TEST(Operators, addition_mat_with_assigment) {
    Matrix m1(3, 3);
    Matrix m2(3, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    vector<double> m2_array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    vector<double> m3_array({2, 4, 6, 8, 10, 12, 14, 16, 18});
    set_matrix_by_vector(m1, m1_array);
    set_matrix_by_vector(m2, m2_array);
    m1 += m2;
    ASSERT_EQ(m1, m3_array);
}

TEST(Operators, bad_addition_mat_with_assigment) {
    Matrix m1(3, 2);
    Matrix m2(2, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6});
    vector<double> m2_array({1, 2, 3, 4, 5, 6});
    set_matrix_by_vector(m1, m1_array);
    set_matrix_by_vector(m2, m2_array);
    m1 += m2;
    ASSERT_FALSE(m1.isValid());
}

TEST(Operators, subtraction_mat) {
    Matrix m1(3, 3);
    Matrix m2(3, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    vector<double> m2_array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    vector<double> m3_array({0, 0, 0, 0, 0, 0, 0, 0, 0});
    set_matrix_by_vector(m1, m1_array);
    set_matrix_by_vector(m2, m2_array);
    Matrix m3 = m1 - m2;
    ASSERT_EQ(m3, m3_array);
}

TEST(Operators, bad_subtraction_mat) {
    Matrix m1(3, 2);
    Matrix m2(2, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6});
    vector<double> m2_array({1, 2, 3, 4, 5, 6});
    set_matrix_by_vector(m1, m1_array);
    set_matrix_by_vector(m2, m2_array);
    Matrix m3 = m1 - m2;
    ASSERT_FALSE(m3.isValid());
}

TEST(Operators, subtraction_mat_with_assigment) {
    Matrix m1(3, 3);
    Matrix m2(3, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    vector<double> m2_array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    vector<double> m3_array({0, 0, 0, 0, 0, 0, 0, 0, 0});
    set_matrix_by_vector(m1, m1_array);
    set_matrix_by_vector(m2, m2_array);
    m1 -= m2;
    ASSERT_EQ(m1, m3_array);
}

TEST(Operators, bad_subtraction_mat_with_assigment) {
    Matrix m1(3, 2);
    Matrix m2(2, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6});
    vector<double> m2_array({1, 2, 3, 4, 5, 6});
    set_matrix_by_vector(m1, m1_array);
    set_matrix_by_vector(m2, m2_array);
    m1 -= m2;
    ASSERT_FALSE(m1.isValid());
}

TEST(Operators_numeric, multiply) {
    Matrix m1(3, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    set_matrix_by_vector(m1, m1_array);
    double k = 3;
    vector<double> result({3, 6, 9, 12, 15, 18, 21, 24, 27});
    Matrix m2 = m1 * k;
    ASSERT_EQ(m2, result);
}

TEST(Operators_numeric, divide) {
    Matrix m1(3, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    double k = 3;
    vector<double> result({3, 6, 9, 12, 15, 18, 21, 24, 27});
    set_matrix_by_vector(m1, result);

    Matrix m2 = m1 / k;
    ASSERT_EQ(m2, m1_array);
}

TEST(Operators_numeric, multiply_with_assigment) {
    Matrix m1(3, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    set_matrix_by_vector(m1, m1_array);
    double k = 3;
    vector<double> result({3, 6, 9, 12, 15, 18, 21, 24, 27});

    m1 *= k;
    ASSERT_EQ(m1, result);
}

TEST(Operators_numeric, divide_with_assigment) {
    Matrix m1(3, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    double k = 3;
    vector<double> result({3, 6, 9, 12, 15, 18, 21, 24, 27});
    set_matrix_by_vector(m1, result);
    m1 /= k;
    ASSERT_EQ(m1, m1_array);
}

TEST(Complex_functions, transpose) {
    Matrix m1(3, 3);
    vector<double> m1_array({1, 2, 3, 4, 5, 6, 7, 8, 9});
    set_matrix_by_vector(m1, m1_array);
    Matrix m2 = m1.transpose();
    for (size_t row = 0; row < m1.rows(); row++)
        for (size_t col = 0; col < m1.cols(); col++)
            ASSERT_EQ(m2.coeffRef(col, row), m1_array[row * m1.cols() + col]);
}

TEST(Complex_functions, inverse) {
    Matrix m1(3, 3);
    vector<double> m1_array({2, 5, 7, 6, 3, 4, 5, -2, -3});
    vector<double> m2_array({1, -1, 1, -38, 41, -34, 27, -29, 24});
    set_matrix_by_vector(m1, m1_array);
    Matrix m2 = m1.inverse();
    for (size_t row = 0; row < m2.rows(); row++)
        for (size_t col = 0; col < m2.cols(); col++)
            EXPECT_LE(
                    std::abs(m2_array[row * m2.cols() + col] - m2.coeffRef(row, col)),
                    1E-06);
}

TEST(Complex_functions, inverse_zero_main_diagonal) {
    Matrix m1(3, 3);
    vector<double> m1_array({0, 1, 1, 1, 0, 1, 1, 1, 0});
    vector<double> m2_array({-0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, -0.5});
    set_matrix_by_vector(m1, m1_array);
    Matrix m2 = m1.inverse();
    for (size_t row = 0; row < m2.rows(); row++)
        for (size_t col = 0; col < m2.cols(); col++)
            EXPECT_DOUBLE_EQ(m2.coeffRef(row, col), m2_array[row * m2.cols() + col]);
}

TEST(Complex_functions, bad_inverses) {
    Matrix m1{};
    ASSERT_FALSE(m1.inverse().isValid());
    Matrix m2(3, 2);
    ASSERT_FALSE(m2.inverse().isValid());
}

TEST(Complex_functions, determinant) {
    Matrix m1(3, 3);
    vector<double> m1_array({2, 5, 7, 6, 3, 4, 5, -2, -3});
    set_matrix_by_vector(m1, m1_array);
    double det = m1.det();
    ASSERT_LT(std::abs(det + 1), 1E-06);
}

TEST(Complex_functions, determinant_non_quadratic) {
    Matrix m1(2, 3);
    ASSERT_TRUE(std::isnan(m1.det()));
}

TEST(Complex_functions, determinant_non_valid) {
    Matrix m1{};
    ASSERT_TRUE(std::isnan(m1.det()));
}