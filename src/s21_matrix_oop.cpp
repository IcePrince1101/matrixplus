#include "s21_matrix_oop.h"

// * ----------------------------
// * Class constructors and destructor
// * ----------------------------

S21Matrix::S21Matrix() {
  // * Default constructor. Set default count of rols and cols and set zeros to
  // * matrix
  // * params: none
  // * return: none
  // set default parameters
  this->rows_ = DEFAULT_SIZE;
  this->cols_ = DEFAULT_SIZE;
  // allocate memory
  this->matrix_ = new double*[this->rows_];
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_];
  }
  // set zero elements
  S21Matrix::ZeroMatrix();
}

S21Matrix::S21Matrix(int rows, int cols) {
  // * Parameterized constructor. Set count of rols and cols and set zeros to
  // * matrix
  // * params: rows : int
  // *         cols : int
  // * return: none
  // check for correct parameters
  if (rows < 1 || cols < 1)
    throw std::out_of_range("Rows and cols should be > 0");
  // set parameters
  this->rows_ = rows;
  this->cols_ = cols;
  // allocate memory
  this->matrix_ = new double*[this->rows_];
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_];
  }
  // set zero elements
  S21Matrix::ZeroMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  // * Copy constructor. Copy count of rols and cols and copy matrix elements
  // * from other matrix
  // * params: other : S21Matrix
  // * return: none
  // copy parameters (rows and cols)
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  // allocate memory for matrix
  this->matrix_ = new double*[this->rows_];
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_];
  }
  // copy matrix elements
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++)
      this->matrix_[i][j] = other.matrix_[i][j];
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  // * Move constructor. Copy count of rols and cols and copy matrix elements
  // * from other matrix, then clear other matrix
  // * params: other : S21Matrix
  // * return: none
  // copy parameters (rows and cols)
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  // allocate memory for matrix
  this->matrix_ = new double*[this->rows_];
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_];
  }
  // copy matrix elements
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++)
      this->matrix_[i][j] = other.matrix_[i][j];
  }
  // delete old matrix
  other.~S21Matrix();
}

S21Matrix::~S21Matrix() {
  // * Destructor. Clear matrix
  // * params: none
  // * return: none
  if (matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++) {
      delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
    this->matrix_ = nullptr;
    this->rows_ = 0;
    this->cols_ = 0;
  }
}

// * ----------------------------
// * base operators
// * ----------------------------

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  // * Compare two matrices. Compare rows and cols and then compare matrix
  // * elements
  // * params: other : S21Matrix
  // * return: bool
  // check for same size
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) return false;
  bool flag = true;
  // check for same matrix elements
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (this->matrix_[i][j] != other.matrix_[i][j]) flag = false;
    }
  }
  return flag;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  // * Add matrix other to this matrix. Check for same size and then add matrix
  // * elements
  // * params: other : S21Matrix
  // * return: none
  // check for same size
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::out_of_range("Matrixes should have the same size");
  // main logic
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++)
      this->matrix_[i][j] += other.matrix_[i][j];
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  // * Subtract matrix other from this matrix. Check for same size and then
  // * subtract matrix elements
  // * params: other : S21Matrix
  // * return: none
  // check for same size
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::out_of_range("Matrixes should have the same size");
  // main logic
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++)
      this->matrix_[i][j] -= other.matrix_[i][j];
  }
}

void S21Matrix::MulNumber(const double num) {
  // * Multiply matrix by number
  // * params: num : double
  // * return: none
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) this->matrix_[i][j] *= num;
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  // * Multiply matrix other to this matrix. Check for correct input
  // * params: other : S21Matrix
  // * return: none
  // check for correct input
  if (this->cols_ != other.rows_)
    throw std::out_of_range(
        "Number of column of the first matrix must be equal to the number of "
        "rows of the second matrix");
  // main login
  S21Matrix temp(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < this->cols_; k++)
        temp.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
    }
  }
  // copy result to this matrix
  this->~S21Matrix();
  *this = temp;
}

S21Matrix S21Matrix::Transpose() {
  // * Transpose matrix
  // * params: none
  // * return: S21Matrix
  // ? EXAMPLE
  // ? 2 3
  // ? 4 5  ----->  2 4 6
  // ? 6 7          3 5 7
  S21Matrix result(this->cols_, this->rows_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++)
      result.matrix_[j][i] = this->matrix_[i][j];
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  // * Calculate matrix of minors
  // * params: none
  // * return: S21Matrix
  // ? 1 2 3  | For matrix[1,1] we get minor matrix (without 1 row and 1 column)
  // ? 4 5 6  | and then calculate its determinant
  // ? 7 8 9  | and multiply it with -1 if sum of column and row % 2 == 1
  // check for square matrix
  if (this->rows_ != this->cols_)
    throw std::out_of_range("The matrix is not square");
  // main logic
  S21Matrix result(this->rows_, this->cols_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++)
      result.matrix_[i][j] = (((i + j) << 31) >> 31 == 0 ? 1 : -1) *
                             this->MinorMatrix(i, j).Determinant();
  }
  return result;
}

