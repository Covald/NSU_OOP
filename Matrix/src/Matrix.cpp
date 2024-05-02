//
// Created by Covald on 19.03.2024.
//

#include "Matrix.hpp"
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <cstring>

double &Matrix::at(size_t row, size_t col) {
    return n_data[row * n_col + col];
}

double &Matrix::at(size_t row, size_t col) const {
    return n_data[row * n_col + col];
}

void Matrix::init(size_t rows, size_t cols) {
    if (rows != 0 && cols != 0) {
        n_row = rows;
        n_col = cols;
        n_data = new double[rows * cols];
        setZero();
    } else {
        n_row = 0;
        n_col = 0;
        n_data = nullptr;
    }
}

void Matrix::_make_invalid() {
    delete[] n_data;
    n_data = nullptr;
    n_row = 0;
    n_col = 0;
}

Matrix::Matrix(size_t cols) {
    init(1, cols);
}

Matrix::Matrix(size_t rows, size_t cols) {
    init(rows, cols);
}

Matrix::~Matrix() {
    delete[] n_data;
}

Matrix::Matrix(const Matrix &mat) {
    if (!mat.isValid()) return;
    init(mat.rows(), mat.cols());
    if (isValid())
        memcpy(n_data, mat.data(), n_row * n_col * sizeof(double));
}

Matrix Matrix::operator*(const Matrix &mat) const {
    if (n_row != mat.cols() || !isValid() || !mat.isValid()) return {};

    Matrix result(n_row, mat.cols());

    for (size_t row = 0; row < n_row; row++)
        for (size_t col = 0; col < mat.cols(); col++)
            for (size_t k = 0; k < n_col; k++)
                result.at(row, col) += at(row, k) * mat.at(k, col);

    return result;
}

Matrix Matrix::operator-(const Matrix &mat) const {
    if (n_row != mat.n_row || n_col != mat.n_col || !isValid() || !mat.isValid()) return {};

    auto result = *this;

    result -= mat;
    return result;
}

Matrix Matrix::operator+(const Matrix &mat) const {
    if (n_row != mat.n_row || n_col != mat.n_col || !isValid() || !mat.isValid()) return {};

    Matrix result = *this;
    if (!result.data()) return {};

    result += mat;
    return result;
}

Matrix Matrix::operator*(double value) const {
    if (!isValid()) return {};

    auto result = *this;
    result *= value;
    return result;
}

Matrix Matrix::operator/(double value) const {
    if (!isValid()) return {};

    auto result = *this;
    result /= value;
    return result;
}

Matrix &Matrix::operator=(const Matrix &mat) {
    if (this == &mat) return *this;

    delete[] n_data;
    n_row = mat.n_row;
    n_col = mat.n_col;
    if (n_col == 0 || n_row == 0) {
        n_data = nullptr;
        return *this;
    }
    n_data = new double[n_row * n_col];

    memcpy(n_data, mat.data(), n_row * n_col * sizeof(double));

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &mat) {
    auto res = *this * mat;
    delete[] n_data;
    n_data = res.data();
    n_row = res.rows();
    n_col = res.cols();
    res.n_data = nullptr;
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &mat) {
    if (!isValid() || !mat.isValid() || n_row != mat.rows() || n_col != mat.cols()) {
        _make_invalid();
        return *this;
    };

    for (size_t row = 0; row < n_row; row++)
        for (size_t col = 0; col < n_col; col++)
            at(row, col) += mat.coeffRef(row, col);

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &mat) {
    if (!isValid() || !mat.isValid() || n_row != mat.rows() || n_col != mat.cols()) {
        _make_invalid();
        return *this;
    };

    for (size_t row = 0; row < n_row; row++)
        for (size_t col = 0; col < n_col; col++)
            at(row, col) -= mat.at(row, col);

    return *this;
}

Matrix &Matrix::operator*=(double value) {
    if (!isValid()) return *this;

    for (size_t row = 0; row < n_row; row++)
        for (size_t col = 0; col < n_col; col++)
            at(row, col) *= value;

    return *this;
}

Matrix &Matrix::operator/=(double value) {
    if (!isValid()) {
        return *this;
    };

    for (size_t row = 0; row < n_row; row++)
        for (size_t col = 0; col < n_col; col++)
            at(row, col) /= value;

    return *this;
}

bool Matrix::isValid() const {
    return n_data != nullptr;
}

void Matrix::resize(size_t rows, size_t cols) {
    if (rows == n_row && cols == n_col) {
        setZero();
        return;
    }
    delete[] n_data;
    n_data = nullptr;
    init(rows, cols);
}

const double &Matrix::coeffRef(size_t rowIdx, size_t colIdx) const {
    if (rowIdx >= n_row) throw std::out_of_range("Row index out of range");
    if (colIdx >= n_col) throw std::out_of_range("Col index out of range");

    return at(rowIdx, colIdx);
}

double &Matrix::coeffRef(size_t rowIdx, size_t colIdx) {
    if (rowIdx >= n_row) throw std::out_of_range("Row index out of range");
    if (colIdx >= n_col) throw std::out_of_range("Col index out of range");

    return at(rowIdx, colIdx);
}

const double *Matrix::data() const {
    return n_data;
}

double *Matrix::data() {
    return n_data;
}

size_t Matrix::rows() const {
    return n_row;
}

size_t Matrix::cols() const {
    return n_col;
}

Matrix &Matrix::setIdentity() {
    if (!n_data) return *this;

    size_t tmp_size;

    if (rows() > cols()) tmp_size = cols();
    else tmp_size = rows();

    for (size_t tmp = 0; tmp < tmp_size; tmp++)
        at(tmp, tmp) = 1;


    return *this;
}

