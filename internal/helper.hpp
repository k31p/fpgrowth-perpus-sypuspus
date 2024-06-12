#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <sstream>
#include <vector>

/**
 * @brief Fungsi untuk menghapus whitespace di awal dan akhir string
*/
std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
        return str;
    
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

/**
 * @brief Fungsi untuk membagi string berdasarkan delimiter
*/  
std::vector<std::string> split_string(const std::string& string_line, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream ss(string_line);

    while (getline(ss, token, delimiter))
        tokens.push_back(trim(token));
    
    return tokens;
}

/**
 * @brief Method untuk menyimulasikan "press any key to continue"
*/
void pressAnyKey()
{
    #ifdef _WIN32
    system("pause");
    #else
    system("read");
    #endif
}

#endif 