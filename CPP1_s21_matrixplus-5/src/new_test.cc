#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

enum { FAIL, SUCCESS };

TEST(create_matrix, check_create_matrix_1) {
  EXPECT_ANY_THROW(S21Matrix mat_1(-1, 0));
}

TEST(create_matrix, check_copy_constructor_1) {
  S21Matrix mat_1(1, 2);

  mat_1.setValue(1, 1, 3);
  mat_1.setValue(1, 2, 1);

  S21Matrix mat_2(mat_1);

  bool result = mat_2.EqMatrix(mat_1);

  EXPECT_DOUBLE_EQ(result, SUCCESS);
}

TEST(create_matrix, check_move_constructor_1) {
  S21Matrix mat_1(1, 2);

  mat_1.setValue(1, 1, 3);
  mat_1.setValue(1, 2, 1);

  S21Matrix mat_2(mat_1);
  S21Matrix mat_3(std::move(mat_1));

  bool result = mat_2.EqMatrix(mat_3);

  EXPECT_FLOAT_EQ(result, SUCCESS);

  EXPECT_DOUBLE_EQ(0, mat_1.getCol());
  EXPECT_DOUBLE_EQ(0, mat_1.getRow());
}

TEST(sum_matrix, check_sum_1) {
  S21Matrix mat_1(3, 3);

  mat_1.setValue(1, 1, 1);
  mat_1.setValue(1, 2, 2);
  mat_1.setValue(1, 3, 3);

  mat_1.setValue(2, 1, 4);
  mat_1.setValue(2, 2, 5);
  mat_1.setValue(2, 3, 6);

  mat_1.setValue(3, 1, 7);
  mat_1.setValue(3, 2, 8);
  mat_1.setValue(3, 3, 9);

  S21Matrix mat_2(3, 3);

  mat_2.setValue(1, 1, 3);
  mat_2.setValue(1, 2, 1);
  mat_2.setValue(1, 3, 1);

  mat_2.setValue(2, 1, 3);
  mat_2.setValue(2, 2, 1);
  mat_2.setValue(2, 3, 1);

  mat_2.setValue(3, 1, 3);
  mat_2.setValue(3, 2, 1);
  mat_2.setValue(3, 3, 1);

  mat_1.SumMatrix(mat_2);

  EXPECT_DOUBLE_EQ(mat_1(1, 1), 4);
  EXPECT_DOUBLE_EQ(mat_1(1, 2), 3);
  EXPECT_DOUBLE_EQ(mat_1(1, 3), 4);

  EXPECT_DOUBLE_EQ(mat_1(2, 1), 7);
  EXPECT_DOUBLE_EQ(mat_1(2, 2), 6);
  EXPECT_DOUBLE_EQ(mat_1(2, 3), 7);

  EXPECT_DOUBLE_EQ(mat_1(3, 1), 10);
  EXPECT_DOUBLE_EQ(mat_1(3, 2), 9);
  EXPECT_DOUBLE_EQ(mat_1(3, 3), 10);
}

TEST(sum_matrix, check_sum_2) {
  S21Matrix mat_1(1, 1);

  mat_1.setValue(1, 1, 1);

  S21Matrix mat_2(2, 2);

  mat_2.setValue(1, 1, 3);
  mat_2.setValue(1, 2, 1);

  mat_2.setValue(2, 1, 3);
  mat_2.setValue(2, 2, 1);

  EXPECT_ANY_THROW(mat_1.SumMatrix(mat_2));
}

TEST(sub_matrix, check_sub_1) {
  S21Matrix mat_1(3, 3);

  mat_1.setValue(1, 1, 1);
  mat_1.setValue(1, 2, 2);
  mat_1.setValue(1, 3, 3);

  mat_1.setValue(2, 1, 4);
  mat_1.setValue(2, 2, 5);
  mat_1.setValue(2, 3, 6);

  mat_1.setValue(3, 1, 7);
  mat_1.setValue(3, 2, 8);
  mat_1.setValue(3, 3, 9);

  S21Matrix mat_2(3, 3);

  mat_2.setValue(1, 1, 3);
  mat_2.setValue(1, 2, 1);
  mat_2.setValue(1, 3, 1);

  mat_2.setValue(2, 1, 3);
  mat_2.setValue(2, 2, 1);
  mat_2.setValue(2, 3, 1);

  mat_2.setValue(3, 1, 3);
  mat_2.setValue(3, 2, 1);
  mat_2.setValue(3, 3, 1);

  mat_1.SubMatrix(mat_2);

  EXPECT_DOUBLE_EQ(mat_1(1, 1), -2);
  EXPECT_DOUBLE_EQ(mat_1(1, 2), 1);
  EXPECT_DOUBLE_EQ(mat_1(1, 3), 2);

  EXPECT_DOUBLE_EQ(mat_1(2, 1), 1);
  EXPECT_DOUBLE_EQ(mat_1(2, 2), 4);
  EXPECT_DOUBLE_EQ(mat_1(2, 3), 5);

  EXPECT_DOUBLE_EQ(mat_1(3, 1), 4);
  EXPECT_DOUBLE_EQ(mat_1(3, 2), 7);
  EXPECT_DOUBLE_EQ(mat_1(3, 3), 8);
}

