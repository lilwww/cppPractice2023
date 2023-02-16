#include <iostream>
#include <vector>
#include <deque>
#include <list>

using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::list;

template <typename Container>
void display(const Container &con)
{
    for(auto &elem : con)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

void test()
{
    vector<int> number = {1, 3, 7, 9, 5, 8, 2, 6};
    display(number);
    cout << "number.size() = " << number.size() << endl;
    cout << "number.capacity() = " << number.capacity() << endl;

    cout << endl << "在vector的尾部进行插入与删除" << endl;
    number.push_back(10);
    number.push_back(4);
    display(number);
    number.pop_back();
    display(number);
    cout << "number.size() = " << number.size() << endl;
    cout << "number.capacity() = " << number.capacity() << endl;
    
    cout << endl << "在vector的任意位置进行插入" << endl;
    vector<int>::iterator it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    number.insert(it, 300);
    display(number);
    cout << "*it = " << *it << endl;
    cout << "number.size() = " << number.size() << endl;
    cout << "number.capacity() = " << number.capacity() << endl;

    //对于push_back而言，每次插入元素的个数是一定的，那么每次按照
    //两倍形式进行扩容，肯定容量是够的。但是对于insert而言，每次
    //插入元素的个数是不确定的，所以就没有一个统一的标准进行扩容
    //
    //将capacity() = n, size() = m, 插入元素的个数t;
    //1、t < n - m;就不会发生扩容
    //2、n - m < t < m; 按照2 * m进行扩容
    //3、t > n - m = 6, m = 10 < t < n = 16,按照t + m进行扩容
    //4、t > n - m, t > n,按照t + m进行扩容
    cout << endl;
    number.insert(it, 50, 40);
    display(number);
    cout << "*it = " << *it << endl;
    cout << "number.size() = " << number.size() << endl;
    cout << "number.capacity() = " << number.capacity() << endl;

    cout << endl;
    it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    vector<int> vec = {11, 55, 88, 44};
    number.insert(it, vec.begin(), vec.end());
    display(number);
    cout << "*it = " << *it << endl;
    cout << "number.size() = " << number.size() << endl;
    cout << "number.capacity() = " << number.capacity() << endl;
}

void test2()
{
    vector<int> vec;
    /* 2^64 = 1000 * 1000 * 1000 * 4 */
    for(size_t idx = 1; idx != 100000000; ++idx)
    {
        vec.push_back(idx);
    }
}

int main(int argc, char **argv)
{
    test();

    return 0;
}
