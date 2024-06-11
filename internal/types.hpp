#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <map>

/**
 * @brief Tipe data struct untuk mereprentasikan data buku
*/
using Book = struct Book {
    std::string title = "";
    std::string author = "";
    std::string genre = "";
};

/**
 * @brief Tipe data struct untuk merepresentasikan setiap kategori dan frekuensinya
*/
using Categories = std::map<std::string, int>;

/**
 * @brief Tipe data struct untuk merepresentasikan data transaksi
*/

using FPNode = struct FPNode {
    std::string info = "";
    int frequency = 0;
    FPNode *parent = nullptr;
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
using Route = std::deque<std::string>;

using ConditionalPatternBase = std::pair<Route, int>;

using ConditionalFPTree = std::unordered_map<std::string, int>;


#endif