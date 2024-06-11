#include "internal/types.hpp"
#include "internal/transaction.hpp"
#include "internal/FPGrowth.hpp"
#include "internal/UI.hpp"
#include "internal/FPTreeView.hpp"

#include <iostream>
#include <vector>
#include <unordered_map>

#ifdef _WIN32
#define Sleep Sleep
#else
#define Sleep sleep
#endif

int main(){
    //! FP-Growth Processing

    //? [1] Read Transaction Data
    std::vector<Transaction> transactionData = readTransactions("transaction_data.csv");

    //? [2] Count Support for Each Item
    Categories categorySupport = countItemSupport(transactionData);

    //? [3] Transform data by: Eliminating item below min support count, sort data descending by item support
    Categories categorySupportTransformed = removeItemsBelowMinimumSupportCount(categorySupport);
    std::vector<Transaction> transactionDataTransformed = eliminateTransactionsCategoriesBelowMinimumSupportCount(transactionData, categorySupportTransformed);
    sortTransactionItemsByFrequency(transactionDataTransformed, categorySupport);

    //? [4] Constructing FP-Tree
    FPNode fpTree = createFPTree(transactionDataTransformed, categorySupportTransformed);

    //? [5] Defining Conditional Pattern Base
    std::unordered_map<std::string, std::vector<ConditionalPatternBase>> conditionalPatternBase;
    condPatternBase(fpTree, conditionalPatternBase);

    //? [6] Defining Conditional FP-Tree

    std::vector<Book> bookData = readBookData("book_data.csv");
    int userInput; //! for handling user input.

    while (true)
    {
        printMainHeader();
        printMainMenu();
        userInput = inputHandler(1, 3, printMainHeader, printMainMenu);

        switch (userInput)
        {
        case 1:
            printPinjamBukuHeader();
            printPinjamBukuMenu();
            Sleep(3000);
            continue;

        case 2:
            printRekomendasiBukuHeader();
            Sleep(3000);
            continue;

        case 3:
            printFPGrowthHeader();
            Sleep(3000);
            continue;

        case 4:
            printExitHeader();
            Sleep(3000);
            return 0;
        }
    }
}