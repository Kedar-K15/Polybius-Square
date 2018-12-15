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
#include <ios>
#include "Polybius.h"
#include "Exception.h"
#include "ConvertString.h"

std::string parse_str(std::string &input);
void welcome_screen();
void file_options();
void string_options();
int main()
{
    std::ios_base::sync_with_stdio(false);

    welcome_screen();
}

std::string parse_str(std::string &input) {
    std::string result;
    for(unsigned int i = 2; i < input.length(); i++) {
        result += input[i];
    }
    return result;
}

void welcome_screen() {
    std::string input;
    std::cout << "Welcome to the Polybius Square encryptor/decryptor!\n";
    std::cout << "Enter in \"F\" to encrypt/decrypt with files or \"S\" to use strings\n";
    std::cout << "Enter in \"E\" to exit" << std::endl;
    std::cout << "Answer: ";
    std::getline(std::cin, input);
    for(;;) {
        if((ConvertString::is_upper(input))) { ConvertString::to_lowercase(input); }
        if(input == "f") {
            std::cout << std::endl;
            file_options();
            break;
        }
        else if(input == "s") {
            std::cout << std::endl;
            string_options();
            break;
        }
        else if(input == "e") {
            break;
        }
        else {
            std::cout << "Incorrect input, try again:\n";
        }

        std::getline(std::cin, input);
    }
}

void file_options() {
    for(;;) {
        std::string input;
        std::cout << "Enter in \"Y\" to encrypt/decrypt an entire file or \"N\" to encrypt/decrypt the file in the console\n";
        std::cout << "Enter in \"M\" to return to the welcome screen" << std::endl;
        std::cout << "Answer: ";
        std::getline(std::cin, input);
        if((ConvertString::is_upper(input))) { ConvertString::to_lowercase(input); }
        try {
            if(input == "y") {
                std::cout << '\n';
                std::cout << "Enter in \"E\" to encrypt or \"D\" to decrypt followed by a space and the file path\n";
                std::cout << "Answer: ";
                std::getline(std::cin, input);
                if((ConvertString::is_upper(input))) { ConvertString::to_lowercase(input); }

                if(!(input.length() < 2) && input.at(0) == 'e' && input.at(1) == ' ') {
                    Polybius obj;
                    input = parse_str(input);
                    obj.encrypt_file(input);
                    std::cout << obj << '\n';
                }
                else if(!(input.length() < 2) && input.at(0) == 'd' && input.at(1) == ' ') {
                    Polybius obj;
                    input = parse_str(input);
                    obj.decrypt_file(input);
                    std::cout << obj << '\n';
                }
                else {
                    std::cout << "Incorrect input, try again:\n\n";
                }
            }
            else if(input == "n") {
                std::cout << '\n';
                std::cout << "Enter in \"E\" to encrypt or \"D\" to decrypt followed by a space and the file path\n";
                std::cout << "Answer: ";
                std::getline(std::cin, input);
                if((ConvertString::is_upper(input))) { ConvertString::to_lowercase(input); }

                if(!(input.length() < 2) && input.at(0) == 'e' && input.at(1) == ' ') {
                    Polybius obj;
                    input = parse_str(input);
                    obj.read_from_file(input);
                    obj.encrypt();
                    std::cout << obj << '\n';
                }
                else if(!(input.length() < 2) && input.at(0) == 'd' && input.at(1) == ' ') {
                    Polybius obj;
                    input = parse_str(input);
                    obj.read_from_file(input);
                    obj.decrypt();
                    std::cout << obj << '\n';
                }
                else {
                    std::cout << "Incorrect input, try again:\n\n";
                }
            }
            else if(input == "m") {
                std::cout << std::endl;
                welcome_screen();
                break;
            }
            else {
                std::cout << "Incorrect input, try again:\n\n";
            }
        } catch(const std::exception &e) {
            std::cout << e.what() << ", try again:\n\n";
        }
    }
}

void string_options() {
    for(;;) {
        std::string input;
        std::cout << "Enter in \"E\" to encrypt or \"D\" to decrypt followed by a space and the string\n";
        std::cout << "Enter in \"M\" to return to the welcome screen" << std::endl;
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
            else if(input == "m") {
                std::cout << std::endl;
                welcome_screen();
                break;
            }
            else {
                std::cout << "Incorrect input, try again:\n\n";
            }
        }
        catch(const std::exception &e) {
            std::cout << e.what()  << ", try again:\n\n";
        }
    }
}
