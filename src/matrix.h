#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_
#include <vector>
namespace matrix {
class Matrix {
 public:
  Matrix();
  explicit Matrix(int size);
  Matrix(int rows, int columns);
  Matrix(int rows, int columns, const std::vector<double>& vec);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();
  int GetRows() { return rows_; }
  int GetColumns() { return columns_; }
  void SetRows(int rows);
  void SetColumns(int columns);
  bool eq_matrix(const Matrix& other);
  void sum_matrix(const Matrix& other);
  void sub_matrix(const Matrix& other);
  void mul_number(const double num);
  void mul_matrix(const Matrix& other);
  Matrix transpose();
  Matrix calc_complements();
  double determinant();
  Matrix inverse_matrix();

  Matrix& operator=(const Matrix& other);
  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  friend Matrix operator*(double x, const Matrix& other);
  friend Matrix operator*(const Matrix& other, double x);
  bool operator==(const Matrix& other);
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix& operator*=(double x);
  double operator()(int row, int column);

 private:
  int rows_;
  int columns_;
  double** matrix_;
  void AlocateMemory();
  void FreeMemory();
  void MinorMatrix();
  Matrix Minor(int index_row, int index_column);
  void ExceptionMatrixSize();
  void ExceptionSumSubMatrix(const Matrix& other);
  void ExceptionMultiplyMatrix(const Matrix& other);
  void ExceptionMatrixIsSquare();
  void ExceptionMatrixDeterminant();
  void ExceptionMatrixOperatorBrace(int row, int column);
  void ExceptionMatrixCulcCompliment();
};

Matrix operator*(double x, const Matrix& other);
Matrix operator*(const Matrix& other, double x);
}  // namespace matrix

#endif  // SRC__MATRIX_OOP_H_
