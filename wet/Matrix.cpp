#include "Matrix.h"
#include "Utilities.h"

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
Matrix::Matrix(const int& length, const int& width , const int& startValue) : length(length), width(width){
    int arrLen = length * width;
   arr = new int[arrLen];
    for (int i = 0; i < arrLen; i++) {
        arr[i] = startValue;
    }
};
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
void Matrix::operator<<(ofstream& out) {
    for(int i = 0 ; i < this->length ; i++) {
        out << "|";
        for (int j = 0; j < this->width ; j++ ) {
            out << *(this->arr + i * this->width + j) << "|";
        }
        out << endl;
    }
}
int& Matrix::operator()(const int& wedth, const int& length) {
if(length > this->length || wedth > this->width || wedth < 0 || length < 0) {
    exitWithError(MatamErrorType::OutOfBounds);
}
int place = wedth*(this->width)+length;
    int& value = *(this->arr + place);
    return value;
}
Matrix& Matrix::operator+(const Matrix& matrix) {
    if(this->length != matrix.length || this->width != matrix.width) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    for(int i = 0; i < this->length*this->width; i++) {
        arr[i] += *(matrix.arr + i);
    }
    return *this;
}
Matrix& Matrix::operator-(const Matrix& matrix) {
    if(this->length != matrix.length || this->width != matrix.width) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    for(int i = 0; i < this->length*this->width; i++) {
        arr[i] -= *(matrix.arr + i);
    }
    return *this;
}
int multipyRowColumn( Matrix& a, Matrix& b, const int& row, const int& column , const int& length) {
    int result = 0;
    for(int i = 0; i < length; i++) {
        result += a(row*length,i)*b(column,length*i);
    }
    return result;
}
Matrix& Matrix::operator*( Matrix& matrix) {
    if(this->width != matrix.length || this->length != matrix.width) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    Matrix result(this->length, matrix.width);
    int curr;
    for(int i = 0; i < result.length; i++) {
        for(int j = 0; j < result.width; j++) {
           int curr = multipyRowColumn(*this, matrix,i,j,this->width);
            result(i,j) = curr;
        }
    }
    return result;
}
Matrix& Matrix::operator+=(const Matrix& matrix) {
    return *this + matrix;
}
Matrix& Matrix::operator-=(const Matrix& matrix) {
    return *this - matrix;
}
Matrix& Matrix::operator-() {
    int size = this->width * this->length;
    for(int i = 0; i < size; i++) {
        arr[i] *= -1;
    }
    return *this;
}
Matrix& Matrix::operator*=( Matrix& matrix) {
    return *this * matrix;
}
Matrix& Matrix::operator*(const int& scalar){
    int size = this->width * this->length;
    for(int i = 0; i < size; i++) {
        arr[i] *= scalar;
    }
    return *this;
}
Matrix& Matrix::operator*=(const int& scalar) {
    return *this * scalar;
}
Matrix& operator*(const int& scalar,Matrix& matrix) {
    return matrix * scalar;
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
    return os;
}

Matrix Matrix::Transpose(){ //later check to return refernce
    Matrix transposed;
    const int size = length * width;
    transposed.width = this->length;
    transposed.length = this->width;
    transposed.arr = new int[size];
    int currentColumn = 0, currentRow = 0;

    //fill the transposed
    while (currentRow < transposed.length){
        while (currentColumn < transposed.width){
            *(transposed.arr + currentRow*transposed.length + currentColumn) = 
            *(this->arr + currentColumn*transposed.width + currentRow);
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

int Matrix::CalcDetirminant(const Matrix& matrix){
    if (matrix.length != matrix.width){
        exitWithError(MatamErrorType::NotSquareMatrix);
    }
    if (matrix.length == matrix.width == 2){
        return matrix.arr[0]*matrix.arr[3] - matrix.arr[1]*matrix.arr[2];
    }
    int det = 0;
    //i will be calculating the detriminat on the first row so the i represents the columns
    for(int i = 0; i < matrix.width; i++){
        det += (-1)^i * CalcDetirminant(MinorGenerate(matrix, 0, i));
    }
    return det;
}
Matrix& Matrix::rotateClockwise() {
    int newWidth = this->length;
    int newLength = this->width;
    Matrix rotated(newWidth, newLength);
    for(int i = 0; i < newWidth; i++) {
    for(int j = 0; j < newLength; j++) {
        rotated.arr[newWidth - i + j*newWidth -1] = this->arr[j*newLength + i];
    }
    }
    return rotated;
}
Matrix& Matrix::rotateCounterClockwise() {
    int newWidth = this->length;
    int newLength = this->width;
    Matrix rotated(newWidth, newLength);
    for(int i = 0; i < newWidth; i++) {
        for(int j = 0; j < newLength; j++) {
            rotated.arr[j + i*newLength ] = this->arr[newWidth - i + j*newLength -1];
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