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