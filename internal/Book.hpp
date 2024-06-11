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

#endif