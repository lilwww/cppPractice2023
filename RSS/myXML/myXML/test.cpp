
#include <iostream>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;
using namespace std;


int createXML(const char* xmlPath = "material/a.xml") {
	const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";
	XMLDocument doc;
	doc.Parse(declaration);//会覆盖xml所有内容

	//添加申明可以使用如下两行
	//XMLDeclaration* declaration=doc.NewDeclaration();
	//doc.InsertFirstChild(declaration);

	XMLElement* root = doc.NewElement("DBUSER");
	doc.InsertEndChild(root);

	return doc.SaveFile(xmlPath);
}
void infoPrint()
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError ret = doc.LoadFile("dream.xml");
	if (ret != 0) {
		fprintf(stderr, "fail to load dream xml file\n");
		return;
	}

	// Structure of the XML file:
	// - Element "PLAY"      the root Element, which is the
	//                       FirstChildElement of the Document
	// - - Element "TITLE"   child of the root PLAY Element
	// - - - Text            child of the TITLE Element

	// Navigate to the title, using the convenience function,
	// with a dangerous lack of error checking.
	const char* title = doc.FirstChildElement("PLAY")->FirstChildElement("TITLE")->GetText();
	printf("Name of play (1): %s\n", title);

	// Text is just another Node to TinyXML-2. The more
	// general way to get to the XMLText:
	XMLText* textNode = doc.FirstChildElement("PLAY")->FirstChildElement("TITLE")->FirstChild()->ToText();
	title = textNode->Value();
	printf("Name of play (2): %s\n", title);
}
int test_tinyxml2_create()
{
	const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError ret = doc.Parse(declaration);
	if (ret != 0) {
		fprintf(stderr, "fail to parse xml file: %s\n", declaration);
		return -1;
	}

	tinyxml2::XMLComment* comment = doc.NewComment("this is a xml test file");
	doc.InsertEndChild(comment);

	tinyxml2::XMLElement* root = doc.NewElement("Root");
	doc.InsertEndChild(root);

	// User
	tinyxml2::XMLElement* user = doc.NewElement("User");
	user->SetAttribute("Name", "fengbingchun");
	root->InsertEndChild(user);

	tinyxml2::XMLElement* blog = doc.NewElement("Blog");
	tinyxml2::XMLText* text1 = doc.NewText("CSDN");
	blog->InsertEndChild(text1);
	user->InsertEndChild(blog);

	tinyxml2::XMLElement* code = doc.NewElement("Code");
	tinyxml2::XMLText* text2 = doc.NewText("GitHub");
	code->InsertEndChild(text2);
	user->InsertEndChild(code);

	// Blog
	tinyxml2::XMLElement* blog2 = doc.NewElement("Blog");
	blog2->SetAttribute("Name", "CSDN");
	root->InsertEndChild(blog2);

	tinyxml2::XMLElement* addr = doc.NewElement("Address");
	tinyxml2::XMLText* text3 = doc.NewText("https://blog.csdn.net/fengbingchun");
	addr->InsertEndChild(text3);
	blog2->InsertEndChild(addr);

	tinyxml2::XMLElement* id = doc.NewElement("ID");
	tinyxml2::XMLText* text4 = doc.NewText("fengbingchun");
	id->InsertEndChild(text4);
	blog2->InsertEndChild(id);

	// Code
	tinyxml2::XMLElement* code2 = doc.NewElement("Code");
	code2->SetAttribute("Name", "GitHub");
	root->InsertEndChild(code2);

	tinyxml2::XMLElement* addr2 = doc.NewElement("Address");
	tinyxml2::XMLText* text5 = doc.NewText("https://github.com//fengbingchun");
	addr2->InsertEndChild(text5);
	code2->InsertEndChild(addr2);

	tinyxml2::XMLElement* repositories = doc.NewElement("Repositories");
	tinyxml2::XMLText* text6 = doc.NewText("27");
	repositories->InsertEndChild(text6);
	code2->InsertEndChild(repositories);

#ifdef _MSC_VER
	const char* file_name = "git.xml";
#else
	const char* file_name = "testdata/test.xml";
#endif

	ret = doc.SaveFile(file_name);
	if (ret != 0) {
		fprintf(stderr, "fail to save xml file: %s\n", file_name);
		return -1;
	}

	return 0;
}


int test_tinyxml2_parse()
{
#ifdef _MSC_VER
	const char* file_name = "material/git.xml";
#else
	const char* file_name = "testdata/test_tinyxml2.xml";
#endif

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError ret = doc.LoadFile("git.xml");
	if (ret != 0) {
		fprintf(stderr, "fail to load xml file: %s\n", file_name);
		return -1;
	}

	tinyxml2::XMLElement* root = doc.RootElement();
	fprintf(stdout, "root element name: %s\n", root->Name());

	// User
	tinyxml2::XMLElement* user = root->FirstChildElement("User");
	if (!user) {
		fprintf(stderr, "no child element: User\n");
		return -1;
	}
	fprintf(stdout, "user name: %s\n", user->Attribute("Name"));

	tinyxml2::XMLElement* blog = user->FirstChildElement("Blog");
	if (!blog) {
		fprintf(stderr, "no child element: Blog, in User\n");
		return -1;
	}
	fprintf(stdout, "blog value: %s\n", blog->GetText());
	fprintf(stdout, "code value: %s\n\n", user->FirstChildElement("Code")->GetText());

	// Blog
	tinyxml2::XMLElement* blog2 = root->FirstChildElement("Blog");
	if (!blog2) {
		fprintf(stderr, "no child element: Blog\n");
		return -1;
	}
	fprintf(stdout, "blog name: %s\n", blog2->Attribute("Name"));

	tinyxml2::XMLElement* addr = blog2->FirstChildElement("Address");
	if (!addr) {
		fprintf(stderr, "no child element: Address, in Blog\n");
		return -1;
	}
	fprintf(stdout, "address value: %s\n", addr->GetText());
	fprintf(stdout, "id value: %s\n\n", blog2->FirstChildElement("ID")->GetText());

	// Code
	tinyxml2::XMLElement* code = root->FirstChildElement("Code");
	if (!code) {
		fprintf(stderr, "no child element: Code\n");
		return -1;
	}
	fprintf(stdout, "code name: %s\n", code->Attribute("Name"));

	tinyxml2::XMLElement* addr2 = code->FirstChildElement("Address");
	if (!addr2) {
		fprintf(stderr, "no child element: Address, in Code\n");
		return -1;
	}
	fprintf(stdout, "address value: %s\n", addr2->GetText());
	fprintf(stdout, "repositories value: %s\n\n", code->FirstChildElement("Repositories")->GetText());

	return 0;
	//
}

void testXML()
{
	//createXML("a.xml");
	//infoPrint();
	//test_tinyxml2_create();
	test_tinyxml2_parse();
}


