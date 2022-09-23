#include <gtest/gtest.h>

#include "matrix.h"

TEST(constructor_test, empty_constructor1) {
  matrix::Matrix empty;
  ASSERT_EQ(empty.GetRows(), 0);
  ASSERT_EQ(empty.GetColumns(), 0);
}

TEST(constructor_test, empty_constructor2) {
  matrix::Matrix empty(0, 0);
  ASSERT_EQ(empty.GetRows(), 0);
  ASSERT_EQ(empty.GetColumns(), 0);
}

TEST(constructor_test, one_argument_constructor) {
  matrix::Matrix one(5);
  ASSERT_EQ(one.GetRows(), one.GetColumns());
  ASSERT_EQ(one.GetColumns(), 5);
}

TEST(constructor_test, two_arguments_constructor) {
  matrix::Matrix two(4, 9);
  ASSERT_EQ(two.GetRows(), 4);
  ASSERT_EQ(two.GetColumns(), 9);
}

TEST(constructor_test, move_constructor) {
  std::vector<double> vec1{0.1, 0.03, 0.003, 2, 67, 0.4, 13, 0.05, 9};
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(std::move(matrix1));
  matrix::Matrix matrix3(3, 3, vec1);
  ASSERT_EQ(matrix2 == matrix3, 1);
}

TEST(constructor_test, copy_constructor) {
  std::vector<double> vec1{0.1, 0.03, 0.003, 2, 67, 0.4, 13, 0.05, 9};
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(matrix1);
  matrix::Matrix matrix3(3, 3, vec1);
  ASSERT_EQ(matrix2 == matrix3, 1);
}

TEST(setter_test, setter_row1) {
  matrix::Matrix matrix(1, 1);
  matrix.SetRows(5);
  ASSERT_EQ(matrix.GetRows(), 5);
}

TEST(setter_test, setter_row2) {
  matrix::Matrix matrix(1, 1);
  matrix.SetRows(0);
  ASSERT_EQ(matrix.GetRows(), 0);
}

TEST(setter_test, setter_columns1) {
  matrix::Matrix matrix(1, 1);
  matrix.SetColumns(3);
  ASSERT_EQ(matrix.GetColumns(), 3);
}

TEST(setter_test, setter_columns2) {
  matrix::Matrix matrix(1, 1);
  matrix.SetColumns(0);
  ASSERT_EQ(matrix.GetColumns(), 0);
}

TEST(compare_test, fail_test1) {
  matrix::Matrix matrix1(1, 1);
  matrix::Matrix matrix2(2, 2);
  ASSERT_EQ(matrix1 == matrix2, 0);
}

TEST(compare_test, fail_test2) {
  std::vector<double> vec1{1, 1, 1, 2, 2, 2, 3, 3, 3};
  std::vector<double> vec2{1, 2, 3, 3, 2, 1, 4, 5, 6};
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  ASSERT_EQ(matrix1 == matrix2, 0);
}

TEST(arifmetic_test, sum_matrix) {
  std::vector<double> vec1{1, 1, 1, 2, 2, 2, 3, 3, 3};
  std::vector<double> vec2{1, 2, 3, 3, 2, 1, 4, 5, 6};
  std::vector<double> vec3{2, 3, 4, 5, 4, 3, 7, 8, 9};
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  matrix::Matrix matrix3(3, 3, vec3);
  matrix1.sum_matrix(matrix2);
  ASSERT_EQ(matrix1.eq_matrix(matrix3), 1);
}

TEST(arifmetic_test, sub_matrix) {
  std::vector<double> vec1{3, 3, 3, 4, 4, 4, 7, 7, 7};
  std::vector<double> vec2{1, 2, 3, 3, 2, 1, 4, 5, 6};
  std::vector<double> vec3{2, 1, 0, 1, 2, 3, 3, 2, 1};
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  matrix::Matrix matrix3(3, 3, vec3);
  matrix1.sub_matrix(matrix2);
  ASSERT_EQ(matrix1.eq_matrix(matrix3), 1);
}

