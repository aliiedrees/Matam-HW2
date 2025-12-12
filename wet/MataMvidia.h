#pragma once

#include "Matrix.h"

using std::string;
class MataMvidia{
    string movieName;
    string creator;
    int movieLength;
    Matrix* frames;

    public:
    //Ali
    //constructor
    MataMvidia(const string& movieName, const string& creator, const Matrix* frameArr
        , const int& framesQuantity){}; 
    //operators
    MataMvidia& operator+=(const MataMvidia& movie); // += movie
    MataMvidia& operator+=(const Matrix& matrix); // += frames
    MataMvidia operator+(const MataMvidia& movie) const;
    const Matrix& operator[](const int& frame) const;

    ///Abed
    
};