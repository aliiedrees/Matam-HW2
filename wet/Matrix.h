#pragma once

#include <iostream>
#include <fstream>
using namespace std;
class Matrix {
    int length;
    int width;
    int* arr;

    friend Matrix MinorGenerate(const Matrix& matrix, const int& row, const int& column);
public:
    //Ali
    //constructors
    Matrix(const Matrix& matrix); //copy construct
    Matrix();

    ~Matrix() = default;
    //operators
    Matrix& operator=(const Matrix& matrix); //העתקה
   // void operator<<( ofstream& out);
    bool operator==(const Matrix& matrix);
    bool operator!=(const Matrix& matrix);
    int& operator()(const int& row, const int& column);
    Matrix operator+(const Matrix& matrix);
    Matrix operator-(const Matrix& matrix);
    Matrix& operator-();
    Matrix operator*(Matrix& matrix);
    Matrix operator*(const int& scalar);
    Matrix& operator+=(const Matrix& matrix);
    Matrix& operator-=(const Matrix& matrix);
    Matrix& operator*=( Matrix& matrix);
    Matrix& operator*=(const int& scalar);
    friend Matrix operator*(const int& scalar,Matrix& matrix);
    Matrix rotateClockwise();
    Matrix rotateCounterClockwise();
    int CalcFrobeniusNorm() const ;
    friend std::ostream &operator<<(std::ostream &os, const Matrix& matrix);
    //methods
    Matrix transpose(); // will figure later if returns a refrence
    static int CalcDeterminant(const Matrix& matrix);// will figure later if in .h or .cpp

    Matrix(const int& length, const int& wedth , const int& startValue = 0);
};