#include <time.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::map;
using std::ofstream;
using std::pair;
using std::string;

class Dictionary
{
public:
    void read1(const string &filename)
    {
        ifstream ifs(filename);
        if (!ifs)
        {
            cerr << "ifs open " << filename << " error!" << endl;
            return;
        }

        string line;
        while (getline(ifs, line))
        {
            istringstream iss(line);
            string word;
            while (iss >> word)
            {
                string newWord = dealWord(word);
                if (string() != newWord)
                {
                    ++_map[newWord];
                }
            }
        }

        ifs.close();
    }

    void read(const string &filename)
    {
        ifstream ifs(filename);
        if (!ifs)
        {
            cerr << "ifs open " << filename << " error!" << endl;
            return;
        }

        string line;
        while (getline(ifs, line))
        {
            preProceccLine(line);
            istringstream iss(line);
            string newWord;
            while (iss >> newWord)
            {
                
                if (string() != newWord)
                {
                    ++_map[newWord];
                }
            }
        }

        ifs.close();
    }

    void store(const string &filename)
    {
        ofstream ofs(filename);
        if (!ofs)
        {
            cerr << "ofs open " << filename << " error!" << endl;
            return;
        }

        map<string, int>::iterator it;
        for (it = _map.begin(); it != _map.end(); ++it)
        {
            ofs << it->first << "  " << it->second << endl;
        }

        ofs.close();
    }

private:
    string dealWord(const string &word)
    {
        // 查看获取到的字符串是不是单词：标点符号，true1都不算
        for (size_t idx = 0; idx != word.size(); ++idx)
        {
            if (!isalpha(word[idx]))
            {
                // 如果存在标点，数字等不算单词，返回空串
                return string();
            }
        }

        // 转换为合理的单词
        return word;
    }

    void preProceccLine(string &line)
    {
        for (auto &ch : line)
        {
            if (!isalpha(ch)) // 处理单词，如果不是字母就用空格代替abc? abc123 Hello
            {
                ch = ' ';
            }
            else if (isupper(ch)) // 如果是大写就转为小写
            {
                ch = tolower(ch);
            }
        }
    }

private:
    map<string, int> _map;
};

int main(void)
{
    cout << "before reading..." << endl;
    Dictionary dictionary;
    time_t beg = time(NULL);
    dictionary.read("The_Holy_Bible.txt");
    time_t end = time(NULL);
    cout << "time: " << (end - beg) << "s" << endl;
    cout << "aftre reading..." << endl;
    dictionary.store("dictMap_preProccess.dat");
    return 0;
}
