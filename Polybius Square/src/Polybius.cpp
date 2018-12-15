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
#include <fstream>
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
    add_history("Encrypted: " + str + "; ");
    return *this;
}

Polybius & Polybius::decrypt() {
    std::string temp;
    int iter = 0;

    while(iter < str.length()) {
        if(iter+1 == str.length()) {
            break;
        }
        else if(std::isspace(str.at(iter))) {
            temp += " ";
            iter += 1;
            continue;
        }
        else if(symbol_if(str.at(iter)) != "-1") {
            temp += symbol_if(str.at(iter));
            iter += 1;
            continue;
        }
        else if(!(std::isspace(str.at(iter+1))) && !(symbol_if(str.at(iter+1)) != "-1")){
            std::string both = std::string(1,str.at(iter)) + std::string(1,str.at(iter+1));
            if(check_key(both) != '\0') {
                temp += std::string(1,check_key(both));
            }
            else {
                iter += 2;
                continue;
            }
        }
        else {
           iter += 1;
           continue;
        }
       iter += 2;
    }

    if(temp.empty() || temp.find_first_not_of(' ') == std::string::npos) {
        throw Exception("Invalid input");
    }

    str = temp;
    add_history("Decrypted: " + str + "; ");
    return *this;
}

std::string Polybius::get_string() const { return str; }

void Polybius::show_history() const {
    for(auto &x : history) {
        std::cout << x << ' ';
    }
}

void Polybius::read_from_file(std::string &file_path) {
    std::string line;
    std::string temp;
    std::ifstream file(file_path);
    if(file.is_open()) {
        while(std::getline(file, line)) {
            temp += line;
        }
        str = temp;
        file.close();
     //   std::cout << "The file should be closed now" << std::endl;
    }
    else {
        file.close();
        throw Exception("File does not exist");
    }
}

void Polybius::encrypt_file(std::string &file_path) {
    read_from_file(file_path);
    std::ofstream file(file_path);
    // if(file.is_open()) { std::cout << "Wait what it's open?" << std::endl; }
   // std::cout << "So we have read from the file, now to encrypt function" << std::endl;
    encrypt();
   // std::cout << "After incorrect input ?? " << std::endl;
    if(file.is_open()) {
        file << str << '\n';
        file.close();
    }
    else {
        file.close();
        throw Exception("File does not exist");
    }
}

void Polybius::decrypt_file(std::string &file_path) {
    read_from_file(file_path);
    std::ofstream file(file_path);
    decrypt();
    if(file.is_open()) {
        file << str << '\n';
        file.close();
    }
    else {
        file.close();
        throw Exception("File does not exist");
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

char Polybius::check_key(const std::string &value) {
    for (search = letters.begin(); search != letters.end(); ++search) {
        if (search->second == value) {
            return search->first;
        }
    }
    return '\0';
}