TEST(sub_matrix, check_sub_2) {
  S21Matrix mat_1(1, 1);

  mat_1.setValue(1, 1, 1);

  S21Matrix mat_2(2, 2);

  mat_2.setValue(1, 1, 3);
  mat_2.setValue(1, 2, 1);

  mat_2.setValue(2, 1, 3);
  mat_2.setValue(2, 2, 1);

  EXPECT_ANY_THROW(mat_1.SumMatrix(mat_2));
}

TEST(eq_matrix, check_eq_1) {
  S21Matrix mat_1(1, 2);

  mat_1.setValue(1, 1, 3);
  mat_1.setValue(1, 2, 1);

  S21Matrix mat_2(1, 2);

  mat_2.setValue(1, 1, 3);
  mat_2.setValue(1, 2, 1);

  int result = mat_1.EqMatrix(mat_2);

  EXPECT_DOUBLE_EQ(result, SUCCESS);
}

TEST(eq_matrix, check_eq_2) {
  S21Matrix mat_1(1, 2);

  mat_1.setValue(1, 1, 3);
  mat_1.setValue(1, 2, 1);

  S21Matrix mat_2(1, 1);

  mat_2.setValue(1, 1, 0);

  int result = mat_1.EqMatrix(mat_2);

  EXPECT_DOUBLE_EQ(result, FAIL);
}

TEST(eq_matrix, check_eq_3) {
  S21Matrix mat_1(1, 2);

  mat_1.setValue(1, 1, 3);
  mat_1.setValue(1, 2, 1);

  S21Matrix mat_2(1, 1);

  mat_2.setValue(1, 1, 0);

  int result = mat_1.EqMatrix(mat_2);

  EXPECT_DOUBLE_EQ(result, FAIL);
}

TEST(eq_matrix, check_eq_4)  // летит время от времени
{
  S21Matrix mat_1(1, 2);

  mat_1.setValue(1, 1, 3);
  mat_1.setValue(1, 2, 1);

  S21Matrix mat_2(1, 2);

  mat_2.setValue(1, 1, 3);
  mat_2.setValue(1, 2, -1);

  int result = mat_1.EqMatrix(mat_2);

  EXPECT_DOUBLE_EQ(result, FAIL);
}

TEST(mul_naum, check_mul_num_1) {
  S21Matrix mat_1(1, 2);

  mat_1.setValue(1, 1, 3);
  mat_1.setValue(1, 2, 1);

  mat_1.MulNumber(5);

  EXPECT_DOUBLE_EQ(mat_1(1, 1), 15);
  EXPECT_DOUBLE_EQ(mat_1(1, 2), 5);
}

TEST(mul_matrix, check_mul_matrix_1) {
  S21Matrix mat_1(1, 2);

  mat_1.setValue(1, 1, 3);
  mat_1.setValue(1, 2, 1);

  S21Matrix mat_2(2, 1);

  mat_2.setValue(1, 1, 3);
  mat_2.setValue(2, 1, 1);

  mat_1.MulMatrix(mat_2);

  EXPECT_DOUBLE_EQ(mat_1(1, 1), 10);
}

TEST(mul_matrix, check_mul_matrix_2) {
  S21Matrix mat_1(1, 2);

  mat_1.setValue(1, 1, 3);
  mat_1.setValue(1, 2, 1);

  S21Matrix mat_2(1, 2);

  mat_2.setValue(1, 1, 3);
  mat_2.setValue(1, 2, 1);

  EXPECT_ANY_THROW(mat_1.MulMatrix(mat_2));
}

