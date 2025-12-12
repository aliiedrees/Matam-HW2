#pragma once

#include <iostream>

class Matrix{
    int length;
    int width;
    int* matrix;

    public:
    //Ali
    //constructors
    Matrix(const Matrix& matrix); //copy construct
    //operators
    Matrix& operator=(const Matrix& matrix); //העתקה
    bool operator==(const Matrix& matrix);
    bool operator!=(const Matrix& matrix);
    friend std::ostream &operator<<(std::ostream &os, const Matrix& matrix);
    //methods
    Matrix Transpose(); // will figure later if returns a refrence
    //static
    static int CalcDetirminant(const Matrix& matrix);

    //Abed
};