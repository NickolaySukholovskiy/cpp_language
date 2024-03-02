#include "s21_matrix_oop.h"

#include <stdio.h>

#include <iostream>

S21Matrix::S21Matrix() noexcept {
  this->rows_ = 1;
  this->cols_ = 1;
  this->matrix_ = new double *[this->rows_];
  this->matrix_[0] = new double[this->cols_];
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Incorrect number of rows or cols");
  }

  this->matrix_ = new double *[this->rows_];
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_];
  }
}

S21Matrix::~S21Matrix() noexcept { this->ClearMatrix_(); }

void S21Matrix::ClearMatrix_() {
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++) {
      delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
    this->matrix_ = nullptr;
    this->cols_ = 0;
    this->rows_ = 0;
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  this->matrix_ = nullptr;

  if (other.matrix_ != nullptr) {
    this->matrix_ = new double *[this->rows_];
    for (int i = 0; i < this->rows_; i++) {
      this->matrix_[i] = new double[this->cols_];
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.cols_ = 0;
  other.rows_ = 0;
  other.matrix_ = nullptr;
}

bool S21Matrix::CheckMatrixForEqRowsCols_(S21Matrix arg) const {
  bool output_result = kFAIL;
  if (this->rows_ == arg.rows_) {
    if (this->cols_ == arg.cols_) {
      if (this->matrix_ != nullptr && arg.matrix_ != nullptr) {
        output_result = kSUCCESS;
      }
    }
  }

  return output_result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (this->CheckMatrixForEqRowsCols_(other) == kFAIL) {
    throw std::invalid_argument("Different matrix dimensions");
  }

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (this->CheckMatrixForEqRowsCols_(other) == kFAIL) {
    throw std::invalid_argument("Different matrix dimensions");
  }

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool output_result = CheckMatrixForEqRowsCols_(other);
  if (this->matrix_ == nullptr && other.matrix_ == nullptr) {
    output_result = kSUCCESS;
  }

  if (output_result == kSUCCESS) {
    for (int i = 0; i < this->rows_ && output_result; i++) {
      for (int j = 0; j < this->cols_ && output_result; j++) {
        if (std::abs(this->matrix_[i][j] - other.matrix_[i][j]) > 1e-15) {
          output_result = kFAIL;
        }
      }
    }
  }

  return output_result;
}

void S21Matrix::MulNumber(const double num) {
  if (this->matrix_ == nullptr) {
    throw std::invalid_argument("Incorrect matrix");
  }

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->cols_ != other.rows_) {
    throw std::invalid_argument("Incorrect number of matrix cols and rows");
  } else if (this->matrix_ == nullptr) {
    throw std::invalid_argument("Incorrect matrix");
  }

  int buf_rows = this->rows_;
  int buf_cols = other.cols_;

  S21Matrix buf(buf_rows, buf_cols);

  for (int i = 0; i < buf.rows_; i++) {
    for (int j = 0; j < buf.cols_; j++) {
      buf.matrix_[i][j] = 0;
      for (int k = 0; k < this->cols_; k++) {
        buf.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  this->ClearMatrix_();
  *this = std::move(buf);
}

S21Matrix S21Matrix::Transpose() {
  if (this->matrix_ == nullptr) {
    throw std::invalid_argument("Incorrect matrix");
  }

  S21Matrix result_matrix(this->cols_, this->rows_);

  {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        result_matrix.matrix_[j][i] = this->matrix_[i][j];
      }
    }
  }

  return result_matrix;
}

double S21Matrix::Minor_(S21Matrix &tmp, int row, int column) {
  double result = 0;
  int s = 0, st = 0;

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (i != row && j != column) {
        tmp.matrix_[s][st] = this->matrix_[i][j];
        st++;
      }
    }
    if (st == this->rows_ - 1) {
      s++;
      st = 0;
    }
  }

  result = tmp.Determinant();

  return result;
}

double S21Matrix::Determinant() {
  if (this->rows_ != this->cols_) {
    throw std::invalid_argument("Matrix is not square");
  } else if (this->matrix_ == nullptr) {
    throw std::invalid_argument("Incorrext matrix");
  }

  double result = 0;
  if (this->rows_ == 1) {
    result = this->matrix_[0][0];
  } else if (this->rows_ == 2) {
    result = this->matrix_[0][0] * this->matrix_[1][1] -
             this->matrix_[0][1] * this->matrix_[1][0];
  } else {
    S21Matrix tmp(this->rows_ - 1, this->cols_ - 1);
    for (int i = 0; i < this->cols_; i++) {
      result += pow(-1, i) * this->matrix_[0][i] * Minor_(tmp, 0, i);
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (this->rows_ != this->cols_) {
    throw std::invalid_argument("Matrix is not square");
  } else if (this->matrix_ == nullptr) {
    throw std::invalid_argument("Incorrect matrix");
  }

  S21Matrix result_matrix(this->rows_, this->cols_);

  if (this->rows_ == 1) {
    result_matrix.matrix_[0][0] = this->matrix_[0][0];
  } else {
    S21Matrix tmp(this->rows_ - 1, this->cols_ - 1);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        result_matrix.matrix_[i][j] = pow(-1, i + j) * Minor_(tmp, i, j);
      }
    }
  }

  return result_matrix;
}

