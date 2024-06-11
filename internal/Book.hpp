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

        std::vector<Book> categoryFilterer;
        recommendedBooks[category] = categoryFilterer;

        std::copy_if(bookData.begin(), bookData.end(), std::back_inserter(recommendedBooks[category]), [&category](const Book book) {return book.genre == category;});
    }

    return recommendedBooks;
}

#endif