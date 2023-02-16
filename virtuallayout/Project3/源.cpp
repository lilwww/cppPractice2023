
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include "tinyxml2\tinyxml2.h"

using namespace tinyxml2;
using namespace std;

/*
<rss>
	<channel>
		<item>
			 <title>  </title>
			 <link>   </link>
			 <description>   </description>
			 <content>   </content>
		</item>

		<item>
			 <title>  </title>
			 <link>   </link>
			 <description>   </description>
			 <content>   </content>
		</item>
		<item>
		</item>
	</channel>
</rss>
*/
/*
��coolshell.xml�ļ�
rss��channel�ڵ������item�ڵ��title�ڵ㡢link�ڵ��м���ı�
ÿ�ζ�ȡ���������������ʽȥ����ǩ��,����浽vector��
����ȥ���ڶ���item����ʵ����һ��ѭ������������ʵ�ڶ���item�ǵ�һ��item���ֵܽڵ㣨����ʹ��tinyxml2����ĺ���������ת���ڶ���item��
�����Ϳ��Խ���coolshell.xml�ĵ���


���ţ���Ϊdescription��Ϣ�а���html�ı�ǩ��������Ҫȥ��������html��ǩ����<p></p>
�������ʹ���������ʽ��Ҳ����std::regex����ȥ�������������cppreference.html�н��в���ʹ�÷�����

�����Ǳ���vector������ȡ������Ϣ�浽����һ���ļ�����ʽ��Ҫ�Լ����壬ʹ�������Զ����<doc> </doc>��ʽ
*/
struct RssItem
{
	string title;
	string link;
	string description;
	string content;
};

class RssReader
{
public:
	RssReader();
	void parseRss(const string & filename);//����
	void dump(const string & filename);//���
	//tag����
	string tagFilter(const string &desc);
	friend ostream &operator<<(ostream &os, RssReader &rs);
private:
	vector<RssItem> _rss;
};

RssReader::RssReader() {}

void RssReader::dump(const string & filename) {
	const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	XMLDocument doc;
	XMLError ret = doc.Parse(declaration);
	if (ret != 0) {
		cerr << "fail to parse" << filename;
		return;
	}


	XMLComment* comment = doc.NewComment("rss.xml-pageLib.txt");
	doc.InsertEndChild(comment);

	XMLElement* root = doc.NewElement("pageLib");
	doc.InsertEndChild(root);

	// doc
	int i = 1;
	vector<RssItem>::iterator iter = _rss.begin();
	for (iter = _rss.begin(); iter != _rss.end(); iter++) {
		XMLElement* doctag = doc.NewElement("doc");
		root->InsertEndChild(doctag);

		XMLElement* tag = doc.NewElement("docid");

		XMLText* txt = doc.NewText(to_string(i).c_str());
		tag->InsertEndChild(txt);
		doctag->InsertEndChild(tag);

		tag = doc.NewElement("title");
		txt = doc.NewText((iter->title).c_str());
		tag->InsertEndChild(txt);
		doctag->InsertEndChild(tag);

		tag = doc.NewElement("link");
		txt = doc.NewText((iter->link).c_str());
		tag->InsertEndChild(txt);
		doctag->InsertEndChild(tag);

		tag = doc.NewElement("description");
		txt = doc.NewText((iter->description).c_str());
		tag->InsertEndChild(txt);
		doctag->InsertEndChild(tag);

		tag = doc.NewElement("content");
		txt = doc.NewText((iter->content).c_str());
		tag->InsertEndChild(txt);
		doctag->InsertEndChild(tag);
		i++;
	}




	ret = doc.SaveFile(filename.c_str());
	if (ret != 0) {
		cerr << "fail to save" << filename;
		return;
	}

	return;
}
//������������
ostream &operator<<(ostream &os, RssReader &rs) {
	vector<RssItem>::iterator iter = rs._rss.begin();
	for (iter = rs._rss.begin(); iter != rs._rss.end(); iter++) {
		os << "**********************iter->title*********************" << endl
			<< iter->title << endl
			<< "**********************iter->link*********************" << endl
			<< iter->link << endl
			<< "**********************iter->description*********************" << endl
			<< iter->description << endl
			<< "**********************iter->content*********************" << endl
			<< iter->content << endl;
	}
	return os;
}


string RssReader::tagFilter(const string &desc) {
	//������
	regex rgx("<[^>]*>");
	string tmp;
	sregex_token_iterator iter(desc.begin(), desc.end(), rgx, -1);
	sregex_token_iterator end;
	//cout << "**********************DESC*********************" << endl;
	//cout << desc << endl;
	while (iter != end)
	{
		tmp.append(*iter);
		++iter;
	}
	//cout << "**********************TMP*********************" << endl;
	//cout << tmp << endl;
	return tmp;
}
//
void RssReader::parseRss(const string & filename) {
	XMLDocument doc;
	XMLError ret = doc.LoadFile(filename.c_str());
	if (ret != 0) {
		cerr << "fail to load " << filename << endl;
		return;
	}


	//rss
	XMLElement* root = doc.RootElement();

	// channel
	XMLElement* channel = root->FirstChildElement("channel");
	if (!channel) {
		cerr << "no child element: channel" << endl;
		return;
	}


	//item
	XMLElement* item = channel->FirstChildElement("item");
	if (!item) {
		cerr << "no child element: item" << endl;
		return;
	}

	while (item) {
		//������ǩ
		RssItem it;
		it.title = item->FirstChildElement("title")->GetText();
		it.link = item->FirstChildElement("link")->GetText();
		string raw = item->FirstChildElement("description")->GetText();
		it.description = tagFilter(raw);
		raw = item->FirstChildElement("content:encoded")->GetText();
		it.content = tagFilter(raw);


		_rss.push_back(it);
		item = item->NextSiblingElement();//��һ���ֵܽڵ�
	}

	return;
}




void testmyXML()
{
	RssReader rs;
	rs.parseRss("material/coolshell.xml");
	//cout << rs<<endl;
	rs.dump("material/pagelib.txt");

}
int main() {
	testmyXML();
	return 0;
}
