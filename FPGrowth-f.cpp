#include "FPGrowth.h"

//? HELPER FUNCTION
vector<string> split_string (const string& string_line, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream ss(string_line);

    while (getline(ss, token, delimiter))
        tokens.push_back(token);
    
    return tokens;
}
//! CONCRETE FUNCTION
vector<vector<string>> split_data(vector<string> data_list, char delimiter)
{
    vector<vector<string>> category_list;

    for (size_t i = 0; i < data_list.size(); i++) {
        category_list.push_back(split_string(data_list[i], delimiter));
    }

    return category_list;
}

unordered_map<string, int> count_support(vector<vector<string>> data_list)
{
    unordered_map<string, int> support_count;

    for (size_t i = 0; i < data_list.size(); i++)
    {
        for (size_t j = 0; j < data_list[i].size(); j++)
            support_count[data_list[i][j]]++;
    }

    return support_count;
}

vector<vector<string>> remove_low_support(vector<vector<string>> data_list, unordered_map<string,int> support_count, int minimum_support_count) 
{
    for (size_t i = 0; i < data_list.size(); i++) {
        for (size_t j = 0; j < data_list[i].size(); j++) {
            if (support_count[data_list[i][j]] < minimum_support_count)
                data_list[i].erase(data_list[i].begin() + (int) j);
        }
    }

    return data_list;
}

FPTree create_tree(vector<vector<string>> data_list)
{
    
}