#include "Matrix.h"
using std::endl;

Matrix::Matrix(const Matrix& matrix){
    const int size = matrix.length * matrix.width; 
    this->length = matrix.length;
    this->width = matrix.width;
    this->arr = new int[size];
    for(int i = 0; i < size; i++){
        *(this->arr + i) = *(matrix.arr + i);
    }
}

Matrix& Matrix::operator=(const Matrix& matrix){ //will deal with if new fails later
    if(this == &matrix){
        return *this;
    }
    const int size = matrix.length * matrix.width; 
    this->length = matrix.length;
    this->width = matrix.width;
    delete[] this->arr;
    this->arr = new int[size];
    for(int i = 0; i < size; i++){
        *(this->arr + i) = *(matrix.arr + i);
    }
    return *this;
}

bool Matrix::operator==(const Matrix& matrix){
    if (this->length != matrix.length || this->width != matrix.width){
        return false;
    }
    const int size = length * width;
    for(int i = 0; i < size; i++){
        if (*(this->arr + i) != *(matrix.arr + i)){
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& matrix){
    return !(*this == matrix);
}

std::ostream &operator<<(std::ostream &os, const Matrix& matrix){
    int currentRow = 0, currentColumn = 0;
    while(currentRow < matrix.length){
        os << "|";
        while(currentColumn < matrix.width){
            os << matrix.arr[currentRow*matrix.width + currentColumn] << "|";
            currentColumn++;
        }
        currentColumn = 0;
        currentRow++;
        os << endl;
    }
}

Matrix Matrix::Transpose(){
    
}
