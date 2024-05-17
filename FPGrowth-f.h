#ifndef FPGrowth_H
#define FPGrowth_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

using FPNode = struct FPNode {
    string category;
    int frequency;
    unordered_map<string, FPNode> children;
};

using FPTree = struct FPTree {
    FPNode root;
};

vector<vector<string>> split_data(vector<string> data_list, char delimiter);

unordered_map<string, int> count_support(vector<vector<string>> data_list);

vector<vector<string>> remove_low_support(vector<vector<string>> data_list, unordered_map<string,int> support_count, int minimum_support_count);

FPTree create_tree(vector<vector<string>> data_list);
#endif