Matrix &Matrix::setZero() {
    if (!n_data) return *this;
    std::fill_n(n_data, n_row * n_col, 0.0);
    return *this;
}

Matrix &Matrix::setConstants(double value) {
    if (!n_data) return *this;

    for (size_t row = 0; row < n_row; row++) {
        for (size_t col = 0; col < n_col; col++) {
            at(row, col) = value;
        }
    }

    return *this;
}

Matrix &Matrix::setIdentity(size_t rows, size_t cols) {
    resize(rows, cols);
    setIdentity();
    return *this;
}

Matrix &Matrix::setZero(size_t rows, size_t cols) {
    resize(rows, cols);
    return *this;
}

Matrix &Matrix::setConstants(size_t rows, size_t cols, double value) {
    delete[] n_data;
    n_row = rows;
    n_col = cols;
    n_data = new double[n_row * n_col];
    setConstants(value);
    return *this;
}

Matrix Matrix::transpose() const {
    if (!isValid()) return {};
    Matrix temp(n_row, n_col);

    for (size_t row = 0; row < n_row; row++) {
        for (size_t col = 0; col < n_col; col++) {
            temp.at(row, col) = at(col, row);
        }
    }

    return temp;
}


double Matrix::determinant() const {
    size_t size = n_row;
    auto *temp_matrix = new double[size * size];
    std::copy(n_data, n_data + size * size, temp_matrix);

    double determinant = 1.0;
    for (size_t row = 0; row < size; row++) {
        size_t pivot_row = row;
        for (size_t next_row = row + 1; next_row < size; next_row++) {
            if (fabs(temp_matrix[next_row * size + row]) > fabs(temp_matrix[pivot_row * size + row])) {
                pivot_row = next_row;
            }
        }
        if (pivot_row != row) {
            for (size_t col = 0; col < size; col++) {
                std::swap(temp_matrix[row * size + col], temp_matrix[pivot_row * size + col]);
            }
            determinant *= -1;
        }
        if (fabs(temp_matrix[row * size + row]) < 1e-10) { // Проверка с погрешностью
            delete[] temp_matrix;
            return 0;
        }
        determinant *= temp_matrix[row * size + row];
        for (size_t next_row = row + 1; next_row < size; next_row++) {
            double factor = temp_matrix[next_row * size + row] / temp_matrix[row * size + row];
            for (size_t col = row + 1; col < size; col++) {
                temp_matrix[next_row * size + col] -= factor * temp_matrix[row * size + col];
            }
        }
    }
    delete[] temp_matrix;
    return determinant;
}

Matrix Matrix::inverse() const {
    if (!isValid() || cols() != rows()) return {};

    Matrix result = *this;

    size_t size = rows();
    Matrix E = identity(size, size);
    double temp;

    for (size_t k = 0; k < size; k++) {
        temp = result.at(k, k);
        if (temp == 0.0) {
            // Если встречается ноль на диагонали, ищем строку, где можно поменять
            // текущую строку с нулевым значением на диагонали
            size_t swapRow = k + 1;
            for (; swapRow < size; swapRow++) {
                if (result.at(swapRow, k) != 0.0) {
                    // Нашли ненулевой элемент, меняем строки местами
                    for (size_t col = 0; col < size; col++) {
                        std::swap(result.at(k, col), result.at(swapRow, col));
                        std::swap(E.at(k, col), E.at(swapRow, col));
                    }
                    break;
                }
            }
            if (swapRow == size) {
                // Если не найдено ненулевых элементов, обратная матрица не существует
                return {};
            }
            temp = result.at(k, k); // Обновляем temp после смены строк
        }
        for (size_t col = 0; col < size; col++) {
            result.at(k, col) /= temp;
            E.at(k, col) /= temp;
        }
        for (size_t row = k + 1; row < size; row++) {
            temp = result.at(row, k);
            for (size_t col = 0; col < size; col++) {
                result.at(row, col) -= result.at(k, col) * temp;
                E.at(row, col) -= E.at(k, col) * temp;
            }
        }
    }

    for (size_t k = size - 1; k > 0; k--) {
        for (size_t row = k - 1; row != static_cast<size_t>(-1); row--) {
            temp = result.at(row, k);
            for (size_t col = 0; col < size; col++) {
                result.at(row, col) -= result.at(k, col) * temp;
                E.at(row, col) -= E.at(k, col) * temp;
            }
        }
    }

    for (size_t row = 0; row < size; row++)
        for (size_t col = 0; col < size; col++)
            result.at(row, col) = E.at(row, col);

    return result;
}

double Matrix::det() const {
    if (!isValid() || cols() != rows()) return std::nan("NaN");

    double _det = determinant();

    return _det;
}

Matrix Matrix::identity(size_t rows, size_t cols) {
    auto res = Matrix(rows, cols);
    res.setIdentity();
    return res;
}

Matrix Matrix::zeros(size_t rows, size_t cols) {
    auto res = Matrix(rows, cols);
    return res;
}

Matrix Matrix::constants(size_t rows, size_t cols, double value) {
    auto res = Matrix(rows, cols);
    res.setConstants(value);
    return res;
}

Matrix operator*(double value, const Matrix &mat) {
    auto res = mat * value;
    return res;
}


std::ostream &operator<<(std::ostream &stream, const Matrix &matrix) {
    stream << std::endl;
    for (size_t row = 0; row < matrix.rows(); row++) {
        stream << "|";
        for (size_t col = 0; col < matrix.cols(); col++) {
            stream << std::setw(2) << matrix.coeffRef(row, col) << std::setw(2);
            stream << "|";
        }
        stream << std::endl;
    }
    stream << std::endl;
    return stream;
}