TEST(transpose_matrix, check_transpose_matrix_1) {
  S21Matrix mat_1(1, 2);

  mat_1.setValue(1, 1, 3);
  mat_1.setValue(1, 2, 1);

  S21Matrix mat_2(2, 1);

  mat_2.setValue(1, 1, 3);
  mat_2.setValue(2, 1, 1);

  S21Matrix result_matrix(mat_1.Transpose());

  bool result = mat_2.EqMatrix(result_matrix);

  EXPECT_EQ(result, SUCCESS);
}

TEST(transpose_matrix, check_transpose_matrix_2) {
  S21Matrix mat_1(2, 2);

  mat_1.setValue(1, 1, 3);
  mat_1.setValue(1, 2, 1);
  mat_1.setValue(2, 1, 2);
  mat_1.setValue(2, 2, 7);

  S21Matrix mat_2(2, 2);

  mat_2.setValue(1, 1, 3);
  mat_2.setValue(1, 2, 2);
  mat_2.setValue(2, 1, 1);
  mat_2.setValue(2, 2, 7);

  S21Matrix result_matrix(mat_1.Transpose());

  bool result = mat_2.EqMatrix(result_matrix);

  EXPECT_EQ(result, SUCCESS);
}

TEST(determinant_matrix, check_calc_complements_matrix_1) {
  S21Matrix mat_1(2, 2);

  mat_1.setValue(1, 1, 3);
  mat_1.setValue(1, 2, 1);
  mat_1.setValue(2, 1, 2);
  mat_1.setValue(2, 2, 7);

  S21Matrix mat_2(2, 2);

  mat_2.setValue(1, 1, 7);
  mat_2.setValue(1, 2, -2);
  mat_2.setValue(2, 1, -1);
  mat_2.setValue(2, 2, 3);

  S21Matrix result_matrix(mat_1.CalcComplements());

  bool result = mat_2.EqMatrix(result_matrix);

  EXPECT_EQ(result, SUCCESS);
}

TEST(determinant_matrix, check_determinant_matrix_2) {
  S21Matrix mat_1(2, 3);

  mat_1.setValue(1, 1, 2);
  mat_1.setValue(1, 2, 2);
  mat_1.setValue(1, 3, 1);

  mat_1.setValue(2, 1, 3);
  mat_1.setValue(2, 2, -2);
  mat_1.setValue(2, 3, 1);

  EXPECT_ANY_THROW(mat_1.Determinant());
}

TEST(inverse_matrix, check_inverse_matrix_1) {
  S21Matrix mat_1(2, 2);

  mat_1.setValue(1, 1, 2);
  mat_1.setValue(1, 2, 2);

  mat_1.setValue(2, 1, 3);
  mat_1.setValue(2, 2, -2);

  S21Matrix mat_2(2, 2);

  mat_2.setValue(1, 1, 0.2);
  mat_2.setValue(1, 2, 0.2);

  mat_2.setValue(2, 1, 0.3);
  mat_2.setValue(2, 2, -0.2);

  S21Matrix buf(mat_1.InverseMatrix());

  bool result = mat_2.EqMatrix(buf);

  EXPECT_EQ(result, SUCCESS);
}

TEST(inverse_matrix, check_inverse_matrix_2) {
  S21Matrix mat_1(2, 1);

  mat_1.setValue(1, 1, 2);

  mat_1.setValue(2, 1, 3);

  EXPECT_ANY_THROW(mat_1.InverseMatrix());
}

TEST(inverse_matrix, check_inverse_matrix_3) {
  S21Matrix mat_1(3, 3);

  mat_1.setValue(1, 1, 1);
  mat_1.setValue(1, 2, 2);
  mat_1.setValue(1, 3, 3);

  mat_1.setValue(2, 1, 4);
  mat_1.setValue(2, 2, 5);
  mat_1.setValue(2, 3, 6);

  mat_1.setValue(3, 1, 7);
  mat_1.setValue(3, 2, 8);
  mat_1.setValue(3, 3, 9);

  EXPECT_ANY_THROW(mat_1.InverseMatrix());
}

