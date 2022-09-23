#include "matrix.h"

#include <cmath>
#include <stdexcept>
namespace matrix {
Matrix::Matrix() : rows_(0), columns_(0), matrix_(nullptr) {}

Matrix::Matrix(int size) : rows_(size), columns_(size) {
  ExceptionMatrixSize();
  AlocateMemory();
}

Matrix::Matrix(int rows, int columns) : rows_(rows), columns_(columns) {
  ExceptionMatrixSize();
  AlocateMemory();
}

Matrix::Matrix(int rows, int columns, const std::vector<double>& vec)
    : rows_(rows), columns_(columns) {
  ExceptionMatrixSize();
  AlocateMemory();
  for (int i = 0, z = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++, z++) {
      matrix_[i][j] = vec[z];
    }
  }
}

Matrix::Matrix(const Matrix& other) : Matrix(other.rows_, other.columns_) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix::Matrix(Matrix&& other) : rows_(other.rows_), columns_(other.columns_) {
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = other.columns_ = 0;
}

Matrix::~Matrix() {
  FreeMemory();
  rows_ = 0;
  columns_ = 0;
}

void Matrix::SetRows(int rows) {
  FreeMemory();
  rows_ = rows;
  AlocateMemory();
}

void Matrix::SetColumns(int columns) {
  FreeMemory();
  columns_ = columns;
  AlocateMemory();
}

bool Matrix::eq_matrix(const Matrix& other) {
  if (rows_ != other.rows_ || columns_ != other.columns_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      double res = fabs(matrix_[i][j] - other.matrix_[i][j]);
      if (res > 1e-7) {
        return false;
      }
    }
  }
  return true;
}

void Matrix::sum_matrix(const Matrix& other) {
  ExceptionSumSubMatrix(other);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::sub_matrix(const Matrix& other) {
  ExceptionSumSubMatrix(other);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void Matrix::mul_number(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::mul_matrix(const Matrix& other) {
  ExceptionMultiplyMatrix(other);
  Matrix temp(rows_, other.columns_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.columns_; j++) {
      for (int k = 0; k < columns_; k++) {
        temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = temp;
}

Matrix Matrix::transpose() {
  Matrix result(columns_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

Matrix Matrix::calc_complements() {
  ExceptionMatrixIsSquare();
  ExceptionMatrixCulcCompliment();
  Matrix result(*this);
  result.MinorMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      result.matrix_[i][j] *= (i + j) % 2 ? -1 : 1;
    }
  }
  return result;
}

double Matrix::determinant() {
  ExceptionMatrixIsSquare();
  double result = 0;
  if (rows_ < 2) {
    result = matrix_[0][0];
  } else {
    for (int i = 0; i < rows_; i++) {
      Matrix tmp = this->Minor(i, 0);
      result += matrix_[i][0] * (i % 2 ? -1 : 1) * tmp.determinant();
    }
  }
  return result;
}

Matrix Matrix::inverse_matrix() {
  ExceptionMatrixDeterminant();
  Matrix result(*this);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1 / result.matrix_[0][0];
    return result;
  }
  double det = result.determinant();
  result = result.transpose();
  result = result.calc_complements();
  result.mul_number(1.0 / det);
  return result;
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this == &other) {
    return *this;
  }
  FreeMemory();
  rows_ = other.rows_;
  columns_ = other.columns_;
  AlocateMemory();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

Matrix Matrix::operator+(const Matrix& other) {
  Matrix result(*this);
  result.sum_matrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix result(*this);
  result.sub_matrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix result(*this);
  result.mul_matrix(other);
  return result;
}

Matrix operator*(double x, const Matrix& other) {
  Matrix result(other);
  result.mul_number(x);
  return result;
}

Matrix operator*(const Matrix& other, double x) {
  Matrix result(other);
  result.mul_number(x);
  return result;
}

bool Matrix::operator==(const Matrix& other) { return this->eq_matrix(other); }

Matrix& Matrix::operator+=(const Matrix& other) {
  this->sum_matrix(other);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  this->sub_matrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  this->mul_matrix(other);
  return *this;
}

Matrix& Matrix::operator*=(double x) {
  this->mul_number(x);
  return *this;
}

double Matrix::operator()(int row, int column) {
  ExceptionMatrixOperatorBrace(row, column);
  return matrix_[row][column];
}

void Matrix::AlocateMemory() {
  if (rows_ == 0 || columns_ == 0) {
    matrix_ = nullptr;
  } else {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[columns_]{};
    }
  }
}

void Matrix::FreeMemory() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

Matrix Matrix::Minor(int index_row, int index_column) {
  Matrix result(rows_ - 1, columns_ - 1);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.columns_; j++) {
      if (i < index_row && j < index_column) {
        result.matrix_[i][j] = matrix_[i][j];
      } else if (i >= index_row && j < index_column) {
        result.matrix_[i][j] = matrix_[i + 1][j];
      } else if (i < index_row && j >= index_column) {
        result.matrix_[i][j] = matrix_[i][j + 1];
      } else {
        result.matrix_[i][j] = matrix_[i + 1][j + 1];
      }
    }
  }
  return result;
}

void Matrix::MinorMatrix() {
  Matrix tmp1(*this);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      Matrix tmp = tmp1.Minor(i, j);
      matrix_[i][j] = tmp.determinant();
    }
  }
}

void Matrix::ExceptionMatrixSize() {
  if (rows_ < 0 || columns_ < 0) {
    throw std::out_of_range("Rows or columns are less 0!");
  }
}

void Matrix::ExceptionSumSubMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || columns_ != other.columns_) {
    throw std::out_of_range("Rows or columns are not equal!");
  }
}

void Matrix::ExceptionMultiplyMatrix(const Matrix& other) {
  if (columns_ != other.rows_) {
    throw std::out_of_range("Columns are not equal rows!");
  }
}

void Matrix::ExceptionMatrixIsSquare() {
  if (rows_ != columns_ || rows_ < 1) {
    throw std::out_of_range("Matrix are not square!");
  }
}

void Matrix::ExceptionMatrixDeterminant() {
  if (fabs(this->determinant() - 0.0) < 1e-7) {
    throw std::out_of_range("Determinant equal 0!");
  }
}

void Matrix::ExceptionMatrixOperatorBrace(int row, int column) {
  if (rows_ <= row || columns_ <= column || row < 0 || column < 0) {
    throw std::out_of_range("Out of matrix range!");
  }
}

void Matrix::ExceptionMatrixCulcCompliment() {
  if (rows_ < 2) {
    throw std::out_of_range("Matrix size less then 2!");
  }
}

}  // namespace matrix
