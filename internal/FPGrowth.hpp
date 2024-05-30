#ifndef FPGROWTH_H
#define FPGROWTH_H

#define MINIMUM_SUPPORT_COUNT 5

#include "types.hpp"
#include <algorithm>
#include <vector>
#include <unordered_map>

/**
 * @brief Fungsi untuk menghitung frekuensi dari setiap item
 */
std::unordered_map<std::string, int> countItemFrequency(const std::vector<Transaction>& transactions)
{
    std::unordered_map<std::string, int> item_frequency;

    for (Transaction transaction : transactions)
    {
        for (std::string category : transaction.categories)
        {
            if (item_frequency.find(category) == item_frequency.end())
                item_frequency[category] = 1;
            else
                item_frequency[category]++;
        }
    }

    return item_frequency;
}

std::vector<Transaction> eliminateTransactionsCategoriesBelowMinimumSupportCount(const std::vector<Transaction> &transactions, const std::unordered_map<std::string, int> &item_frequency)
{
    std::vector<Transaction> filtered_transactions;

    for (Transaction transaction : transactions)
    {
        Transaction filtered_transaction;
        filtered_transaction.id = transaction.id;

        for (std::string category : transaction.categories)
        {
            if (item_frequency.find(category) != item_frequency.end() && item_frequency.at(category) >= MINIMUM_SUPPORT_COUNT)
                filtered_transaction.categories.push_back(category);
        }

        if (!filtered_transaction.categories.empty())
            filtered_transactions.push_back(filtered_transaction);
    }

    return filtered_transactions;
}

/**
 * @brief Fungsi untuk menghapus item yang tidak memenuhi minimum support count
 */
std::unordered_map<std::string, int> removeItemsBelowMinimumSupportCount(const std::unordered_map<std::string, int> &item_frequency)
{
    std::unordered_map<std::string, int> filtered_item_frequency;

    for (auto it = item_frequency.begin(); it != item_frequency.end(); it++)
    {
        if (it->second >= MINIMUM_SUPPORT_COUNT)
            filtered_item_frequency[it->first] = it->second;
    }

    return filtered_item_frequency;
}

/**
 * @brief Method untuk mengurutkan kategori dalam transaksi berdasarkan frekuensinya
 */
void sortTransactionItemsByFrequency(std::vector<Transaction> &transactions, const std::unordered_map<std::string, int> &item_frequency)
{
    for (Transaction &transaction : transactions)
    {
        std::sort(transaction.categories.begin(), transaction.categories.end(), [&](const std::string &a, const std::string &b)
                  { return item_frequency.at(a) > item_frequency.at(b); });
    }
}

/**
 * @brief Fungsi untuk membuat FP-Tree
 */
FPTree createFPTree(const std::vector<Transaction> &transactions, const std::unordered_map<std::string, int> &item_frequency)
{
    FPTree tree;

    for (Transaction transaction : transactions)
    {
        FPNode *current_node = nullptr;

        for (int i = 0; i < transaction.categories.size(); i++)
        {
            // Check if current node is null
            if (current_node == nullptr)
            {
                if (tree.childrens.find(transaction.categories[i]) == tree.childrens.end())
                {
                    FPNode new_node;
                    new_node.info = transaction.categories[i];
                    new_node.frequency = 1;
                    tree.childrens[transaction.categories[i]] = new_node;
                }
                else
                {
                    tree.childrens[transaction.categories[i]].frequency++;
                }

                current_node = &tree.childrens[transaction.categories[i]];
                continue;
            }

            // Check if the current node not have the children
            if (current_node->childrens.find(transaction.categories[i]) == current_node->childrens.end())
            {
                FPNode new_node;
                new_node.info = transaction.categories[i];
                new_node.frequency = 1;
                current_node->childrens[transaction.categories[i]] = new_node;
            }
            else
            {
                current_node->childrens[transaction.categories[i]].frequency++;
            }

            current_node = &current_node->childrens[transaction.categories[i]];
        }
    }

    return tree;
}

/**
 * @brief Print fpnode
*/
void traverseFPNode(const FPNode node){
    std::cout << node.info << " ";
        
    // Call traverse again if childrens not empty
    std::cout << "Child: ";
    for (auto &it: node.childrens){
        traverseFPNode(it.second);
    }
}

/**
 * @brief Print fptree
*/
void traverseFPTree(const FPTree tree){
    for(auto &it: tree.childrens){
        std::cout << "Currently selected: " << it.second.info << std::endl;
        traverseFPNode(it.second);
        std::cout << std::endl;
    }
}

/**
 * @brief Prosedur untuk mencari setiap kemungkinan rute dari suatu kategori
 */
void findRoutes(const FPNode &node, std::vector<std::string> &route, Routes &routes){
    route.push_back(node.info);

    if (node.childrens.empty()){
        routes[route[0]] = route;
        return;
    }

    for (auto &it: node.childrens){
        findRoutes(it.second, route, routes);
    }

    route.pop_back();
}

#endif