TEST(arifmetic_test, mul_number_matrix) {
  std::vector<double> vec1{3, 3, 3, 4, 4, 4, 7, 7, 7};
  std::vector<double> vec2{15.75, 15.75, 15.75, 21,   21,
                           21,    36.75, 36.75, 36.75};
  float num = 5.25;
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  matrix1.mul_number(num);
  ASSERT_EQ(matrix1.eq_matrix(matrix2), 1);
}

TEST(arifmetic_test, mul_matrix) {
  std::vector<double> vec1{1, 2, 3};
  std::vector<double> vec2{4, 5, 6};
  std::vector<double> vec3{4, 5, 6, 8, 10, 12, 12, 15, 18};
  matrix::Matrix matrix1(3, 1, vec1);
  matrix::Matrix matrix2(1, 3, vec2);
  matrix::Matrix matrix3(3, 3, vec3);
  matrix1.mul_matrix(matrix2);
  ASSERT_EQ(matrix1.eq_matrix(matrix3), 1);
}

TEST(arifmetic_test, transpose_matrix) {
  std::vector<double> vec1{1, 2, 3};
  std::vector<double> vec2{1, 2, 3};
  matrix::Matrix matrix1(3, 1, vec1);
  matrix::Matrix matrix2(1, 3, vec2);
  matrix::Matrix matrix3(1, 3);
  matrix3 = matrix1.transpose();
  ASSERT_EQ(matrix3.eq_matrix(matrix2), 1);
}

TEST(arifmetic_test, determinant_matrix1) {
  std::vector<double> vec1{0.1, 0.03, 0.003, 2, 67, 0.4, 13, 0.05, 9};
  matrix::Matrix matrix1(3, 3, vec1);
  double res = 57.3013;
  double res1 = matrix1.determinant();
  ASSERT_EQ(res, res1);
}

TEST(arifmetic_test, determinant_matrix2) {
  std::vector<double> vec1{124.2, 215.25, 4.53,  8.32,   75.24, 74.21,
                           3.42,  12,     472.2, 26.236, 19.2,  -9.23,
                           10.23, 65.3,   94.5,  1.99};
  matrix::Matrix matrix1(4, 4, vec1);
  double res = -91467183.198996989992;
  double res1 = matrix1.determinant();
  ASSERT_NEAR(res, res1, 1e-7);
}

TEST(arifmetic_test, determinant_matrix3) {
  std::vector<double> vec1{0.2341};
  matrix::Matrix matrix1(1, 1, vec1);
  double res = 0.2341;
  double res1 = matrix1.determinant();
  ASSERT_NEAR(res, res1, 1e-7);
}

TEST(arifmetic_test, calc_complements_matrix) {
  std::vector<double> vec1{0.73,  -0.19, -0.12, -0.07, 0.72,
                           -0.17, -0.12, -0.15, 0.92};
  std::vector<double> vec2{0.6369, 0.0848, 0.0969, 0.1928, 0.6572,
                           0.1323, 0.1187, 0.1325, 0.5123};

  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  matrix::Matrix res1 = matrix1.calc_complements();
  ASSERT_EQ(res1.eq_matrix(matrix2), 1);
}

TEST(arifmetic_test, invers_matrix1) {
  std::vector<double> vec1{0.73,  -0.07, -0.12, -0.19, 0.72,
                           -0.15, -0.12, -0.17, 0.92};
  std::vector<double> vec2{1.45678035,  0.193962905, 0.221639215,
                           0.440991132, 1.50321251,  0.302609579,
                           0.27150232,  0.303067038, 1.17178297};
  std::vector<double> vec3{1, 0, 0, 0, 1, 0, 0, 0, 1};

  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  matrix::Matrix matrix3(3, 3, vec3);
  matrix::Matrix res1 = matrix1.inverse_matrix();
  ASSERT_EQ(res1.eq_matrix(matrix2), 1);
  res1 *= matrix1;
  ASSERT_EQ(res1 == matrix3, 1);
}

TEST(arifmetic_test, invers_matrix2) {
  std::vector<double> vec1{5};
  std::vector<double> vec2{1. / 5.};
  std::vector<double> vec3{1};

  matrix::Matrix matrix1(1, 1, vec1);
  matrix::Matrix matrix2(1, 1, vec2);
  matrix::Matrix matrix3(1, 1, vec3);
  matrix::Matrix res1 = matrix1.inverse_matrix();
  ASSERT_EQ(res1.eq_matrix(matrix2), 1);
  res1 *= matrix1;
  ASSERT_EQ(res1 == matrix3, 1);
}

