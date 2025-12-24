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

    ~Matrix();
    //operators
    Matrix& operator=(const Matrix& matrix); //העתקה
   // void operator<<( ofstream& out);
    bool operator==(const Matrix& matrix) const;
    bool operator!=(const Matrix& matrix) const;
    int& operator()(const int& row, const int& column);
    const int& operator()(const int& row, const int& column) const;
    Matrix operator+(const Matrix& matrix) const;
    Matrix operator-(const Matrix& matrix) const;
    Matrix operator-() const;
    Matrix operator*( const Matrix& matrix) const;
    Matrix operator*(const int& scalar) const;
    Matrix& operator+=(const Matrix& matrix);
    Matrix& operator-=(const Matrix& matrix);
    Matrix& operator*=( Matrix& matrix);
    Matrix& operator*=(const int& scalar);
    friend Matrix operator*(const int& scalar,const Matrix& matrix);
    Matrix rotateClockwise() const;
    Matrix rotateCounterClockwise() const;
    int CalcFrobeniusNorm() const ;
    friend std::ostream &operator<<(std::ostream &os, const Matrix& matrix);
    //methods
    Matrix transpose() const; // will figure later if returns a refrence
<<<<<<< HEAD
    static double CalcDeterminant(const Matrix& matrix);// will figure later if in .h or .cpp
=======
    static int CalcDeterminant(const Matrix& matrix);// will figure later if in .h or .cpp
>>>>>>> submit

    Matrix(const int& length, const int& wedth , const int& startValue = 0);
};