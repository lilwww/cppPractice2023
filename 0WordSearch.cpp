/*
将读取用户指定的任意文本文件【当前目录下的china_daily.txt】，然后允许用户从该文件中查找单词
查询的结果是该单词出现的次数，并列出每次出现所在的行。如果某单词在同一行中多次出现，程序将只显示该行一次。行号按升序显示。

要求：
a、filename
b、line context,line number
c、它必须将每一行分解为各个单词，并记录每个单词所在的所有行。在输出行号时，应保证以升序输出，并且不重复。

map<string, set<int> > _word2Numbers;
map<string, int> _dict;


d、对特定单词的查询将返回出现该单词的所有行的行号。
e、输出某单词所在的行文本时，程序必须能根据给定的行号从输入文件中获取相应的行。
​		示例：

使用提供的文件内容，然后查找单词 "element"。输出的前几行为
element occurs 125 times.
   (line 62) element with a given key.
   (line 64) second element with the same key.
   (line 153) element |==| operator.
   (line 250) the element type.

(line 398) corresponding element.
//程序测试用例
int main(int argc, char *argv[])
{
   string  queryWord("hello");

   TextQuery tq;
   tq.readFile("test.dat");
   tq.query(queryWord);

   return 0;
}
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <regex>
#include <algorithm>
using namespace std;

class TextQuery
{

public:
   // 内部类，查询结果，将查询和打印解耦
   class QueryResult
   {
   private:
      pair<string, set<int>> _word2Numbers;
      map<int, string> _lines2print;
      TextQuery *_tq;
      bool isFound;

   public:
      QueryResult(const string &word);
      QueryResult(TextQuery *tq, pair<string, set<int>> w2Num);
      void prtRes();
   };
   // File2Lines
   void readFile(const string filename);
   //
   QueryResult query(const string &word);
   void token2dict(const string &word, const int &ln);
   string dealWord(string &word);
   void printLn();
   void printNum();
   void printWd();
   void printAll();

private:
   void addLineNum(const string &word, const int &ln);
   vector<string> _lines;
   map<string, set<int>> _word2Numbers;
   map<string, int> _dict;
};

void TextQuery::readFile(const string filename)
{
   // open file
   ifstream ifs(filename);
   if (!ifs)
   {
      cerr << "open " << filename << " error!" << endl;
      return;
   }

   string line;
   // string rgx_str = "'[s|d|re]|[0-9\\s\\n\\r-,.?:;!]+";
   // regex rgx(rgx_str);
   int lineNum = 0;
   map<string, int> wdNLine;
   while (getline(ifs, line))
   {

      _lines.push_back(line);
      istringstream iss(line);
      string word;
      while (iss >> word)
      {
         string newWord = dealWord(word); // 对老的单词做处理，得到新的单词
         token2dict(newWord, lineNum);    // 将满足条件的单词存在vector中
      }

      lineNum++;
   }

   return;
}

string TextQuery::dealWord(string &word)
{
   for (size_t idx = 0; idx != word.size(); ++idx)
   {
      // word!
      /* if((word[idx] >= 'a'&& word[idx] <= 'z') || (word[idx] >= 'A'&& word[idx] <= 'Z')) */
      char c = word[idx];
      if (!isalpha(c))
      {
         if (c == '.' || '?' || '!' || "'")
         {
            word = word.substr(0, idx);
            return word;
         }
         return string(); // 临时对象
      }
   }

   return word;
}

void TextQuery::token2dict(const string &word, const int &ln)
{
   if (word.empty())
      return;

   map<string, int>::iterator iter;

   for (iter = _dict.begin(); iter != _dict.end(); iter++)
   {
      if (iter->first == word)
      { // 找到
         iter->second++;
         break;
      }
   }
   if (iter == _dict.end())
   {
      _dict.insert(pair<string, int>(word, 1));
   }
   addLineNum(word, ln);
   return;
}

TextQuery::QueryResult TextQuery::query(const string &word)
{
   map<string, set<int>>::iterator iter;
   for (iter = _word2Numbers.begin(); iter != _word2Numbers.end(); iter++)
   {
      if (iter->first == word)
      { // 找到
         return QueryResult(this, *iter);
      }
   }
   return QueryResult(word);
}
void TextQuery::addLineNum(const string &word, const int &ln)
{
   map<string, set<int>>::iterator iter;

   for (iter = _word2Numbers.begin(); iter != _word2Numbers.end(); iter++)
   {
      if (iter->first == word)
      { // 找到
         iter->second.insert(ln);
         return;
      }
   }
   if (iter == _word2Numbers.end())
   {
      set<int> lines = {ln};
      _word2Numbers.insert(pair<string, set<int>>(word, lines));
   }
}
void TextQuery::printLn()
{
   cout << "*******Line Content*******" << endl;
   vector<string>::iterator iterLn;

   for (iterLn = _lines.begin(); iterLn != _lines.end(); iterLn++)
   {
      cout << *iterLn << endl;
   }
}
void TextQuery::printNum()
{
   cout << "*******Wd&LineNum*******" << endl;
   vector<string>::iterator iterLn;
   map<string, set<int>>::iterator iterNum;
   map<string, int>::iterator iterWd;
   for (iterNum = _word2Numbers.begin(); iterNum != _word2Numbers.end(); iterNum++)
   {
      cout << iterNum->first << " ";
      set<int>::iterator iterSet;
      for (iterSet = iterNum->second.begin(); iterSet != iterNum->second.end(); iterSet++)
      {
         cout << *iterSet << " ";
      }
      cout << endl;
   }
}

void TextQuery::printWd()

{
   cout << "*******Wd&Freq*******" << endl;

   map<string, int>::iterator iterWd;
   for (iterWd = _dict.begin(); iterWd != _dict.end(); iterWd++)
   {
      cout << iterWd->first << " " << iterWd->second << endl;
   }
}
void TextQuery::printAll()
{
   printLn();
   printNum();
   printWd();
}

//QueryResult 方法

TextQuery::QueryResult::QueryResult(const string &word)
{
   _word2Numbers.first = word;
   isFound = false;
}

TextQuery::QueryResult::QueryResult(TextQuery *tq, pair<string, set<int>> w2Num) : _tq(tq), _word2Numbers(w2Num)
{
   isFound = true;
   set<int>::iterator iter;
   for (iter = _word2Numbers.second.begin(); iter != _word2Numbers.second.end(); iter++)
   {
      // line2print
      _lines2print.insert(pair<int, string>(*iter, tq->_lines[*iter]));
   }
}

void TextQuery::QueryResult::prtRes()
{
   /*
   element occurs 125 times.
   (line 62) element with a given key.
   (line 64) second element with the same key.
   (line 153) element |==| operator.
   (line 250) the element type.

(line 398) corresponding element.*/
   cout << _word2Numbers.first << " ";
   if (!isFound)
   {
      cout << "NOT FOUND" << endl;
      return;
   }
   else
   {
      // 次数
      int cnt = _word2Numbers.second.size();
      cout << "occurs " << _word2Numbers.second.size() << " time";
      if (cnt > 1)
         cout << "s" << endl;
      else
         cout << endl;

      map<int, string>::iterator iter;
      for (iter = _lines2print.begin(); iter != _lines2print.end(); iter++)
      {
         cout << "(line " << iter->first + 1 << ") "
              << iter->second
              << endl;
      }
   }
}
// 程序测试用例
int main(int argc, char *argv[])
{

   TextQuery tq;
   tq.readFile("china_daily.txt");
   //tq.printLn();
   //tq.printWd();
   string queryWord("all");
   tq.query(queryWord).prtRes();

   return 0;
}
