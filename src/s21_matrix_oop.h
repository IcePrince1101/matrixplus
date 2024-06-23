#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <iostream>

#include <math.h>


#define DEFAULT_SIZE 3;

class S21Matrix
{
private:
    // * rows and columns attributes
    int rows_, cols_;
    // * pointer to the memory where the matrix will be allocated
    double** matrix_;
public:
    // * rules five
    S21Matrix(); // base constructor
    S21Matrix(int rows, int cols); // parameterized constructor
    S21Matrix(const S21Matrix& other); // copy constructor
    S21Matrix(S21Matrix&& other); // move constructor
    ~S21Matrix(); // destructor

    // * operations
    bool EqMatrix(const S21Matrix& other);
    void SumMatrix(const S21Matrix& other);
    void SubMatrix(const S21Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix& other);
    S21Matrix Transpose();
    S21Matrix CalcComplements();
    double Determinant();
    S21Matrix InverseMatrix();

    // * other methods
    S21Matrix MinorMatrix(int row, int col);
    void ZeroMatrix();
    void Print();

    //  * accessors and mutators
    void SetRows(int rows);
    void SetCols(int cols);
    int GetRows();
    int GetCols();

    // * operators overload
    S21Matrix& operator=(const S21Matrix& other);
    double& operator()(int i, int j);
    // +
    S21Matrix operator+(const S21Matrix& other);
    S21Matrix& operator+=(const S21Matrix& other);
    // -
    S21Matrix operator-(const S21Matrix& other);
    S21Matrix& operator-=(const S21Matrix& other);
    // *
    S21Matrix operator*(const S21Matrix& other);
    S21Matrix& operator *=(const S21Matrix& other);
    S21Matrix operator*(const double num);
    S21Matrix& operator*=(const double num);
    // equal
    bool operator==(const S21Matrix& other);
};

#endif