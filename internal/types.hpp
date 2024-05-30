#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <vector>
#include <unordered_map>

/**
 * @brief Tipe data struct untuk mereprentasikan data buku
*/
using Book = struct Book {
    std::string title = "";
    std::string author = "";
    std::string genre = "";
};

/**
 * @brief Tipe data struct untuk merepresentasikan data transaksi
*/

using FPNode = struct FPNode {
    std::string info = "";
    int frequency = 0;
    std::unordered_map<std::string, FPNode> childrens;
};

/**
 * @brief Tipe data struct untuk merepresentasikan FPTree
*/
using FPTree = struct FPTree {
    std::unordered_map<std::string, FPNode> childrens;
};

/**
 * @brief Tipe data struct untuk merepresentasikan data transaksi
*/
using Transaction = struct Transaction {
    int id = 0;
    std::vector<std::string> categories;
};

/**
 * @brief Tipe data struct untuk merepresentasikan data rute setiap kategori
*/
using Routes = std::unordered_map<std::string, std::vector<std::string>>;


#endif