#ifndef S21_CPP_MATRIX_PLUS_S21_MATRIX_OOP_H
#define S21_CPP_MATRIX_PLUS_S21_MATRIX_OOP_H

#include <math.h>

#include <exception>

class S21Matrix {
 public:
  S21Matrix() noexcept;
  S21Matrix(int row, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix() noexcept;
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  S21Matrix operator+(const S21Matrix &arg_2) const;
  S21Matrix operator-(const S21Matrix &arg_2) const;
  S21Matrix operator*(const S21Matrix &arg_2) const;
  S21Matrix operator*(const double num) const;
  bool operator==(const S21Matrix &arg_2) const;
  S21Matrix &operator=(const S21Matrix &arg_2) noexcept;
  S21Matrix &operator=(S21Matrix &&arg_2) noexcept;
  S21Matrix &operator+=(const S21Matrix &arg_2);
  S21Matrix &operator-=(const S21Matrix &arg_2);

  S21Matrix &operator*=(const S21Matrix &arg_2);
  S21Matrix &operator*=(const double num);

  double &operator()(const int row, const int col);

  void setRow(const int rows);
  void setCol(const int cols);
  void setValue(const int rows, const int cols, double num);
  double getRow();
  double getCol();

 private:
  enum { kFAIL, kSUCCESS };
  int rows_, cols_;
  double **matrix_;

  bool CheckMatrixForEqRowsCols_(S21Matrix arg) const;
  double Minor_(S21Matrix &tmp, int row, int column);
  void EqualizeMatrix_(S21Matrix other);
  void ClearMatrix_();
};

#endif