S21Matrix S21Matrix::InverseMatrix() {
  double divider = 0;

  if (this->rows_ != this->cols_) {
    throw std::invalid_argument("Matrix is not square");
  } else if (this->matrix_ == nullptr) {
    throw std::invalid_argument("Incorrect matrix");
  } else if ((divider = this->Determinant()) == 0) {
    throw std::invalid_argument("Determint is zero");
  }

  S21Matrix result_matrix;
  S21Matrix tmp(this->CalcComplements());
  result_matrix.EqualizeMatrix_(tmp.Transpose());
  result_matrix.MulNumber(1 / divider);

  return result_matrix;
}

void S21Matrix::EqualizeMatrix_(S21Matrix other) {
  this->ClearMatrix_();
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;

  if (other.matrix_ != nullptr) {
    this->matrix_ = new double *[this->rows_];
    for (int i = 0; i < this->rows_; i++) {
      this->matrix_[i] = new double[this->cols_];
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix &arg_2) const {
  S21Matrix result_matrix(*this);
  result_matrix.SumMatrix(arg_2);

  return result_matrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix &arg_2) const {
  S21Matrix result_matrix(*this);
  result_matrix.SubMatrix(arg_2);

  return result_matrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix &arg_2) const {
  S21Matrix result_matrix(*this);
  result_matrix.MulMatrix(arg_2);

  return result_matrix;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result_matrix(*this);
  result_matrix.MulNumber(num);

  return result_matrix;
}

bool S21Matrix::operator==(const S21Matrix &arg_2) const {
  S21Matrix result_matrix(*this);
  bool result = result_matrix.EqMatrix(arg_2);

  return result;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &arg_2) noexcept {
  if (*this == arg_2) {
    return *this;
  }

  this->ClearMatrix_();
  S21Matrix buf(arg_2);

  *this = buf;

  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&arg_2) noexcept {
  if (*this == arg_2) {
    return *this;
  }

  this->ClearMatrix_();

  std::swap(this->rows_, arg_2.rows_);
  std::swap(this->cols_, arg_2.cols_);
  std::swap(this->matrix_, arg_2.matrix_);

  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &arg_2) {
  this->SumMatrix(arg_2);

  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &arg_2) {
  this->SubMatrix(arg_2);

  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &arg_2) {
  this->MulMatrix(arg_2);

  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  this->MulNumber(num);

  return *this;
}

double &S21Matrix::operator()(const int row, const int col) {
  if (row > this->rows_ || row < 1) {
    throw std::invalid_argument("Incorrect indexes");
  }
  if (col > this->cols_ || col < 1) {
    throw std::invalid_argument("Incorrect indexes");
  }
  return this->matrix_[row - 1][col - 1];
}

void S21Matrix::setRow(const int rows) {
  if (rows < 1) {
    throw std::invalid_argument("Incorrect rows");
  }

  if (this->rows_ != rows) {
    S21Matrix buf(rows, this->cols_);
    for (int i = 0; i < buf.rows_; i++) {
      for (int j = 0; j < buf.cols_; j++) {
        if (i < this->rows_) {
          buf.matrix_[i][j] = this->matrix_[i][j];
        } else {
          buf.matrix_[i][j] = 0;
        }
      }
    }

    this->ClearMatrix_();
    *this = std::move(buf);
  }
}

void S21Matrix::setCol(const int cols) {
  if (cols < 1) {
    throw std::invalid_argument("Incorrect cols");
  }

  if (this->cols_ != cols) {
    S21Matrix buf(this->rows_, cols);
    for (int i = 0; i < buf.rows_; i++) {
      for (int j = 0; j < buf.cols_; j++) {
        if (j < this->cols_) {
          buf.matrix_[i][j] = this->matrix_[i][j];
        } else {
          buf.matrix_[i][j] = 0;
        }
      }
    }

    this->ClearMatrix_();
    *this = std::move(buf);
  }
}

void S21Matrix::setValue(const int rows, const int cols, double num) {
  if (cols < 1 || rows < 1) {
    if (cols > this->cols_ || rows > this->rows_) {
      throw std::invalid_argument("Incorrect row or col");
    }
  }

  this->matrix_[rows - 1][cols - 1] = num;
}

double S21Matrix::getCol() { return this->cols_; }

double S21Matrix::getRow() { return this->rows_; }
