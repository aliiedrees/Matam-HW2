#include "MataMvidia.h"
#include "Matrix.h"

MataMvidia::MataMvidia(const string& movieName, const string& creator, const Matrix* frameArr
    , const int& framesQuantity)
    : movieName(movieName), creator(creator) ,movieLength(framesQuantity){
        this->frames = new Matrix[framesQuantity];
        for(int i = 0; i < framesQuantity; i++){
            (this->frames)[i] = frameArr[i];
        }
}

MataMvidia& MataMvidia::operator+=(const MataMvidia& movie){
    int newSize = this->movieLength + movie.movieLength;
    Matrix* newFrames = new Matrix[newSize];
    for(int i = 0; i < this->movieLength; i++){
        newFrames[i] = (this->frames)[i];
    }
    for(int j = 0; j < movie.movieLength; j++){
        newFrames[this->movieLength + j] = movie.frames[j];
    }
    delete[] this->frames;
    this->frames = newFrames;
    return *this;
}

MataMvidia& MataMvidia::operator+=(const Matrix& matrix){
    int newSize = this->movieLength + 1;
    Matrix* newFrames = new Matrix[newSize];
    for(int i = 0; i < this->movieLength; i++){
        newFrames[i] = (this->frames)[i];
    }
    newFrames[this->movieLength] = matrix;
    delete[] this->frames;
    this->frames = newFrames;
    return *this;
}

MataMvidia MataMvidia::operator+(const MataMvidia& movie) const {
    MataMvidia newMovie(this->movieName, this->creator, this->frames, this->movieLength);
    newMovie += movie;
    return newMovie;
}