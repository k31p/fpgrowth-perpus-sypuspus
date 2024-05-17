#include "csv.h"

//? HELPER FUNCTION
ifstream open_file(string file_name)
{
    ifstream file(file_name);

    if (!file.is_open()) {
        cerr << "Error Opening File" << endl;
        exit(1);
    }

    return file;
}

vector<string> parse_csv_line(const string& csv_line)
{
    vector<string> tokens;
    string token;
    istringstream ss(csv_line);

    while (getline(ss, token, ';'))
    {
        tokens.push_back(token);
    }
    
    return tokens;
}

//! CONCRETE FUNCTION
unordered_map<string, vector<string>> read_csv(string file_name)
{
    ifstream file = open_file(file_name);

    unordered_map<string, vector<string>> csv_data;
    string input_line;


    while (getline(file, input_line))
    {
        vector parsed_line = parse_csv_line(input_line);

        csv_data["No Peminjam"].push_back(parsed_line[0]);
        csv_data["Kategori"].push_back(parsed_line[1]);
    }

    file.close();
    
    return csv_data;
}
