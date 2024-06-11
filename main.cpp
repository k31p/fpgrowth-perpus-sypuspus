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
    std::unordered_map<std::string, ConditionalFPTree> conditionalFPTree = condFPTree(conditionalPatternBase);
    filterConditionalFPTree(conditionalFPTree);

    //? [7] Defining Rule Sets
    RuleSets ruleSets = CreateRuleSets(conditionalFPTree);


    std::vector<Book> bookData = readBookData("book_data.csv");
    Book borrowedBook;
    std::unordered_map<std::string, std::vector<Book>> recommendedBooks;
    int userInput; //! for handling user input.

    
    while(true) {
        printMainHeader();
        printMainMenu();

        userInput = inputHandler(1, 3, "Masukkan Input:", printMainHeader, printMainMenu);

        if (userInput == 1) {
            printPinjamBukuHeader();
            printPinjamBukuMenu();

            userInput = inputHandler(1, 30, "Masukkan No. Buku:", printPinjamBukuHeader, printPinjamBukuMenu);
            borrowedBook = bookData[userInput - 1];
        }
        else if (userInput == 2) {
            printRekomendasiBukuHeader();
            recommendedBooks = GetRecommendation(borrowedBook, bookData, ruleSets);
            std::cin.get();
        }
        else if (userInput == 3) {
            printFPGrowthHeader();
        }
        else if (userInput == 4) {
            printExitHeader();
            Sleep(3000);
            return 0;
        }
        else {
            continue;
        }
    }
}