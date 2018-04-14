#ifndef POLYBIUS_H
#define POLYBIUS_H

/**
    Polybius-Square: A program that encrypts or decrypts strings using the Polybius Square
    Copyright (C) 2018  Kedar Kulkarni
    Full notice at main.cpp
**/

#include <vector>
#include <unordered_map>

class Polybius
{
    public:
        explicit Polybius(std::string str) : str(str) {}
        explicit Polybius(const Polybius &p) : str(p.str), history(p.history) {}

        Polybius & encrypt();
        Polybius & decrypt();
        std::string get_string() const;
        void show_history() const;

        friend std::ostream &operator<<(std::ostream& os, const Polybius &p);
        Polybius &operator=(const Polybius &p) {
            if(this != &p) {
                str = p.str;
                history = p.history;
            }
            return *this;
        }
        Polybius &operator=(const std::string &rhs) {
            if(str != rhs) {
                str = rhs;
            }
            return *this;
        }
    private:
        std::string str;
        std::unordered_map<char, std::string> letters = {
                {'a', "11"}, {'b', "12"}, {'c', "13"}, {'d', "14"}, {'e', "15"},
                {'f', "21"}, {'g', "22"}, {'h', "23"}, {'i', "24"}, {'j', "24"},
                {'k', "25"}, {'l', "31"}, {'m', "32"}, {'n', "33"}, {'o', "34"},
                {'p', "35"}, {'q', "41"}, {'r', "42"}, {'s', "43"}, {'t', "44"},
                {'u', "45"}, {'v', "51"}, {'w', "52"}, {'x', "53"}, {'y', "54"},
                {'z', "55"},
        };
        std::unordered_map<char, std::string>::const_iterator search;
        std::vector<std::string> symbols = {"!","@","#","$","%","^","&","*","(",")",",",".","?","/","'"};
        std::vector<std::string> history;

        void add_history(const std::string &type);
        std::string get_back() const;
        std::string symbol_if(const char &c) const;
        char check_key(std::string &value);
        bool parse_decrypt(std::string &value);
};

#endif // POLYBIUS_H
