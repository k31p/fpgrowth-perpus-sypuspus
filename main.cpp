#include "internal/types.hpp"
#include "internal/transaction.hpp"
#include "internal/FPGrowth.hpp"

#include <iostream>
#include <vector>
#include <unordered_map>

int main(){
    /**
     * STEP 1: Read transaction data
    */
    std::vector<Transaction> transactions = readTransactions("transaction_data.csv");

    for(Transaction transaction: transactions){
        std::cout << "Transaction ID: " << transaction.id << std::endl;
        std::cout << "Categories: ";
        for(std::string category: transaction.categories)
            std::cout << category << " ";
        std::cout << std::endl;
    }


    /**
     * STEP 2: Count item frequency
    */
    std::unordered_map<std::string, int> item_frequency = countItemFrequency(transactions);

    for(auto it = item_frequency.begin(); it != item_frequency.end(); it++)
        std::cout << it->first << ": " << it->second << std::endl;

    /**
     * STEP 3: Remove items below minimum support count
    */
    item_frequency = removeItemsBelowMinimumSupportCount(item_frequency);

    for(auto it = item_frequency.begin(); it != item_frequency.end(); it++)
        std::cout << it->first << ": " << it->second << std::endl;
    
    /**
     * STEP 4: Eliminate transactions categories below minimum support count
    */
    transactions = eliminateTransactionsCategoriesBelowMinimumSupportCount(transactions, item_frequency);

    /**
     * STEP 5: Sort transactions by frequency
    */   
    sortTransactionItemsByFrequency(transactions, item_frequency);

    std::cout << transactions.size() << std::endl;
    for(Transaction transaction: transactions){
        std::cout << "Transaction ID: " << transaction.id << std::endl;
        std::cout << "Categories: ";
        for(std::string category: transaction.categories)
            std::cout << category << " ";
        std::cout << std::endl;
    }

    return 0;
}