/**
    Polybius-Square: A program that encrypts or decrypts strings using the Polybius Square
    Copyright (C) 2018  Kedar Kulkarni

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <iostream>
#include "Polybius.h"
#include "Exception.h"
#include "ConvertString.h"

std::string parse_str(std::string &input);

int main()
{
    std::string input;
    for(;;) {
        std::cout << "Enter in \"E\" to encrypt or \"D\" to decrypt followed by a space and the string\n";
        std::cout << "Enter in \"S\" to exit" << std::endl;
        std::cout << "Answer: ";
        std::getline(std::cin, input);
        if((ConvertString::is_upper(input))) { ConvertString::to_lowercase(input); }
        try {
            if(!(input.length() < 2) && input.at(0) == 'e' && input.at(1) == ' ') {
                Polybius obj(parse_str(input));
                obj.encrypt();
                std::cout << obj << '\n';
            }
            else if(!(input.length() < 2) && input.at(0) == 'd' && input.at(1) == ' ') {
                Polybius obj(parse_str(input));
                obj.decrypt();
                std::cout << obj << '\n';
            }
            else if(input == "s") {
                break;
            }
            else {
                std::cout << "Incorrect input. Try again:\n";
            }
        }
        catch(const std::exception &e) {
            std::cout << e.what()  << ", try again:\n";
        }
        std::cout << std::endl;
    }
}

std::string parse_str(std::string &input) {
    std::string result;
    for(unsigned int i = 2; i < input.length(); i++) {
        result += input[i];
    }
    return result;
}
