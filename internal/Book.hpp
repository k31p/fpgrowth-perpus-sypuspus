#ifndef BOOK_H
#define BOOK_H

#include "types.hpp"
#include "../external/csv.hpp"

std::vector<Book> readBookData(const std::string& filename) {
    std::vector<Book> bookData;

    csv::CSVReader reader(filename);

    for(csv::CSVRow& row: reader){
        Book book;

        book.title = row["Title"].get<std::string>();
        book.author = row["Author"].get<std::string>();
        book.genre = row["Genre"].get<std::string>();

        bookData.push_back(book);
    }

    return bookData;
}

std::unordered_map<std::string, std::vector<Book>> GetRecommendation(Book borrowedBook, std::vector<Book> bookData, RuleSets ruleSets) {

    std::unordered_map<std::string, std::vector<Book>> recommendedBooks;

    std::vector<std::string> recommendedCategories = ruleSets[borrowedBook.genre];

    for (auto& category : recommendedCategories) {
        if (recommendedBooks.find(category) == recommendedBooks.end()) {
            std::vector<Book> temp;
            recommendedBooks[category] = temp;
        }

        std::vector<Book> categoryFilterer;

        std::copy_if(bookData.begin(), bookData.end(), std::back_inserter(categoryFilterer), [&category](const Book book) {return book.genre == category;});

        recommendedBooks[category] = categoryFilterer;
        categoryFilterer.clear();
    }

    return recommendedBooks;
}

#endif