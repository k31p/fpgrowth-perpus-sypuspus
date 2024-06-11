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
Categories countItemFrequency(const std::vector<Transaction>& transactions){
    Categories item_frequency;

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

std::vector<Transaction> eliminateTransactionsCategoriesBelowMinimumSupportCount(const std::vector<Transaction> &transactions, const Categories &item_frequency)
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
Categories removeItemsBelowMinimumSupportCount(const Categories &item_frequency)
{
    Categories filtered_item_frequency;

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
void sortTransactionItemsByFrequency(std::vector<Transaction> &transactions, Categories &item_frequency)
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
FPNode createFPTree(const std::vector<Transaction> &transactions, Categories &item_frequency)
{
    FPNode rootNode;

    for (Transaction transaction : transactions)
    {
        FPNode *current_node = nullptr;

        for (int i = 0; i < transaction.categories.size(); i++)
        {
            // Check if current node is null
            if (current_node == nullptr)
            {
                if (rootNode.childrens.find(transaction.categories[i]) == rootNode.childrens.end())
                {
                    FPNode new_node;
                    new_node.info = transaction.categories[i];
                    new_node.frequency = 1;
                    new_node.parent = &rootNode;
                    rootNode.childrens[transaction.categories[i]] = new_node;
                }
                else
                {
                    rootNode.childrens[transaction.categories[i]].frequency++;
                }

                current_node = &rootNode.childrens[transaction.categories[i]];
                continue;
            }

            // Check if the current node not have the children
            if (current_node->childrens.find(transaction.categories[i]) == current_node->childrens.end())
            {
                FPNode new_node;
                new_node.info = transaction.categories[i];
                new_node.frequency = 1;
                new_node.parent = current_node;
                current_node->childrens[transaction.categories[i]] = new_node;
            }
            else
            {
                current_node->childrens[transaction.categories[i]].frequency++;
            }

            current_node = &current_node->childrens[transaction.categories[i]];
        }
    }

    return rootNode;
}

/**
 * @brief Print fpnode
*/
void traverseFPNode(const FPNode node, int &level){
    // Print garis untuk setiap node
    std::cout << "|" << std::endl << "| ";
    for (int stripes = 1; stripes <= level; stripes++){
        std::cout << "-";
    }
    
    std::cout << " " << node.info << std::endl;
        
    // Call traverse again if childrens not empty
    if (node.childrens.empty() == false) {
        level++;
        for (auto &it: node.childrens){
            traverseFPNode(it.second, level);
        }
    }
    else {
        level = 2;
        return;
    }
}

/**
 * @brief Print fptree
*/
void traverseFPTree(const FPNode node){
    for(auto &it: node.childrens){
        int level = 1;
        std::cout << it.second.info << std::endl;
        traverseFPNode(it.second, level);
        std::cout << std::endl;
    }
}

std::unordered_map<std::string, ConditionalFPTree> condFPTree(
    const std::unordered_map<std::string, std::vector<ConditionalPatternBase>>& categoryRoutes) {
    
    std::unordered_map<std::string, std::unordered_map<std::string, int>> result;

    for (const auto& categoryEntry : categoryRoutes) {
        const std::string& category = categoryEntry.first;
        const std::vector<ConditionalPatternBase>& conditionalPatternBases = categoryEntry.second;
        
        std::unordered_map<std::string, int> frequencyMap;

        // Count the frequency of each string across all routes in this category
        for (const auto& cpb : conditionalPatternBases) {
            const Route& route = cpb.first;
            int routeFrequency = cpb.second;
            std::unordered_set<std::string> seenInCurrentRoute;
            for (const auto& str : route) {
                // To avoid counting duplicates within the same route
                if (seenInCurrentRoute.find(str) == seenInCurrentRoute.end()) {
                    frequencyMap[str] += routeFrequency;
                    seenInCurrentRoute.insert(str);
                }
            }
        }

        // Collect elements that appear in at least two routes
        std::unordered_map<std::string, int> intersection;
        for (const auto& entry : frequencyMap) {
            if (entry.second > 1) {  // Appears in at least two routes
                intersection[entry.first] = entry.second;
            }
        }

        if (!intersection.empty()) {
            result[category] = intersection;
        }
    }

    return result;
}

void ascendTree(FPNode node, Route &currentRoute) {
    if (node.parent != nullptr) {
        if (node.parent->info != "")
            currentRoute.push_front(node.parent->info);
        ascendTree(*(node.parent), currentRoute);
    }
}

std::unordered_map<std::string, std::vector<ConditionalPatternBase>> condPatternBase(const FPNode tree, std::unordered_map<std::string, std::vector<ConditionalPatternBase>> &conditionalPatternBase) {

    for (auto& map : tree.childrens) {

        Route currentRoute;
        ConditionalPatternBase currentCdp;

        ascendTree(map.second, currentRoute);

        if (currentRoute.size() > 1) {
            if (conditionalPatternBase.find(map.first) == conditionalPatternBase.end()) {
                std::vector<ConditionalPatternBase> temp;
                conditionalPatternBase[map.first] = temp;
            }
            currentCdp.first = currentRoute;
            currentCdp.second = map.second.frequency;
            conditionalPatternBase[map.first].push_back(currentCdp);
        }

        currentRoute.clear();

        condPatternBase(map.second, conditionalPatternBase);
    }

    return conditionalPatternBase;
}

void filterConditionalFPTree(std::unordered_map<std::string, ConditionalFPTree> &conditionalFPTree) {

    for (auto& pair : conditionalFPTree) {

        std::vector<std::pair<std::string, int>> conditionalFPTreePair(pair.second.begin(), pair.second.end());

        std::sort(conditionalFPTreePair.begin(), conditionalFPTreePair.end(), [](const std::pair<std::string, int> a, const std::pair<std::string, int> b) {
            return a.second > b.second;
        });

        for (auto it = pair.second.begin(); it != pair.second.end(); ) {
            if (it->first != conditionalFPTreePair[0].first && it->first != conditionalFPTreePair[1].first) {
                it = pair.second.erase(it);
            } else {
                ++it;
            }
        }

    }

}

RuleSets CreateRuleSets(std::unordered_map<std::string, ConditionalFPTree> conditionalFPTree) {

    RuleSets ruleSets;

    for (auto& it : conditionalFPTree) {
        for (auto& item : it.second) {
            std::vector<std::string> temp;
            
            if (ruleSets.find(it.first) == ruleSets.end())
                ruleSets[it.first] = temp;

            if (ruleSets.find(item.first) == ruleSets.end())
                ruleSets[item.first] = temp;
            
            ruleSets[it.first].push_back(item.first);
            ruleSets[item.first].push_back(it.first);
        }
    }

    return ruleSets;
}

#endif