TEST(sum_matrix_operator, check_sum_matrix_operator_1) {
  S21Matrix mat_1(3, 3);

  mat_1.setValue(1, 1, 1);
  mat_1.setValue(1, 2, 2);
  mat_1.setValue(1, 3, 3);

  mat_1.setValue(2, 1, 4);
  mat_1.setValue(2, 2, 5);
  mat_1.setValue(2, 3, 6);

  mat_1.setValue(3, 1, 7);
  mat_1.setValue(3, 2, 8);
  mat_1.setValue(3, 3, 9);

  S21Matrix mat_2(3, 3);

  mat_2.setValue(1, 1, 1);
  mat_2.setValue(1, 2, 2);
  mat_2.setValue(1, 3, 3);

  mat_2.setValue(2, 1, 4);
  mat_2.setValue(2, 2, 5);
  mat_2.setValue(2, 3, 6);

  mat_2.setValue(3, 1, 7);
  mat_2.setValue(3, 2, 8);
  mat_2.setValue(3, 3, 9);

  S21Matrix result = mat_1 + mat_2;

  S21Matrix result_sum(3, 3);

  result_sum.setValue(1, 1, 2);
  result_sum.setValue(1, 2, 4);
  result_sum.setValue(1, 3, 6);

  result_sum.setValue(2, 1, 8);
  result_sum.setValue(2, 2, 10);
  result_sum.setValue(2, 3, 12);

  result_sum.setValue(3, 1, 14);
  result_sum.setValue(3, 2, 16);
  result_sum.setValue(3, 3, 18);

  int result_output = (int)result_sum.EqMatrix(result);

  EXPECT_EQ(result_output, SUCCESS);
}

TEST(sum_matrix_operator, check_sum_matrix_operator_2) {
  S21Matrix mat_1(2, 2);

  mat_1.setValue(1, 1, 1);
  mat_1.setValue(1, 2, 2);

  mat_1.setValue(2, 1, 4);
  mat_1.setValue(2, 2, 5);

  S21Matrix mat_2(3, 3);

  mat_2.setValue(1, 1, 1);
  mat_2.setValue(1, 2, 2);
  mat_2.setValue(1, 3, 3);

  mat_2.setValue(2, 1, 4);
  mat_2.setValue(2, 2, 5);
  mat_2.setValue(2, 3, 6);

  mat_2.setValue(3, 1, 7);
  mat_2.setValue(3, 2, 8);
  mat_2.setValue(3, 3, 9);

  EXPECT_ANY_THROW(mat_1 + mat_2);
}

TEST(sum_matrix_operator, check_sum_matrix_operator_3) {
  S21Matrix mat_1(2, 2);

  mat_1.setValue(1, 1, 1);
  mat_1.setValue(1, 2, 2);

  mat_1.setValue(2, 1, 4);
  mat_1.setValue(2, 2, 5);

  S21Matrix mat_2(2, 2);

  mat_2.setValue(1, 1, 1);
  mat_2.setValue(1, 2, 2);

  mat_2.setValue(2, 1, 4);
  mat_2.setValue(2, 2, 5);

  mat_2 += mat_1;

  S21Matrix result_sum(2, 2);

  result_sum.setValue(1, 1, 2);
  result_sum.setValue(1, 2, 4);

  result_sum.setValue(2, 1, 8);
  result_sum.setValue(2, 2, 10);

  int result_output = (int)result_sum.EqMatrix(mat_2);

  EXPECT_EQ(result_output, SUCCESS);
}

TEST(sub_matrix_operator, check_sub_matrix_operator_1) {
  S21Matrix mat_1(3, 3);

  mat_1.setValue(1, 1, 1);
  mat_1.setValue(1, 2, 2);
  mat_1.setValue(1, 3, 3);

  mat_1.setValue(2, 1, 4);
  mat_1.setValue(2, 2, 5);
  mat_1.setValue(2, 3, 6);

  mat_1.setValue(3, 1, 7);
  mat_1.setValue(3, 2, 8);
  mat_1.setValue(3, 3, 9);

  S21Matrix mat_2(3, 3);

  mat_2.setValue(1, 1, 1);
  mat_2.setValue(1, 2, 2);
  mat_2.setValue(1, 3, 3);

  mat_2.setValue(2, 1, 4);
  mat_2.setValue(2, 2, 5);
  mat_2.setValue(2, 3, 6);

  mat_2.setValue(3, 1, 7);
  mat_2.setValue(3, 2, 7);
  mat_2.setValue(3, 3, 8);

  S21Matrix result = mat_1 - mat_2;

  S21Matrix result_sum(3, 3);

  result_sum.setValue(1, 1, 0);
  result_sum.setValue(1, 2, 0);
  result_sum.setValue(1, 3, 0);

  result_sum.setValue(2, 1, 0);
  result_sum.setValue(2, 2, 0);
  result_sum.setValue(2, 3, 0);

  result_sum.setValue(3, 1, 0);
  result_sum.setValue(3, 2, 1);
  result_sum.setValue(3, 3, 1);

  int result_output = (int)result_sum.EqMatrix(result);

  EXPECT_EQ(result_output, SUCCESS);
}

