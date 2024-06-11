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

    printf("Transaction Data\n");
    printf("===============\n");
    for (auto& it : transactions)
    {
        std::cout << "Transaction ID: " << it.id << std::endl;
        std::cout << "Categories: ";
        for (std::string category : it.categories)
            std::cout << category << " ";
        std::cout << std::endl;
    }
    printf("\n\n");

    /**
     * STEP 2: Count item frequency
    */
    Categories item_frequency = countItemFrequency(transactions);

    printf("Item Frequency\n");
    printf("==============\n");
    for (auto& it : item_frequency)
    {
        std::cout << "Category: " << it.first << " Frequency: " << it.second << std::endl;
    }
    printf("\n\n");

    /**
     * STEP 3: Remove items below minimum support count
    */
    item_frequency = removeItemsBelowMinimumSupportCount(item_frequency);

    printf("Item Frequency (After Removing Items Below Minimum Support Count)\n");
    printf("===============================================================\n");
    for (auto& it : item_frequency)
    {
        std::cout << "Category: " << it.first << " Frequency: " << it.second << std::endl;
    }
    printf("\n\n");
    
    /**
     * STEP 4: Eliminate transactions categories below minimum support count
    */
    transactions = eliminateTransactionsCategoriesBelowMinimumSupportCount(transactions, item_frequency);

    printf("Transaction Data (After Eliminating Transactions Categories Below Minimum Support Count)\n");
    printf("=========================================================================================\n");
    for (auto& it : transactions)
    {
        std::cout << "Transaction ID: " << it.id << std::endl;
        std::cout << "Categories: ";
        for (std::string category : it.categories)
            std::cout << category << " ";
        std::cout << std::endl;
    }
    printf("\n\n");

    /**
     * STEP 5: Sort transactions by frequency
    */   
    sortTransactionItemsByFrequency(transactions, item_frequency);

    printf("Transaction Data (After Sorting Transactions by Frequency)\n");
    printf("=========================================================\n");
    for(Transaction transaction: transactions){
        std::cout << "Transaction ID: " << transaction.id << std::endl;
        std::cout << "Categories: ";
        for(std::string category: transaction.categories)
            std::cout << category << " ";
        std::cout << std::endl;
    }
    printf("\n\n");

    /**
     * STEP 6: Construct FPTree
    */
    FPNode fptree = createFPTree(transactions, item_frequency);

    printf("FPTree\n");
    printf("======\n");
    traverseFPTree(fptree);
    printf("\n\n");

    /**
     * STEP 7: Find each route for eacn category
    */
    std::unordered_map<std::string, std::vector<ConditionalPatternBase>> conditionalPatternBase;
    std::unordered_map<std::string, std::vector<ConditionalPatternBase>> routes = condPatternBase(fptree, conditionalPatternBase);

    std::unordered_map<std::string, ConditionalFPTree> conditionalFPTree = condFPTree(routes);

    filterConditionalFPTree(conditionalFPTree);


    return 0;
}