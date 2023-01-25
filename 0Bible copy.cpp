#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
using namespace std;

/****
已完成
token分割：regex
sortByFreq
sortByAlpha

未优化
分词预处理:全转小写
查找效率:vec用map
sort函数参数加入cmp指针，可由外部自定义cmp

***/
struct Record
{
    string _word;
    int _frequency = 0;
};

class Dictionary
{
public:
    int searchToken(string tk);

    // void sortByFreq(bool sortByFreq = false);
    // bool cmpByFreq(Record a, Record b);
    // bool cmpByAlpha(Record a, Record b);
    void sortByFreq();
    void sortByAlpha();
    void printDic();
    void read(const string &filename);
    vector<string> file2Token(const string &filename);
    void store(const string &filename);

private:
    vector<Record> _dict;
};

// file2Token
vector<string> Dictionary::file2Token(const string &filename)
{
    // string rgx_str = "[0-9\\s\\n\\r-,.?:;'"!']+";
    vector<string> tokens;
    regex rgx("'[s|d|re]|[0-9\\s\\n\\r-,.?:;!]+");
    ifstream ifs(filename);

    if (!ifs)
    {
        cerr << "open " << filename << " error!" << endl;
        return tokens;
    }
    /*ifs-ss-str*/
    stringstream ss;
    ss << ifs.rdbuf();
    string fstr(ss.str());
    ifs.close();
    sregex_token_iterator iter(fstr.begin(), fstr.end(), rgx, -1);
    sregex_token_iterator end;
    while (iter != end)
    {
        tokens.push_back(*iter);
        ++iter;
    }

    return tokens;
}

void Dictionary::read(const string &filename)
{
    vector<string> tokens = file2Token(filename);
    vector<string>::iterator iter;
    for (iter = tokens.begin(); iter != tokens.end(); iter++)
    {
    
        int i = searchToken(*iter); // 对应单词下标
        if (i != -1)
        {
            _dict[i]._frequency++;
        }
        else
        {
            Record newWord{*iter, 1};
            _dict.push_back(newWord);
        }
    }
    cout << "getToken" << endl;
    printDic();
}

int Dictionary::searchToken(string tk)
{
    for (int i = 0; i < _dict.size(); i++)
    {
        if (_dict[i]._word == tk)
        {
            return i;
        }
    }
    return -1; // 未找到
}
bool cmpByAlpha(Record a, Record b)
{
    return (a._word < b._word) || ((a._word == b._word) && (a._frequency > b._frequency));
}
bool cmpByFreq(Record a, Record b)
{
    return (a._frequency > b._frequency) || ((a._frequency == b._frequency) && (a._word < b._word));
}
void Dictionary::sortByFreq()
{

    cout << "sortbyFreq" << endl;
    sort(_dict.begin(), _dict.end(), cmpByFreq);
    printDic();
}
void Dictionary::sortByAlpha()
{
    sort(_dict.begin(), _dict.end(), cmpByAlpha);
    cout << "sortByAlpha" << endl;
    printDic();
    return;
}
void Dictionary::store(const string &filename)
{
    sortByAlpha();
    cout << "toStore" << endl;
    printDic();
    ofstream ofs(filename, std::ios::out);
    if (!ofs)
    {
        cerr << "ofstream is not good!" << endl;
        return;
    }
    vector<Record>::iterator iter;
    for (iter = _dict.begin(); iter != _dict.end(); iter++)
    {
        // 元素内容：加*
        ofs << "[" << iter->_word << "] "
            << iter->_frequency << "   " << endl;
    }

    ofs.close();
    // printDic();
}

void Dictionary::printDic()
{

    vector<Record>::iterator iter;
    int i = 0; // 计数器，一行多数
    for (iter = _dict.begin(); iter != _dict.end(); iter++)
    {
        // 元素内容：加*
        cout << "[" << iter->_word << "] "
             << iter->_frequency << "   ";
        i++;
        if (i == 5)
        {
            cout << endl;
            i = 0;
        }
    }
    cout << endl;
}

void test()
{
    string rfile = "word.txt";
    // string sfile = "word_dic.txt";
    Dictionary *pDic = new Dictionary();
    pDic->read(rfile);
    // pDic->store(sfile);
     pDic->sortByFreq();
     pDic->sortByAlpha();
}
int main()
{
    test();

    return 0;
}