TEST(sub_matrix_operator, check_sub_matrix_operator_2) {
  S21Matrix mat_1(2, 2);

  mat_1.setValue(1, 1, 1);
  mat_1.setValue(1, 2, 2);

  mat_1.setValue(2, 1, 4);
  mat_1.setValue(2, 2, 5);

  S21Matrix mat_2(3, 3);

  mat_2.setValue(1, 1, 1);
  mat_2.setValue(1, 2, 2);
  mat_2.setValue(1, 3, 3);

  mat_2.setValue(2, 1, 4);
  mat_2.setValue(2, 2, 5);
  mat_2.setValue(2, 3, 6);

  mat_2.setValue(3, 1, 7);
  mat_2.setValue(3, 2, 8);
  mat_2.setValue(3, 3, 9);

  EXPECT_ANY_THROW(mat_1 - mat_2);
}

TEST(sub_matrix_operator, check_sub_matrix_operator_3) {
  S21Matrix mat_1(2, 2);

  mat_1.setValue(1, 1, 2);
  mat_1.setValue(1, 2, -3);

  mat_1.setValue(2, 1, 10);
  mat_1.setValue(2, 2, 11);

  S21Matrix mat_2(2, 2);

  mat_2.setValue(1, 1, 1);
  mat_2.setValue(1, 2, 2);

  mat_2.setValue(2, 1, 4);
  mat_2.setValue(2, 2, 5);

  mat_2 -= mat_1;

  S21Matrix result_sum(2, 2);

  result_sum.setValue(1, 1, -1);
  result_sum.setValue(1, 2, 5);

  result_sum.setValue(2, 1, -6);
  result_sum.setValue(2, 2, -6);

  int result_output = (int)result_sum.EqMatrix(mat_2);

  EXPECT_EQ(result_output, SUCCESS);
}

TEST(mul_matrix_operator, check_mul_matrix_operator_1) {
  S21Matrix mat_1(1, 2);

  mat_1.setValue(1, 1, 1);
  mat_1.setValue(1, 2, 2);

  S21Matrix mat_2(2, 1);

  mat_2.setValue(1, 1, 1);
  mat_2.setValue(2, 1, 4);

  S21Matrix result = mat_1 * mat_2;

  S21Matrix result_sum(1, 1);

  result_sum(1, 1) = 9;

  int result_output = (int)result_sum.EqMatrix(result);

  EXPECT_EQ(result_output, SUCCESS);
}

TEST(mul_matrix_operator, check_mul_matrix_operator_2) {
  S21Matrix mat_1(2, 2);

  mat_1.setValue(1, 1, 1);
  mat_1.setValue(1, 2, 2);

  mat_1.setValue(2, 1, 4);
  mat_1.setValue(2, 2, 5);

  S21Matrix mat_2(3, 3);

  mat_2.setValue(1, 1, 1);
  mat_2.setValue(1, 2, 2);
  mat_2.setValue(1, 3, 3);

  mat_2.setValue(2, 1, 4);
  mat_2.setValue(2, 2, 5);
  mat_2.setValue(2, 3, 6);

  mat_2.setValue(3, 1, 7);
  mat_2.setValue(3, 2, 8);
  mat_2.setValue(3, 3, 9);

  EXPECT_ANY_THROW(mat_1 * mat_2);
}

TEST(mul_matrix_operator, check_mul_matrix_operator_3) {
  S21Matrix mat_1(2, 2);

  mat_1.setValue(1, 1, 2);
  mat_1.setValue(1, 2, -3);

  mat_1.setValue(2, 1, 10);
  mat_1.setValue(2, 2, 11);

  S21Matrix mat_2(2, 2);

  mat_2.setValue(1, 1, 1);
  mat_2.setValue(1, 2, 2);

  mat_2.setValue(2, 1, 4);
  mat_2.setValue(2, 2, 5);

  mat_1 *= mat_2;

  S21Matrix result_sum(2, 2);

  result_sum.setValue(1, 1, -10);
  result_sum.setValue(1, 2, -11);

  result_sum.setValue(2, 1, 54);
  result_sum.setValue(2, 2, 75);

  int result_output = (int)result_sum.EqMatrix(mat_1);

  EXPECT_EQ(result_output, SUCCESS);
}

