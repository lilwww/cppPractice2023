#include "tinyxml2/tinyxml2.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
using namespace std;
using namespace tinyxml2;
using std::regex;

struct Rss
{
	string title;
	string link;
	string description;
	string content;
};

class Dictionary
{
public:
	void Rssltem(const std::string& filename);
	void store(const std::string& filename);
private:
	vector<Rss> _Rss;
};

string delete_spilth(string line)
{
	regex rx(R"(\<.+?\>|&nbsp;)");
	return  regex_replace(line, rx, "");

}

/*
正则表达式R"(\<.+?\>)"在此的作用等价于<.+?>,大意是匹配所有<string>或<char>,string或char必须存在至少一个字符，否则匹配数量为0。  .+?的含义详见此链接     https://www.jb51.net/article/183106.htm
表达式中,\<和\>中的\用来表示<和>只是一个没有任何意义的字符。举个例子[xyz]表示匹配含有xyz的字符串，而/[xyz/]表示匹配含有[xyz]的字符串
R"()则属于c++11的特性，具体见https://segmentfault.com/a/1190000018903666
*/


void Dictionary::Rssltem(const std::string& filename)
{

	//声明
	XMLDocument xml;

	//导入xml文件
	if (xml.LoadFile(filename.c_str() != XML_SUCCESS)
	{
		cout << "导入文件失败" << endl;
		return;
	}

	cout << "导入文件成功" << endl;
	//找到导入的xml的根节点
	//
	XMLElement* rootNode = xml.RootElement();
	if (rootNode == NULL)
	{
		cout << "未找到根节点" << endl;
		return;
	}

	cout << "找到根节点" << endl;
	//读取第一层子节点信息并打印在控制台上
	XMLElement* root_1_channel = rootNode->FirstChildElement("channel");
	XMLElement* root_2_item = root_1_channel->FirstChildElement("item");

	while (root_2_item)
	{
		Rss rss;
		XMLElement* root_3_title = root_2_item->FirstChildElement("title");
		string title = root_3_title->GetText();
		rss.title = title;

		XMLElement* root_3_link = root_2_item->FirstChildElement("link");
		string link = root_3_link->GetText();
		rss.link = link;

		XMLElement* root_3_description = root_2_item->FirstChildElement("description");
		string descr = root_3_description->GetText();
		rss.description = delete_spilth(descr);

		_Rss.push_back(rss);

		root_2_item = root_2_item->NextSiblingElement("item");
	}
	cout << "读取完毕" << endl;

}
void Dictionary::store(const std::string& filename)
{
#ifdef Debug
	cout << "store" << endl;
#endif
	ofstream ofs(filename);
	if (!ofs.good())
	{
		cerr << "打开文件失败" << endl;
	}

	int size = _Rss.size();
	for (int i = 0; i < size; ++i)
	{

		char str_c[32] = { 0 };
		sprintf_s(str_c, sizeof(str_c), "%d", i + 1);
		ofs << "<doc>" << endl;;
		ofs << "    " << "<docid>" << str_c << "</docid>" << endl;;
		ofs << "    " << "<title>" << _Rss[i].title << "</title>" << endl;;
		ofs << "    " << "<link>" << _Rss[i].link << "</link>" << endl;;
		ofs << "    " << "<description>" << _Rss[i].description << "</description>" << endl;;
		ofs << "    " << "<content>" << _Rss[i].content << "</content>" << endl;;
		ofs << "    " << "</doc>" << endl;;
		ofs << endl;
	}
	cout << "写入结束" << endl;
}
void testhisXML()
{
	Dictionary fieq;
	fieq.Rssltem("material/coolshell.xml");
	fieq.store("material/pagelib2.txt");
}