TEST(operator_test, operator_assignment) {
  std::vector<double> vec1{1.253, 2.2,   3.325, 4.235, 5.253,
                           6.253, 7.865, 8.45,  9.854};
  std::vector<double> vec2{423.12, 24.24,      124.124,   0.4409911, 9924.2,
                           11.443, 125.271502, 2.3030670, 1.171782};

  std::vector<double> vec3{424.373, 26.44,      127.449,   4.6759911, 9929.453,
                           17.696,  133.136502, 10.753067, 11.025782};
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  matrix::Matrix matrix3(3, 3, vec3);
  matrix1 = matrix2;
  ASSERT_EQ(matrix1.eq_matrix(matrix2), 1);
  matrix1 = matrix3;
  matrix3 = matrix3;
  ASSERT_EQ(matrix1.eq_matrix(matrix3), 1);
}

TEST(operator_test, operator_plus) {
  std::vector<double> vec1{1.253, 2.2,   3.325, 4.235, 5.253,
                           6.253, 7.865, 8.45,  9.854};
  std::vector<double> vec2{423.12, 24.24,      124.124,   0.4409911, 9924.2,
                           11.443, 125.271502, 2.3030670, 1.171782};

  std::vector<double> vec3{424.373, 26.44,      127.449,   4.6759911, 9929.453,
                           17.696,  133.136502, 10.753067, 11.025782};
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  matrix::Matrix matrix3(3, 3, vec3);
  matrix::Matrix res1 = matrix1 + matrix2;
  ASSERT_EQ(res1.eq_matrix(matrix3), 1);
}

TEST(operator_test, operator_minus) {
  std::vector<double> vec1{14.221, 1254.522, 152.325, -4.235, 12.23,
                           61.3,   5712.865, 242.45,  19.14};
  std::vector<double> vec2{-42.12, 122.24,   174.124, 1.4211,   994.2,
                           131.43, 1253.212, 212.370, -1123.382};

  std::vector<double> vec3{56.341, 1132.282, -21.799, -5.6561, -981.97,
                           -70.13, 4459.653, 30.08,   1142.522};
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  matrix::Matrix matrix3(3, 3, vec3);
  matrix::Matrix res1 = matrix1 - matrix2;
  ASSERT_EQ(res1.eq_matrix(matrix3), 1);
}

TEST(operator_test, operator_multiply) {
  std::vector<double> vec1{1.21,   154.522, 752.325, 34.25,  -124.3,
                           6431.3, 572.65,  442.45,  -149.49};
  std::vector<double> vec2{-41.12,  122.24,    174.124,   12.421,   1974.22,
                           6121.43, 12243.212, -21422.30, -2123.382};

  std::vector<double> vec3{
      9212744.030462, -15811323.51426,   -651367.06665,
      78736817.0453,  -138014446.816,    -14411036.6586,
      -1848289.45843, 4145914.001999999, 3125563.1872799997};
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  matrix::Matrix matrix3(3, 3, vec3);
  matrix::Matrix res1 = matrix1 * matrix2;
  ASSERT_EQ(res1.eq_matrix(matrix3), 1);
}

TEST(operator_test, operator_multiply_number) {
  std::vector<double> vec1{1, 2, 3, 1.5, 2.5, 3.5, -3.3, -2.2, -1.1};
  std::vector<double> vec2{3, 6, 9, 4.5, 7.5, 10.5, -9.9, -6.6, -3.3};
  float x = 3.0;
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  matrix::Matrix res1 = matrix1 * x;
  matrix::Matrix res2 = x * matrix1;
  ASSERT_EQ(res1.eq_matrix(matrix2), 1);
  ASSERT_EQ(res2.eq_matrix(matrix2), 1);
}

TEST(operator_test, operator_equal) {
  std::vector<double> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<double> vec2{1, 2, 3, 4, 5, 6, 7, 8, 9};
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  ASSERT_EQ(matrix1 == matrix2, 1);
}

