#include "MataMvidia.h"
#include "Matrix.h"
#include "Utilities.h"
MataMvidia::~MataMvidia(){
    delete[] this->frames;
}
MataMvidia::MataMvidia(const string& movieName, const string& creator, const Matrix* frameArr
        , const int& framesQuantity)
    : movieName(movieName), creator(creator) ,movieLength(framesQuantity), frames(nullptr){
        this->frames = new Matrix[framesQuantity];
        for(int i = 0; i < framesQuantity; i++){
            (this->frames)[i] = frameArr[i];
        }
}
MataMvidia::MataMvidia( const MataMvidia& mataMvidia)
: movieName(mataMvidia.movieName), creator(mataMvidia.creator) ,movieLength(mataMvidia.movieLength),
frames(nullptr)
{
    this->frames = new Matrix[movieLength];
    for(int i = 0; i < mataMvidia.movieLength; i++) {
        frames[i] = mataMvidia.frames[i];
    }
}
std::ostream& operator<<(ostream& os, const MataMvidia& movie){
    os << "Movie Name: "<< movie.movieName << endl;
    os <<"Author: " << movie.creator << endl ;
    os << "" << endl;
    for(int i = 0; i < movie.movieLength; i++) {
        os << "Frame " << i << ":" << endl;
        os << movie.frames[i] << endl;
    }
    os << "-----End of Movie-----" << endl;
    return os;
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
    this->movieLength = newSize;
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
    this->movieLength = newSize;
    return *this;
}

MataMvidia MataMvidia::operator+(const MataMvidia& movie) const {
    MataMvidia newMovie(this->movieName, this->creator, this->frames, this->movieLength);
    newMovie += movie;
    return newMovie;
}

const Matrix& MataMvidia::operator[](const int& frame) const{
    if(frame < 0 || frame >= this->movieLength){
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return this->frames[frame];
}

Matrix& MataMvidia::operator[](const int& frame){
    if(frame < 0 || frame >= this->movieLength){
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return this->frames[frame];
}

MataMvidia& MataMvidia::operator=(const MataMvidia& mataMvidia){
    if(this == &mataMvidia) return *this;
    this->creator = mataMvidia.creator;
    this->movieLength = mataMvidia.movieLength;
    this->movieName = mataMvidia.movieName;
    if(this->frames != nullptr){
        delete[] frames;
    }
    frames = new Matrix[mataMvidia.movieLength];
    for(int i=0; i < mataMvidia.movieLength; i++){
        frames[i] = mataMvidia.frames[i];
    }
    return *this;
}