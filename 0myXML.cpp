
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include "tinyxml2/tinyxml2-master/tinyxml2.h"

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
读coolshell.xml文件
rss的channel节点下面的item节点的title节点、link节点中间的文本
每次读取经过后面正则表达式去除标签后,将其存到vector中
后再去读第二个item（其实就是一个循环操作），其实第二个item是第一个item的兄弟节点（可以使用tinyxml2里面的函数进行跳转到第二个item）
这样就可以解析coolshell.xml文档了


接着，因为description信息中包含html的标签，所以需要去除这样的html标签，如<p></p>
这个可以使用正则表达式，也就是std::regex进行去除，这个可以在cppreference.html中进行查找使用方法。

最后就是遍历vector，讲读取到的信息存到另外一个文件，格式需要自己定义，使用我们自定义的<doc> </doc>格式
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
	void parseRss(const string & filename);//解析
	void dump(const string & filename);//输出
	//tag过滤
	string tagFilter(const string &desc);
	friend ostream &operator<<(ostream &os,  RssReader &rs);
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
		cerr<<"fail to save" << filename;
		return;
	}

	return;
}
//不能类内重载
ostream &operator<<(ostream &os,  RssReader &rs) {
	vector<RssItem>::iterator iter = rs._rss.begin();
	for (iter = rs._rss.begin(); iter != rs._rss.end(); iter++) {
		os  << "**********************iter->title*********************" << endl
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
	//正则处理
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
		cerr<<"fail to load " <<filename<<endl;
		return ;
	}


	//rss
	XMLElement* root = doc.RootElement();

	// channel
	XMLElement* channel = root->FirstChildElement("channel");
	if (!channel) {
		cerr<< "no child element: channel"<<endl;
		return;
	}


	//item
	XMLElement* item = channel->FirstChildElement("item");
	if (!item) {
		cerr << "no child element: item" << endl;
		return;
	}

	while (item) {
	//处理标签
		RssItem it;
		it.title = item->FirstChildElement("title")->GetText();
		it.link= item->FirstChildElement("link")->GetText();
		string raw = item->FirstChildElement("description")->GetText();
		it.description = tagFilter(raw);
		raw = item->FirstChildElement("content:encoded")->GetText();
		it.content= tagFilter(raw);


		_rss.push_back(it);
		item = item->NextSiblingElement();//下一个兄弟节点
	}
	
	return ;
}




void testmyXML()
{
	RssReader rs;
	rs.parseRss("coolshell1.xml");
	//cout << rs<<endl;
	rs.dump("pagelib.txt");

}

int main(int argc, char **argv)
{
	testmyXML();
	return 0;
}
