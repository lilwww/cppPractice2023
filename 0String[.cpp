#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

// CowString.h
class CowString
{
private:
    class myCh
    {

    private:
        /* data */
        CowString *_s;
        size_t _idx;

    public:
        myCh();
        ~myCh();
        myCh(CowString &s, size_t idx);
        char &operator=(const char &val);
       // char &getCh();
        operator char();
    };

    char *_pstr;
    myCh ch;

public:
    CowString();
    CowString(const char *pstr);
    CowString(const CowString &rhs);

    CowString &operator=(const CowString &rhs);

    CowString::myCh &operator[](size_t idx);

    // 获取引用计数
    int getRefCount() const;
    // 获取底层的指针
    const char *c_str() const;
    ~CowString();

private:
    size_t size() const;
    void initRefCount();
    void increseRefCount();
    void descreRefCount();
    void release();

    friend std::ostream &operator<<(std::ostream &os, const CowString &rhs);
};

// myCh相关实现
CowString::myCh::myCh() {}
CowString::myCh::~myCh() {}
CowString::myCh::operator char()
{
    return _s->_pstr[_idx];
}
CowString::myCh::myCh(CowString &s, size_t idx) : _s(&s), _idx(idx) {}

// ch="d",深拷贝
char &CowString::myCh::operator=(const char &val)
{
    if (_s->getRefCount() > 1) // 共享的
    {
        // 深拷贝
        char *tmp = new char[_s->size() + 5]() + 4;
        strcpy(tmp, _s->_pstr);
        // 原引用计数--
        _s->descreRefCount();

        // 浅拷贝
        _s->_pstr = tmp;
        // 初始化引用计数
        _s->initRefCount();
    }
    _s->_pstr[_idx] = val;
    return _s->_pstr[_idx];
}


// CowString相关实现
CowString::CowString()
    : _pstr(new char[5]() + 4)
{
    cout << "CowString()" << endl;
    initRefCount();
}

CowString::CowString(const char *pstr)
    : _pstr(new char[strlen(pstr) + 5]() + 4)
{
    cout << "CowString(const char *)" << endl;
    strcpy(_pstr, pstr);
    initRefCount();
}

CowString::CowString(const CowString &rhs)
    : _pstr(rhs._pstr)
{
    cout << "CowString(const CowString &)" << endl;
    increseRefCount();
}

CowString &CowString::operator=(const CowString &rhs)
{
    cout << "CowString &operator=(const CowString &)" << endl;
    // 1、自复制
    if (this != &rhs)
    {
        // 2、释放左操作数
        release();

        // 3、浅拷贝
        _pstr = rhs._pstr;
        increseRefCount();
    }

    // 4、返回*this
    return *this;
}

CowString::myCh &CowString::operator[](size_t idx)
{
    if (idx < size())
    {
        ch = myCh(*this, idx);
    }
    else
    {
        ch = (*this, size());
    }
    return ch;
}
CowString::~CowString()
{
    cout << "~CowString()" << endl;
    release();
}

// 获取引用计数
int CowString::getRefCount() const
{
    return *(int *)(_pstr - 4);
}

// 获取底层的指针
const char *CowString::c_str() const
{
    return _pstr;
}

size_t CowString::size() const
{
    return strlen(_pstr);
}

void CowString::initRefCount()
{
    *(int *)(_pstr - 4) = 1;
}

void CowString::increseRefCount()
{
    ++*(int *)(_pstr - 4);
}

void CowString::descreRefCount()
{
    --*(int *)(_pstr - 4);
}

// 释放
void CowString::release()
{
    descreRefCount();
    if (0 == getRefCount())
    {
        delete[] (_pstr - 4);
    }
}

std::ostream &operator<<(std::ostream &os, const CowString &rhs)
{
    if (rhs._pstr)
    {
        os << rhs._pstr;
    }
    return os;
}

// test.cpp
void test()
{
    CowString s1("hello");
    cout << "s1 = " << s1 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    printf("s1'address = %p\n", s1.c_str());

    cout << endl
         << endl;
    CowString s2 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    printf("s1'address = %p\n", s1.c_str());
    printf("s2'address = %p\n", s2.c_str());

    cout << endl
         << endl;
    CowString s3("world");
    cout << "s3 = " << s3 << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;
    printf("s3'address = %p\n", s3.c_str());

    cout << endl
         << endl;
    s3 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;
    printf("s1'address = %p\n", s1.c_str());
    printf("s2'address = %p\n", s2.c_str());
    printf("s3'address = %p\n", s3.c_str());

    cout << endl
         << "对s1[0]执行<<读操作" << endl;
    cout << "s1[0] = " << s1[0] << endl; // cout << s1[0];
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;
    printf("s1'address = %p\n", s1.c_str());
    printf("s2'address = %p\n", s2.c_str());
    printf("s3'address = %p\n", s3.c_str());

    cout << endl
         << "对s3[0]执行=写操作" << endl;
    s3[0] = 'H'; // char = char
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;
    printf("s1'address = %p\n", s1.c_str());
    printf("s2'address = %p\n", s2.c_str());
    printf("s3'address = %p\n", s3.c_str());

    cout << endl
         << "对s1[0]执行=读操作" << endl;
    char a = s1[0];
    cout << "s1[0] = " << s1[0] << " "
         << "a = " << a << endl; // cout << s1[0];
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;
    printf("s1'address = %p\n", s1.c_str());
    printf("s2'address = %p\n", s2.c_str());
    printf("s3'address = %p\n", s3.c_str());
}

int main(int argc, char **argv)
{
    test();
    return 0;
}
