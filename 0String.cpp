#include <iostream>
#include <string.h>
using namespace std;

class String
{
public:
    String();
    String(const char *);
    String(const String &);
    ~String();
    String &operator=(const String &);
    String &operator=(const char *);

    String &operator+=(const String &);
    String &operator+=(const char *);

    char &operator[](std::size_t index);
    const char &operator[](std::size_t index) const;

    std::size_t size() const;
    const char *c_str() const;

    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    char *_pstr;
};

String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);

// 成员实现
String::String() {}
String::String(const char *s)
{
    _pstr = new char[strlen(s) + 1]();
    strcpy(_pstr, s);
}

String::String(const String &s) : _pstr(s._pstr) {}
String::~String()
{
    if (_pstr)
    {
        delete[] _pstr;
        _pstr = nullptr;
    }
}

String &String::operator=(const String &s)
{
    if (this != &s)
    {
        delete[] _pstr;
        _pstr = nullptr;
        _pstr = new char[strlen(s._pstr) + 1]();
        strcpy(_pstr, s._pstr);
    }

    return *this;
}
String &String::operator=(const char *s)
{
    if (s != _pstr) // 同
    {
        delete _pstr;
        _pstr = nullptr;
        _pstr = new char[strlen(s) + 1]();
        strcpy(_pstr, s);
    }
    return *this;
}

String &String::operator+=(const String &s)
{
    strcat(_pstr, s._pstr);
    return *this;
}
String &String::operator+=(const char *s)
{
    strcat(_pstr, s);
    return *this;
}

char &String::operator[](std::size_t index)
{
    int sz = size();
    if (index >= sz)
    {
        cout << "index invalid" << endl;
        return _pstr[sz]; // "/0"
    }

    return _pstr[index];
}
const char &String::operator[](std::size_t index) const
{
    int sz = size();
    if (index >= sz)
    {
        cout << "index invalid" << endl;
        return _pstr[sz]; // "/0"
    }

    return _pstr[index];
}

std::size_t String::size() const
{
    return strlen(_pstr);
}
const char *String::c_str() const
{
    // 回收问题
    char *ch = new char[strlen(_pstr) + 1];
    strcpy(ch, _pstr);
    return ch;
}

// 友元
bool operator==(const String &s1, const String &s2)
{
    return s1._pstr == s2._pstr;
}
bool operator!=(const String &s1, const String &s2)
{
    return !(s1._pstr == s2._pstr);
}
bool operator<(const String &s1, const String &s2)
{
    return s1._pstr < s2._pstr;
}

bool operator>(const String &s1, const String &s2)
{
    return s1._pstr > s2._pstr;
}
bool operator<=(const String &s1, const String &s2)
{
    return !(s1._pstr > s2._pstr);
}
bool operator>=(const String &s1, const String &s2)
{
    return !(s1._pstr < s2._pstr);
}
ostream &operator<<(std::ostream &os, const String &s)
{
    os << s._pstr << " ";
    return os;
}

istream &operator>>(std::istream &is, String &s)
{
    is >> s._pstr;
    return is;
}





// 普通函数

void basicTest()
{
    String s("lili");
    cout << s.size() << endl;
    cout << s.c_str() << endl;

    String s1 = s;
    cout << s1;
    String s2(s);
    cout << s;
    cin >> s2;
    cout << s2;

    const char *ch = {"amy"};
    s = ch;
    cout << s << endl;
}
void cmpTest()
{
    String s1("lili");
    String s2("jay");
    String s3(s1);
    cout << s1 << s2 << s3 << endl;
    cout << "?s1>s2 " << (s1 > s2) << endl;
    cout << "?s1!=s2 " << (s1 != s2) << endl;
    cout << "?s1>=s2 " << (s1 >= s2) << endl;

    cout << "?s1==s3 " << (s1 == s3) << endl;
    cout << "?s1<=s3 " << (s1 <= s3) << endl;
    cout << "?s1<s3 " << (s1 < s3) << endl;
}
int main()
{
    basicTest();
    cmpTest();
    return 0;
}