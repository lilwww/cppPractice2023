#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <memory>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::map;
using std::set;
using std::shared_ptr;
using std::string;
using std::vector;

class TextQuery
{
public:
    // 构造函数先分配一定空间的大小
    TextQuery() : _filePtr(new vector<string>())
    {
        _filePtr->reserve(100);
    }

    void readFile(const string &filename);
    void query(const string &word);

private:
    void preProceccLine(string &line);

private:
    // 每次获取一行并存起来
    // vector<string> _file; //lines
    shared_ptr<vector<string>> _filePtr;
    map<string, int> _dict; // word ,freq
    // shared_ptr<map<string, int>>
    map<string, shared_ptr<set<int>>> _word2line; // word, lineNums
};

void TextQuery::readFile(const string &filename)
{
    ifstream ifs(filename);
    if (!ifs)
    {
        cout << "ifstream open " << filename << " error!" << endl;
        return;
    }

    string line;
    size_t lineNumber = 0;
    while (getline(ifs, line))
    {
        // 读一行，并将结果存在vector中(对单词处理前就存起来，存的是原始的)
        _filePtr->push_back(line);

        // 对读取行的单词进行处理
        preProceccLine(line);

        istringstream iss(line);
        string word;
        while (iss >> word)
        {
            // 统计单词与词频
            ++_dict[word];

            // 将单词所在的行记录下来
            _word2line[word]->insert(lineNumber);
        }

        ++lineNumber;
    }

    ifs.close();
}

void TextQuery::query(const string &word)
{
    int count = _dict[word];                                                          // 获取单词出现的次数
    cout << word << " occurs " << count << (count > 1 ? " times" : " time.") << endl; // 打印单词次数

    auto lines = _word2line[word]; // 对同一个单词出现的行进行遍历，输出单词以及行号
    for (auto &number : *lines)
    {
        cout << "    (line " << number + 1 << ") " << (*_filePtr)[number] << endl;
    }
}

void TextQuery::preProceccLine(string &line)
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

int main(int argc, char **argv)
{
    TextQuery tq;
    tq.readFile("china_daily.txt");
    cout << " please input a query word: " << endl;
    string word;
    while (cin >> word)
    {
        tq.query(word);
    }

    return 0;
}
