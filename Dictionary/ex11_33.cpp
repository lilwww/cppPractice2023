//
//  ex11_33.cpp
//  Exercise 11.33
//
//  Created by pezy on 12/18/14.
//
//  Implement your own version of the word-transformation program.

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using std::ifstream;
using std::string;

std::map<string, string> buildMap(ifstream &map_file)
{
    std::map<string, string> trans_map;
    for (string key, value; map_file >> key && getline(map_file, value);)
        if (value.size() > 1)
            trans_map[key] = value.substr(0).substr(0, value.find_last_not_of(' '));
    return trans_map;
}

const string &transform(const string &s, const std::map<string, string> &m)
{
    // word-key
    auto map_it = m.find(s);
    return map_it == m.cend() ? s : map_it->second;
}

void word_transform(ifstream &map, ifstream &input)
{
    auto trans_map = buildMap(map);
    for (string text; getline(input, text);)
    {
        // rm whitespace
        std::istringstream iss(text);
        for (string word; iss >> word;)
            std::cout << transform(word, trans_map) << " ";
        std::cout << std::endl;
    }
}

int main()
{
    ifstream ifs_map("replace_rule.txt"), ifs_content("word1.txt");
    if (ifs_map && ifs_content)
        word_transform(ifs_map, ifs_content);
    else
        std::cerr << "can't find the documents." << std::endl;
}
v