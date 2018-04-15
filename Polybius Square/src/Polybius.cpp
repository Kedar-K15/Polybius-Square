/**
    Polybius-Square: A program that encrypts or decrypts strings using the Polybius Square
    Copyright (C) 2018  Kedar Kulkarni
    Full notice at main.cpp
**/

#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>
#include <algorithm>
#include <cctype>
#include "Polybius.h"
#include "Exception.h"

Polybius & Polybius::encrypt() {
    std::string temp;

    for(const char &c : str) {
        search = letters.find(c);
        if(c == ' ') {
            temp += " ";
        }
        else if(search != letters.end()) {
            temp += search->second;
        }
        else if(symbol_if(c) != "-1") {
            temp += symbol_if(c);
        }
        else {
            throw Exception("Invalid input");
        }
    }

    str = temp;
    add_history("Encrypted: " + str);
    return *this;
}

Polybius & Polybius::decrypt() {
    if(!(parse_decrypt(str))) {
        throw Exception("Invalid input");
    }

    std::string temp;
    std::string two;
    unsigned int count = 2;
    int iter;
    bool is_other;

    for(unsigned int i = 0; i < str.length(); i += iter) {
        is_other = false;
        for(unsigned int j = i; j < count; j++) {
           if(std::isspace(str[i])) {
                temp += " ";
                std::string().swap(two);
                is_other = true;
                break;
            }
            if(symbol_if(str[i]) != "-1") {
                temp += symbol_if(str[i]);
                std::string().swap(two);
                is_other = true;
                break;
            }
            two += str.at(j);
        }
        if(is_other) {
            iter = 1;
            count += 1;
        }
        else {
            iter = 2;
            count += 2;
            two.resize(2);
            if(check_key(two) != '\0') {
                temp += std::string(1,check_key(two));
            }
            else {
                throw Exception("Invalid input");
            }
            std::string().swap(two);
        }
    }

    str = temp;
    add_history("Decrypted: " + str);
    return *this;
}

std::string Polybius::get_string() const { return str; }

void Polybius::show_history() const {
    for(auto &x : history) {
        std::cout << x << ' ';
    }
}

std::ostream &operator<<(std::ostream& os, const Polybius &p) {
    if(!(p.history.empty())) {
        os << p.get_back();
    }
    else {
        os << "No encryption or decryption done";
    }
    return os;
}

void Polybius::add_history(const std::string &type) {
    history.emplace_back(type);
}

std::string Polybius::get_back() const {
  return history.back();
}

std::string Polybius::symbol_if(const char &c) const {
    if (std::find(symbols.begin(), symbols.end(), std::string(1,c)) != symbols.end()) {
        return std::string(1,c);
    }
    return "-1";
}

char Polybius::check_key(std::string &value) {
    for (search = letters.begin(); search != letters.end(); ++search) {
        if (search->second == value) {
            return search->first;
        }
    }
    return '\0';
}

bool Polybius::parse_decrypt(std::string &value) {
    value.erase(std::remove_if(value.begin(), value.end(), isspace), value.end());

    if((value.length() % 2) == 0) {
        return true;
    }

    return false;
}