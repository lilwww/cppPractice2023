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
������ʽR"(\<.+?\>)"�ڴ˵����õȼ���<.+?>,������ƥ������<string>��<char>,string��char�����������һ���ַ�������ƥ������Ϊ0��  .+?�ĺ������������     https://www.jb51.net/article/183106.htm
���ʽ��,\<��\>�е�\������ʾ<��>ֻ��һ��û���κ�������ַ����ٸ�����[xyz]��ʾƥ�京��xyz���ַ�������/[xyz/]��ʾƥ�京��[xyz]���ַ���
R"()������c++11�����ԣ������https://segmentfault.com/a/1190000018903666
*/


void Dictionary::Rssltem(const std::string& filename)
{

	//����
	XMLDocument xml;

	//����xml�ļ�
	if (xml.LoadFile(filename.c_str() != XML_SUCCESS)
	{
		cout << "�����ļ�ʧ��" << endl;
		return;
	}

	cout << "�����ļ��ɹ�" << endl;
	//�ҵ������xml�ĸ��ڵ�
	//
	XMLElement* rootNode = xml.RootElement();
	if (rootNode == NULL)
	{
		cout << "δ�ҵ����ڵ�" << endl;
		return;
	}

	cout << "�ҵ����ڵ�" << endl;
	//��ȡ��һ���ӽڵ���Ϣ����ӡ�ڿ���̨��
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
	cout << "��ȡ���" << endl;

}
void Dictionary::store(const std::string& filename)
{
#ifdef Debug
	cout << "store" << endl;
#endif
	ofstream ofs(filename);
	if (!ofs.good())
	{
		cerr << "���ļ�ʧ��" << endl;
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
	cout << "д�����" << endl;
}
void testhisXML()
{
	Dictionary fieq;
	fieq.Rssltem("material/coolshell.xml");
	fieq.store("material/pagelib2.txt");
}