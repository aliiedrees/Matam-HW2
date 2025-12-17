#pragma once

#include "Matrix.h"
#include <fstream>
using std::string;
class MataMvidia{
    string movieName;
    string creator;
    int movieLength;
    Matrix* frames;

    public:
    //Ali
    //constructor
    ~MataMvidia();
    MataMvidia(const string& movieName, const string& creator, const Matrix* frameArr
        , const int& framesQuantity);
    //operators
    MataMvidia(const MataMvidia* copy);
    MataMvidia& operator+=(const MataMvidia& movie); // += movie
    //void operator<<(ofstream& out);
    MataMvidia& operator+=(const Matrix& matrix); // += frames
    MataMvidia operator+(const MataMvidia& movie) const;
    const Matrix& operator[](const int& frame) const;
    Matrix& operator[](const int& frame);//write
    friend std::ostream& operator<<(ostream& os, const MataMvidia& movie);
    ///Abed
    MataMvidia( const MataMvidia& mataMvidia);
    MataMvidia& operator=(const MataMvidia& mataMvidia);
};