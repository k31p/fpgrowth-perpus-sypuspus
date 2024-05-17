#ifndef csv_H
#define csv_H

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

unordered_map<string, vector<string>> read_csv(string file_name);

#endif