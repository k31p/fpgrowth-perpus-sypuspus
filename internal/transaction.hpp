#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "types.hpp"
#include "helper.hpp"
#include "../external/csv.hpp"

#include <iostream>
#include <map>
#include <vector>

/**
 * @brief Fungsi untuk membaca setiap transaksi dari file csv
*/
std::vector<Transaction> readTransactions(const std::string& filename){
    // Membuat vector untuk menyimpan transaksi
    std::vector<Transaction> transactions;
    
    // Membuat objek CSVReader
    csv::CSVReader reader(filename);

    for(csv::CSVRow& row: reader){
        Transaction transaction;

        transaction.id = row["transaction_number"].get<int>();
        transaction.categories = split_string(row["categories"].get<std::string>(), ',');

        transactions.push_back(transaction);
    }

    return transactions;
}

#endif