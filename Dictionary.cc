#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;

struct Record
{
    Record(const string &word, int frequency)
    : _word(word)
    , _frequency(frequency)
    {

    }
	string _word;
	int _frequency;
};

class Dictionary
{
public:
    Dictionary(int capa)
    {
        _dict.reserve(capa);//预留空间
    }

    void read(const string &filename)
    {
        ifstream ifs(filename);
        if(!ifs.good())
        {
            cerr << "open " << filename << " error" << endl;
            return;
        }
        //读filename这个文件，然后对每一个单词做处理
        string line;
        while(getline(ifs, line))
        {
            //字符串IO
            istringstream iss(line);
            string word;
            while(iss >> word)
            {
                //word一定是最终要保存的单词吗？hello!  1
                string newWord = dealWord(word);//对老的单词做处理，得到新的单词
                insert(newWord);//将满足条件的单词存在vector中
            }
        }

        ifs.close();
    }

    void store(const string &filename)
    {
        ofstream ofs(filename);
        if(!ofs.good())
        {
            cerr << "open " << filename << " error!" << endl;
            return;
        }

        for(size_t idx = 0; idx != _dict.size(); ++idx)
        {
            ofs << _dict[idx]._word << "      " 
                << _dict[idx]._frequency << endl;
        }

        ofs.close();
    }

    string dealWord(const string &word)
    {
        for(size_t idx = 0; idx != word.size(); ++idx)
        {
            //word!
            /* if((word[idx] >= 'a'&& word[idx] <= 'z') || (word[idx] >= 'A'&& word[idx] <= 'Z')) */
            if(!isalpha(word[idx]))
            {
                return string();//临时对象
            }
        }

        return word;
    }

    void insert(const string &word)
    {
        //判断空串
        if(word == string())
        {
            return ;
        }

        size_t idx = 0;
        for(idx = 0; idx != _dict.size(); ++idx)
        {
            if(word == _dict[idx]._word)
            {
                ++_dict[idx]._frequency;//频率进行++
                break;
            }
        }

        if(idx == _dict.size())
        {
            _dict.push_back(Record(word, 1));//单词第一次出现的代码
        }
    }

private:
	vector<Record> _dict;
};

int main(int argc, char **argv)
{
    Dictionary dictionary(13000);
    cout << "begin reading..." << endl;
    dictionary.read("The_Holy_Bible.txt");
    cout << "end reading..." << endl;
    dictionary.store("dict.dat");
    return 0;
}

