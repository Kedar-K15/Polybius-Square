#ifndef EXCEPTION_H
#define EXCEPTION_H

/**
    Polybius-Square: A program that encrypts or decrypts strings using the Polybius Square
    Copyright (C) 2018  Kedar Kulkarni
    Full notice at main.cpp
**/

class Exception : public std::runtime_error
{
    public:
        using std::runtime_error::runtime_error;
};

#endif // EXCEPTION_H
