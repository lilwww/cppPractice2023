#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::unordered_map;
using std::ifstream;
using std::istringstream;

const string &transform(const unordered_map<string, string> &um, const string &line)
{
    auto mapIt = um.find(line);

    if(mapIt != um.end())
    {
        return um.find(line)->second;
    }
    else
    {
        return line;
    }
}

const unordered_map<string, string> buildMap(ifstream &ifs)
{
    unordered_map<string, string> um;
    string key;
    string value;

    //使用ifs读取每行需要转换的单词，value存待转换的单词（包括一个空格）
    while(ifs >> key && getline(ifs, value))
    {
        if(value.size() > 1)
        {
            //去除空格
            um[key] = value.substr(1);  
        }
    }

    return um;
}

void trans(ifstream &mapFile, ifstream &input)
{
    auto dictionary = buildMap(mapFile);

    string line;
    string word;
    while(getline(input, line))
    {
        //firstWord要定义在这个地方，否则放在while循环
        //的外部并初始化为true，第二行开始得每行多个空格
        bool firstWord = true;

        //iss也得定义在这个while内，如果定义在这个循环外，
        //则整个循环只有一个内存流is，只能处理一行  
        cout << "line = " << line << endl;
        istringstream iss(line);
        while(iss >> word)
        {
            word = transform(dictionary, word);
            if(firstWord)
            {
                firstWord = false;
            }
            else
            {
                cout << " ";
            }
            cout << word;    
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    ifstream readMap("map.txt");
    ifstream readFile("file2.txt");
    trans(readMap, readFile);

    return 0;
}
