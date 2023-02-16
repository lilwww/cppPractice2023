/********
 * 
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;

//替换掉第一个词出现的词
//working


class strReplace
{
	friend ostream &operator<<(ostream &os, const strReplace &r);

public:
	strReplace(const string &filename)
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
			pair<string, string> r;
			splitRules(line, r);
			_rpRules.insert(r);
		}

		ifs.close();
	}

	void replace(const string &filename)
	{

		fstream fs(filename, ios::in);
		if (!fs)
		{
			cerr << "ofs open " << filename << " error!" << endl;
			return;
		}
		tq.getwdLine1(fs);

		for (auto &rp : _rpRules)
		{
			for (auto &wdInFile : tq.wd_Line1)
			{
				if (rp.first == wdInFile.first)
				{
					string wd = rp.first;
					string line = tq.file[wdInFile.second];

					//split into tokens
					size_t pos = line.find(wd);
					line.erase(pos, wd.size());
					line.insert(pos, rp.second);
					tq.file[wdInFile.second] = line;
					break;
				}
			}
		}
		fs.close();
		//freshWrite(filename);
	}

private:
	void freshWrite(const string &filename)
	{
		ofstream ofs(filename, ios::out);
		for (auto line : tq.file)
		{
			ofs << line.second << endl;
		}
	}
	void splitRules(string &line, pair<string, string> &r)
	{
		size_t i = line.find_first_of(' ');
		r.first = line.substr(0, i);
		r.second = line.substr(i + 1, line.size());
	}
	class TextQuery
	{
		friend class strReplace;
		friend ostream &operator<<(ostream &os, const strReplace &r);

	private:
		void getwdLine1(fstream &is)
		{
			string line;
			size_t lineNum = 0;
			while (getline(is, line))
			{
				file[lineNum] = line;
				preProceccLine(line);
				istringstream iss(line);
				string newWord;
				while (iss >> newWord)
				{
					if (string() != newWord)
					{
						wd_Line1.insert(pair<string, int>(newWord, lineNum));
					}
				}
				lineNum++;
			}
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
		unordered_map<string, int> wd_Line1;
		map<int, string> file;
	};

private:
	unordered_map<string, string> _rpRules;
	TextQuery tq;
};

ostream &operator<<(ostream &os, const strReplace &r)
{
	if (&r)
	{
		os << "##Replace_rules##\n";
		for (auto &i : r._rpRules)
		{
			os <<"[" <<i.first << "] ==> [" << i.second << "]\n";
		}
		os << "##File##\n";
		for (auto &j : r.tq.file)
		{
			os << j.second << endl;
		}
	}
	return os;
}
int main(void)
{
	strReplace rp("replace_rule.txt");
	rp.replace("word1.txt");
	cout << rp;
	return 0;
}
