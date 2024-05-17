#include <iostream>
#include "csv.h"
#include "FPGrowth.h"

using namespace std;

#define NO_PEMINJAM "No Peminjam"
#define KATEGORI "Kategori"

bool compare(const string& a, const string& b, unordered_map<string,int> freq)
{
    return freq[a] > freq[b];
}

int main()
{
    unordered_map<string, vector<string>> data_source;

    data_source = read_csv("Data Source/data_source.csv");

    // for (size_t i = 0; i < data_source[NO_PEMINJAM].size(); i++) {
    //     cout << data_source[NO_PEMINJAM][i] << ". " << data_source[KATEGORI][i] << endl;
    // }

    vector<vector<string>> category_list = split_data(data_source[KATEGORI], ','); 

    unordered_map<string, int> support_count = count_support(category_list);

    for (auto it = support_count.begin(); it != support_count.end(); ++it)
    {
        cout << it->first << ": " << it->second << endl;
    }

    // for (size_t i = 0; i < category_list.size(); i++) {
    //     cout << i+1 << " ";
    //     for (size_t j = 0; j < category_list[i].size(); j++) {
    //         cout << category_list[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    for (size_t i = 0; i < category_list.size(); i++)
    {
        sort(category_list[i].begin(), category_list[i].end(), [&support_count](const string& a, const string& b) {
            return compare(a, b, support_count);
        });
    }


    category_list = remove_low_support(category_list, support_count, 2);

    for (size_t i = 0; i < category_list.size(); i++) {
        cout << i+1 << ". ";
        for (size_t j = 0; j < category_list[i].size(); j++) {
            cout << category_list[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}