#ifndef FPTREEVIEW_H
#define FPTREEVIEW_H

#include "types.hpp"
#include <iostream>

void printTransactionData(const std::vector<Transaction> &transactionData)
{
    std::cout << "Transaction Data: " << std::endl;
    for (Transaction transaction : transactionData)
    {
        std::cout << "Transaction Number: " << transaction.id << " Categories: ";
        for (std::string category : transaction.categories)
        {
            std::cout << category << " ";
        }
        std::cout << std::endl;
    }
}

void printCategorySupport(const Categories &categorySupport){
    std::cout << "Category Support: " << std::endl;
    for (auto it = categorySupport.begin(); it != categorySupport.end(); it++)
    {
        std::cout << "Category: " << it->first << std::endl;
        std::cout << "Support: " << it->second << std::endl;
    }
}

/**
 * @brief Print fpnode
*/
void traverseFPNode(const FPNode node, const int level){
    for(int spaces = 0; spaces < level; spaces++){
        std::cout << "| ";
    }
    
    std::cout << "-> " << node.info << std::endl;
        
    // Call traverse again if childrens not empty
    if (node.childrens.empty() == false) {

        for (auto &it: node.childrens){
            traverseFPNode(it.second, level + 1);
        }
    }
}

/**
 * @brief Print fptree
*/
void printFPTree(const FPNode node){
    for(auto &it: node.childrens){
        traverseFPNode(it.second, 0);
        std::cout << std::endl;
    }
}

void printConditionalPatternBase(const std::unordered_map<std::string, std::vector<ConditionalPatternBase>> &conditionalPatternBase)
{
    std::cout << "Conditional Pattern Base: " << std::endl;
    for (auto it = conditionalPatternBase.begin(); it != conditionalPatternBase.end(); it++)
    {
        std::cout << "Category: " << it->first << std::endl;
        for (ConditionalPatternBase cpb : it->second)
        {
            std::cout << "Total support for this route: " << cpb.second << std::endl;
            std::cout << "Route: ";
            for (std::string category: cpb.first)
            {
                std::cout << category << " ";
            }
            std::cout << std::endl;
        }
    }
}

void printRuleSets(const RuleSets &ruleSets)
{
    std::cout << "Rule Sets: " << std::endl;
    for (auto it = ruleSets.begin(); it != ruleSets.end(); it++)
    {
        std::cout << "Category: " << it->first << std::endl;
        for (std::string category : it->second)
        {
            std::cout << category << " ";
        }
        std::cout << std::endl;
    }
}

#endif