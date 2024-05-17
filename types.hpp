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
    std::vector<FPNode> children;
};

/**
 * @brief Tipe data struct untuk merepresentasikan FPTree
*/
using FPTree = struct FPTree {
    int count = 0;
    std::vector<FPNode> children;
};


#endif