double S21Matrix::Determinant() {
  // * Calculate matrix determinant. for matrix 1x1 we return simple velue of
  // * matrix
  // * for matrix 2x2 we return substract between main and secondary diagonals
  // * for matrix 3x3 we use recursion with minor matrix
  // * params: none
  // * return: double
  // check for square matrix
  if (this->rows_ != this->cols_)
    throw std::out_of_range("The matrix is not square");
  // main logic
  double result = 0;
  if (this->rows_ == 1)
    result = this->matrix_[0][0];
  else if (this->rows_ == 2)
    result = this->matrix_[0][0] * this->matrix_[1][1] -
             this->matrix_[0][1] * this->matrix_[1][0];
  else {
    for (int j = 0; j < this->cols_; j++)
      result += ((j << 31) >> 31 == 0 ? 1 : -1) *
                this->MinorMatrix(0, j).Determinant() * this->matrix_[0][j];
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  // * Inverse matrix. Check for square matrix and determinant != 0
  // * params: none
  // * return: S21Matrix
  // check for square matrix
  if (this->rows_ != this->cols_)
    throw std::out_of_range("The matrix is not square");
  // check for determinant != 0
  if (this->Determinant() == 0)
    throw std::out_of_range("The matrix is not invertible");
  // main logic
  S21Matrix result = this->CalcComplements().Transpose();
  result.MulNumber(1 / this->Determinant());
  return result;
}

// * ----------------------------
// * other methods
// * ----------------------------

S21Matrix S21Matrix::MinorMatrix(int row, int col) {
  // * get minor matrix
  // * params: int row, int col
  // * return: S21Matrix
  // ? EXAMPLE MinorMatrix(1,1)
  // ? 1 2 3
  // ? 4 5 6 -----> 5 6
  // ? 7 8 9        8 9
  if (this->rows_ == 1 && this->cols_ == 1) return *this;
  S21Matrix result(this->rows_ - 1, this->cols_ - 1);
  int rows = 0;
  for (int i = 0; i < this->rows_; i++) {
    int cols = 0;
    if (i != row) {
      for (int j = 0; j < this->cols_; j++)
        if (j != col) result.matrix_[rows][cols++] = this->matrix_[i][j];
      rows++;
    }
  }
  return result;
}

void S21Matrix::ZeroMatrix() {
  // * Set values of matrix to zero
  // * params: none
  // * return: none
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) this->matrix_[i][j] = 0;
  }
}

void S21Matrix::Print() {
  // * print matrix
  // * params: none
  // * return: none
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++)
      std::cout << this->matrix_[i][j] << " ";
    std::cout << std::endl;
  }
}

// * ----------------------------
// * accesors and mutators
// * ----------------------------

void S21Matrix::SetRows(int rows) {
  // * Set or update number of rows. Check for rows > 0
  // * params: int rows
  // * return: none
  if (rows < 1) throw std::out_of_range("Rows should be > 0");
  S21Matrix temp(rows, this->cols_);
  for (int i = 0; i < (this->rows_ < rows ? this->rows_ : rows); i++)
    std::copy(this->matrix_[i], this->matrix_[i] + this->cols_,
              temp.matrix_[i]);
  this->~S21Matrix();
  *this = std::move(temp);
}

void S21Matrix::SetCols(int cols) {
  // * Set or update number of cols. Check for cols > 0
  // * params: int cols
  // * return: none
  if (cols < 1) throw std::out_of_range("Cols should be > 0");
  S21Matrix temp(this->rows_, cols);
  for (int i = 0; i < (this->cols_ < cols ? this->cols_ : cols); i++)
    std::copy(this->matrix_[i],
              this->matrix_[i] + (this->cols_ < cols ? this->cols_ : cols),
              temp.matrix_[i]);
  this->~S21Matrix();
  *this = std::move(temp);
}

int S21Matrix::GetRows() { return this->rows_; }

int S21Matrix::GetCols() { return this->cols_; }

// * ----------------------------
// * operators overload
// * ----------------------------

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  // check for old memory and delete it if necessary
  if (this->matrix_ != nullptr) this->~S21Matrix();
  this->matrix_ = new double*[this->rows_];
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_];
    std::copy(other.matrix_[i], other.matrix_[i] + this->cols_,
              this->matrix_[i]);
  }
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i >= this->rows_ || j >= this->cols_)
    throw std::out_of_range("Index out of range");
  return this->matrix_[i][j];
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}