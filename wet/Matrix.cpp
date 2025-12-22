#include "Matrix.h"
#include "Utilities.h"
#include <cmath>

using std::endl;
Matrix::~Matrix(){
    delete[] this->arr;
}
Matrix::Matrix(): length(0), width(0), arr(nullptr){}
Matrix::Matrix(const Matrix& matrix){
    const int size = matrix.length * matrix.width; 
    this->length = matrix.length;
    this->width = matrix.width;
    this->arr = new int[size];
    for(int i = 0; i < size; i++){
        *(this->arr + i) = *(matrix.arr + i);
    }
}
Matrix::Matrix(const int& length, const int& width , const int& startValue) : length(length), width(width), arr(nullptr){
    int arrLen = length * width;
    this->arr = new int[arrLen];
    for (int i = 0; i < arrLen; i++) {
        this->arr[i] = startValue;
    }
};
Matrix& Matrix::operator=(const Matrix& matrix){ 
    if (this == &matrix) return *this;
    length = matrix.length;
    width = matrix.width;
    if(arr != nullptr){
        delete[] arr;
    }
    this->arr = new int[this->length * this->width];
    for (int i = 0; i < length * width; i++)
        arr[i] = matrix.arr[i];
    return *this;
}


int& Matrix::operator()(const int& row, const int& column) {
    if(row >= this->length || column >= this->width || column < 0 || row < 0) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    int place = (row)*(this->width)+column;
    return *(this->arr + place);
}
const int& Matrix::operator()(const int& row, const int& column) const{
    if(row >= this->length || column >= this->width || column < 0 || row < 0) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    int place = (row)*(this->width)+column;
    return *(this->arr + place);
}
Matrix Matrix::operator+(const Matrix& matrix) const{
    if(this->length != matrix.length || this->width != matrix.width) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    Matrix result(this->length, this->width);
    for(int i = 0; i < this->length*this->width; i++) {
        result.arr[i] = (this->arr)[i] + (matrix.arr)[i];
    }
    return result;
}
Matrix Matrix::operator-(const Matrix& matrix) const{
    if(this->length != matrix.length || this->width != matrix.width) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    Matrix result(this->length, this->width);
    for(int i = 0; i < this->length*this->width; i++) {
        result.arr[i] = (this->arr)[i] -  *(matrix.arr + i);
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& matrix) const {
    if(this->width != matrix.length) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    Matrix result(this->length, matrix.width);
    for(int i = 0; i < result.length; i++) {
        for(int j = 0; j < result.width; j++) {
            int currentSum = 0;
            for (int k = 0; k < this->width; k++) {
                // Dot product: Row i of First * Col j of Second
                currentSum += (*this)(i, k) * matrix(k, j);
            }
            
            result(i, j) = currentSum;
        }
    }
    return result;
}
Matrix& Matrix::operator+=(const Matrix& matrix) {
    *this = *this + matrix;
    return *this;
}
Matrix& Matrix::operator-=(const Matrix& matrix) {
    *this = *this - matrix;
    return *this;
}
Matrix Matrix::operator-() const{
    Matrix m2 = *this;
    int size = this->width * this->length;
    for(int i = 0; i < size; i++) {
        m2.arr[i] *= -1;
    }
    return m2;
}
Matrix& Matrix::operator*=( Matrix& matrix) {
    *this = *this * matrix;
    return *this;
}
Matrix Matrix::operator*(const int& scalar) const{
    Matrix m2 = *this;
    int size = this->width * this->length;
    for(int i = 0; i < size; i++) {
        m2.arr[i] *= scalar;
    }
    return m2;
}
Matrix& Matrix::operator*=(const int& scalar) {
    *this = *this * scalar;
    return *this;
}

Matrix operator*(const int& scalar,const Matrix& matrix) { // make const
    Matrix m2 = matrix;
    int size = matrix.width * matrix.length;
    for(int i = 0; i < size; i++) {
        m2.arr[i] *= scalar;
    }
    return m2;
}
bool Matrix::operator==(const Matrix& matrix) const{
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

bool Matrix::operator!=(const Matrix& matrix) const{
    return !(*this == matrix);
}

std::ostream &operator<<(std::ostream &os, const Matrix& matrix){
    int currentRow = 0, currentColumn = 0;
    if(matrix.length == 0 || matrix.width == 0){
        return os;
    }
    while(currentRow < matrix.length){
        while(currentColumn < matrix.width){
            os << "|" << matrix.arr[currentRow*matrix.width + currentColumn];
            currentColumn++;
        }
        os << "|" << endl;
        currentColumn = 0;
        currentRow++;
    }
    return os;
}

Matrix Matrix::transpose() const{ //later check to return refernce
    Matrix transposed(this->width, this->length) ;
    int currentColumn = 0, currentRow = 0;

    //fill the transposed
    while (currentRow < transposed.length){
        while (currentColumn < transposed.width){
            *(transposed.arr + currentRow*transposed.width + currentColumn) = 
            *(this->arr + currentColumn*transposed.length + currentRow);
            currentColumn++;
        }
        currentColumn = 0;
        currentRow++;
    }
    return transposed;
}

//helper to create a minor
//gets the matrice and the row and column not to include
Matrix MinorGenerate(const Matrix& matrix, const int& row, const int& column){
    Matrix minor(matrix.length - 1, matrix.width - 1);
    int currentRow = 0, currentColumn = 0;
    int skipedRow = 0;
    while (currentRow <  matrix.length){
        if(currentRow == row){
            skipedRow++;
        } else {
            int skipedColumn = 0;
            while (currentColumn < matrix.width){
                if (currentColumn == column){
                    skipedColumn++;
                } else {
                    minor.arr[(currentRow - skipedRow)*minor.width + currentColumn - skipedColumn] 
                    = matrix.arr[currentRow*matrix.width + currentColumn];
                }
                currentColumn++;
            }
            currentColumn = 0;
        }
        currentRow++;
    }
    return minor;
}

double Matrix::CalcDeterminant(const Matrix& matrix){
    if (matrix.length != matrix.width || matrix.length == 0){
        exitWithError(MatamErrorType::NotSquareMatrix);
    }
    if(matrix.length == 1){
        return matrix.arr[0];
    }
    if (matrix.length == 2){
        return matrix.arr[0]*matrix.arr[3] - matrix.arr[1]*matrix.arr[2];
    }
    int det = 0;
    //i will be calculating the detriminat on the first row so the i represents the columns
    for(int i = 0; i < matrix.width; i++){
        int sign = (i % 2 == 0 ? 1 : -1);
        det += sign * matrix.arr[i] * CalcDeterminant(MinorGenerate(matrix, 0, i));
    }
    return det;
}
Matrix Matrix::rotateClockwise() const {
    int newWidth = this->length;
    int newLength = this->width;
    Matrix rotated(newLength, newWidth);
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < length; j++) {
            rotated(i,newWidth - j - 1) = (*this)(j,i);
        }
    }
    return rotated;
}
Matrix Matrix::rotateCounterClockwise() const {
    int newWidth = this->length;
    int newLength = this->width;
    Matrix rotated(newLength, newWidth);
    for(int i = 0; i < newWidth; i++) {
        for(int j = 0; j < newLength; j++) {
            rotated(newLength - j  - 1, i) = (*this)(i,j);
        }
    }
    return rotated;
}
int Matrix::CalcFrobeniusNorm() const {
int sum = 0;
    int size = this->length *this-> width;
    for(int i = 0; i < size; i++) {
        sum += this->arr[i] * this->arr[i];
    }
    return sqrt(sum);
}