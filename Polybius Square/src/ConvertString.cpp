/**
    Polybius-Square: A program that encrypts or decrypts strings using the Polybius Square
    Copyright (C) 2018  Kedar Kulkarni
    Full notice at main.cpp
**/

#include <iostream>
#include <algorithm>
#include <string>
#include "ConvertString.h"

std::string ConvertString::to_lowercase(std::string &input) {
    std::transform(input.begin(), input.end(), input.begin(), &::tolower);
    return input;
}

bool ConvertString::is_upper(std::string &input) {
    return std::any_of(input.begin(), input.end(), &::isupper);
}