TEST(operator_test, operator_plus_equal) {
  std::vector<double> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<double> vec2{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<double> vec3{2, 4, 6, 8, 10, 12, 14, 16, 18};
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  matrix::Matrix matrix3(3, 3, vec3);
  matrix1 += matrix2;
  ASSERT_EQ(matrix1 == matrix3, 1);
}

TEST(operator_test, operator_minus_equal) {
  std::vector<double> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<double> vec2{10, 24, 1, 2, 12, 4, 1, 2, 14};
  std::vector<double> vec3{-9, -22, 2, 2, -7, 2, 6, 6, -5};
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  matrix::Matrix matrix3(3, 3, vec3);
  matrix1 -= matrix2;
  ASSERT_EQ(matrix1 == matrix3, 1);
}

TEST(operator_test, operator_multyply_equal1) {
  std::vector<double> vec1{1.21,   154.522, 752.325, 34.25,  -124.3,
                           6431.3, 572.65,  442.45,  -149.49};
  std::vector<double> vec2{-41.12,  122.24,    174.124,   12.421,   1974.22,
                           6121.43, 12243.212, -21422.30, -2123.382};

  std::vector<double> vec3{
      9212744.030462, -15811323.51426,   -651367.06665,
      78736817.0453,  -138014446.816,    -14411036.6586,
      -1848289.45843, 4145914.001999999, 3125563.1872799997};
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  matrix::Matrix matrix3(3, 3, vec3);
  matrix1 *= matrix2;
  ASSERT_EQ(matrix1 == matrix3, 1);
}

TEST(operator_test, operator_multyply_equal2) {
  std::vector<double> vec1{1, 2, 3, 1.5, 2.5, 3.5, -3.3, -2.2, -1.1};
  std::vector<double> vec2{3, 6, 9, 4.5, 7.5, 10.5, -9.9, -6.6, -3.3};
  float x = 3.0;
  matrix::Matrix matrix1(3, 3, vec1);
  matrix::Matrix matrix2(3, 3, vec2);
  matrix1 *= x;
  ASSERT_EQ(matrix1 == matrix2, 1);
}

TEST(operator_test, operator_bracer) {
  std::vector<double> vec1{1, 2, 3, 1.5, 2.5, 3.5, -3.3, -2.2, -1.1};
  matrix::Matrix matrix1(3, 3, vec1);
  ASSERT_EQ(matrix1(2, 2), -1.1);
}

TEST(exception, constructor_exception) {
  std::vector<double> vec1{1, 2, 3, 1.5, 2.5, 3.5, -3.3, -2.2, -1.1};
  EXPECT_THROW(matrix::Matrix matrix1(-3, 3), std::out_of_range);
  EXPECT_THROW(matrix::Matrix matrix2(-3, 3, vec1), std::out_of_range);
}
TEST(exception, arifmetic_exception) {
  std::vector<double> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9};
  matrix::Matrix matrix1(3, 1);
  matrix::Matrix matrix2(2, 4);
  matrix::Matrix matrix3(3, 3, vec1);
  matrix::Matrix matrix4(1, 1);
  EXPECT_THROW(matrix1.sum_matrix(matrix2), std::out_of_range);
  EXPECT_THROW(matrix1 + matrix2, std::out_of_range);

  EXPECT_THROW(matrix1.sub_matrix(matrix2), std::out_of_range);
  EXPECT_THROW(matrix1 - matrix2, std::out_of_range);

  EXPECT_THROW(matrix1.mul_matrix(matrix2), std::out_of_range);
  EXPECT_THROW(matrix1 * matrix2, std::out_of_range);

  EXPECT_THROW(matrix1 += matrix2, std::out_of_range);
  EXPECT_THROW(matrix1 -= matrix2, std::out_of_range);
  EXPECT_THROW(matrix1 *= matrix2, std::out_of_range);

  EXPECT_THROW(matrix1.determinant(), std::out_of_range);
  EXPECT_THROW(matrix1.calc_complements(), std::out_of_range);
  EXPECT_THROW(matrix1.inverse_matrix(), std::out_of_range);
  EXPECT_THROW(matrix3.inverse_matrix(), std::out_of_range);

  EXPECT_THROW(matrix1(10, 10), std::out_of_range);
  EXPECT_THROW(matrix4.calc_complements(), std::out_of_range);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