TEST(mul_matrix_operator, check_mul_num_operator_1) {
  S21Matrix mat_1(1, 2);

  mat_1.setValue(1, 1, 1);
  mat_1.setValue(1, 2, 2);

  S21Matrix result = mat_1 * 5;

  S21Matrix result_sum(1, 2);

  result_sum.setValue(1, 1, 5);
  result_sum.setValue(1, 2, 10);

  int result_output = (int)result_sum.EqMatrix(result);

  EXPECT_EQ(result_output, SUCCESS);
}

TEST(mul_matrix_operator, check_mul_num_operator_2) {
  S21Matrix mat_1(2, 2);

  mat_1.setValue(1, 1, 2);
  mat_1.setValue(1, 2, -3);

  mat_1.setValue(2, 1, 10);
  mat_1.setValue(2, 2, 11);

  mat_1 *= 3;

  S21Matrix result_sum(2, 2);

  result_sum.setValue(1, 1, 6);
  result_sum.setValue(1, 2, -9);

  result_sum.setValue(2, 1, 30);
  result_sum.setValue(2, 2, 33);

  int result_output = (int)result_sum.EqMatrix(mat_1);

  EXPECT_EQ(result_output, SUCCESS);
}

TEST(eq_matrix_operator, check_eq_matrix_operator_1) {
  S21Matrix mat_1(1, 2);

  mat_1.setValue(1, 1, 1);
  mat_1.setValue(1, 2, 2);

  S21Matrix mat_2 = mat_1;

  int result = mat_1 == mat_2 ? SUCCESS : FAIL;

  EXPECT_EQ(result, SUCCESS);
}

TEST(eq_matrix_operator, check_eq_matrix_operator_2) {
  S21Matrix mat_1(1, 2);

  mat_1.setValue(1, 1, 1);
  mat_1.setValue(1, 2, 2);

  S21Matrix mat_2 = std::move(mat_1);
  S21Matrix mat_3(mat_2);

  int result = mat_2 == mat_3 ? SUCCESS : FAIL;

  EXPECT_EQ(result, SUCCESS);
  EXPECT_EQ(mat_1.getRow(), 0);
  EXPECT_EQ(mat_1.getCol(), 0);
}

TEST(setter_and_getter, check_col_setter_and_getter_1) {
  S21Matrix mat_1(1, 1);

  mat_1.setValue(1, 1, 1);

  mat_1.setCol(5);

  EXPECT_DOUBLE_EQ(mat_1(1, 1), 1);

  for (int i = 2; i < mat_1.getCol(); i++) {
    EXPECT_DOUBLE_EQ(mat_1(1, i), 0);
  }
}

TEST(setter_and_getter, check_col_setter_and_getter_2) {
  S21Matrix mat_1(1, 7);

  for (int i = 1; i < mat_1.getCol(); i++) {
    mat_1.setValue(1, i, 1);
  }

  mat_1.setCol(5);

  for (int i = 1; i < mat_1.getCol(); i++) {
    EXPECT_DOUBLE_EQ(mat_1(1, i), 1);
  }
}

TEST(setter_and_getter, check_row_setter_and_getter_1) {
  S21Matrix mat_1(1, 1);

  mat_1.setValue(1, 1, 1);

  mat_1.setRow(5);

  EXPECT_DOUBLE_EQ(mat_1(1, 1), 1);

  for (int i = 2; i < mat_1.getRow(); i++) {
    EXPECT_DOUBLE_EQ(mat_1(i, 1), 0);
  }
}

TEST(setter_and_getter, check_row_setter_and_getter_2) {
  S21Matrix mat_1(7, 1);

  for (int i = 1; i < mat_1.getRow(); i++) {
    mat_1.setValue(i, 1, 1);
  }

  mat_1.setRow(5);

  for (int i = 1; i < mat_1.getRow(); i++) {
    EXPECT_DOUBLE_EQ(mat_1(i, 1), 1);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}