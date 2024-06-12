#ifndef UI_H
#define UI_H

#include "Book.hpp"

#include <iostream>
#include <vector>

void println(std::string string) {
    std::cout << string << std::endl;
}

void printMainHeader() {
    system("cls");
    std::cout << "========================================\n";
    std::cout << " ___  _ _  ___  _ _  ___  ___  _ _  ___ \n";
    std::cout << "/ __>| | || . \\| | |/ __>| . \\| | |/ __>\n";
    std::cout << "\\__ \\\\   /|  _/| ' |\\__ \\|  _/| ' |\\__ \\\n";
    std::cout << "<___/ |_| |_|  `___'<___/|_|  `___'<___/\n";
    std::cout << "                                        \n";
    std::cout << "========================================\n";
}

void printPinjamBukuHeader() {
    system("cls");
    std::cout << "=================================================\n";
    std::cout << " ___  _       _               ___       _        \n";
    std::cout << "| . \\<_>._ _ <_> ___ ._ _ _  | . > _ _ | |__ _ _ \n";
    std::cout << "|  _/| || ' || |<_> || ' ' | | . \\| | || / /| | |\n";
    std::cout << "|_|  |_||_|_|| |<___||_|_|_| |___/`___||_\\_\\`___|\n";
    std::cout << "            <__'                                 \n";
    std::cout << "=================================================\n";
}

void printRekomendasiBukuHeader() {
    system("cls");
    std::cout << "============================================================================\n";
    std::cout << " ___       _                            _           _   ___       _        \n";
    std::cout << "| . \\ ___ | |__ ___ ._ _ _  ___ ._ _  _| | ___  ___<_> | . > _ _ | |__ _ _ \n";
    std::cout << "|   // ._>| / // . \\| ' ' |/ ._>| ' |/ . |<_> |<_-<| | | . \\| | || / /| | |\n";
    std::cout << "|_\\_\\\\___.|_\\_\\\\___/|_|_|_|\\___.|_|_|\\___|<___|/__/|_| |___/`___||_\\_\\`___|\n";
    std::cout << "                                                                            \n";
    std::cout << "============================================================================\n";
}

void printFPGrowthHeader() {
    system("cls");
    std::cout << "=========================================================\n";
    std::cout << " ___  ___       ___                     _    _           \n";
    std::cout << "| __>| . \\ ___ /  _>  _ _  ___  _ _ _ _| |_ | |_         \n";
    std::cout << "| _> |  _/|___|| <_/\\| '_>/ . \\| | | | | |  | . |        \n";
    std::cout << "|_|  |_|       `____/|_|  \\___/|__/_/  |_|  |_|_|        \n";
    std::cout << "                                                         \n";
    std::cout << "=========================================================\n";
}

void printExitHeader() {
    system("cls");
    std::cout << "==================================================\n";
    std::cout << " ___  _              _     _ _                   \n";
    std::cout << "|_ _|| |_  ___ ._ _ | |__ | | | ___  _ _         \n";
    std::cout << " | | | . |<_> || ' || / / \\   // . \\| | | _      \n";
    std::cout << " |_| |_|_|<___||_|_||_\\_\\  |_| \\___/`___|<_>    \n";
    std::cout << "                                                \n";
    std::cout << "==================================================\n";
    std::cout << "              Created by Fitra & Yobel            \n";
    std::cout << "==================================================\n";
}

void printMainMenu() {
    println("[1] Pinjam Buku");
    println("[2] Rekomendasi Buku");
    println("[3] View FP-Growth Algorithm");
    println("[4] View FP-Growth Algorithm");
}

void printPinjamBukuMenu() {
    std::vector<Book> bookData = readBookData("../book_data.csv");

    int index = 1;
    for (auto& book : bookData) {
        std::cout << "[" << index << "] " << book.title << "|" << book.genre << "|" << book.author << std::endl;
        if (index%5 == 0) 
            std::cout << std::endl;
        index++; 
    }
}

void printRekomendasiBuku(Book *borrowedBook, std::vector<Book> bookData, RuleSets ruleSets) {
    if (borrowedBook == nullptr) {
        std::cout << "Anda belum meminjam buku apapun." << std::endl;
        return;
    }
    
    std::cout << "Karena anda menyukai " + (*borrowedBook).title + ", mungkin anda akan menyukai: " << std::endl;

    std::unordered_map<std::string, std::vector<Book>> recommendedBooks = GetRecommendation((*borrowedBook), bookData, ruleSets);

    for (auto& recommendedBook : recommendedBooks) {
        std::cout << "Buku " << recommendedBook.first << ": " << std::endl;
        for (auto& book : recommendedBook.second) {
            std::cout << "\t - " << book.title << " | " << book.author << std::endl;
        }
        std::cout << std::endl;
    }
}

void printFPGrowthMenu() {
    println("[1] Sumber Data");
    println("[2] Counting Support Item");
    println("[3] Transformed Data");
    println("[4] View FP-Tree");
    println("[5] View Conditional Pattern Base");
    println("[6] View Conditional FPTree");
    println("[7] View Frequent Pattern Generated");
}

int inputHandler(int min_limit, int max_limit, std::string message, void headerFunction(), void menuFunction()) {
    int userInput = 0;
    
    while (true)
    {
        std::cout << message << " ";
        std::cin >> userInput;

        if (userInput >= min_limit && userInput <= max_limit) {
            return userInput;
        }
        else {
            headerFunction();
            menuFunction();

            std::cout << "Invalid Input" << std::endl;
            std::cout << message << " " << min_limit << " - " << max_limit << ": ";
            std::cin >> userInput;
            std::cin.clear();            
        }
    }
    
}

#endif