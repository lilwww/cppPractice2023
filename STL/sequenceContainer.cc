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

class Point
{
public:
    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {
        cout << "Point(int = 0, int = 0)" << endl;
    }

    void print() const
    {
        cout << "(" << _ix
             <<", "<< _iy
             << ")" << endl;
    }

private:
    int _ix;
    int _iy;
};

void test00()
{
    vector<Point> vec;
    vec.push_back(Point(1, 2));
    vec.emplace_back(3, 4);//Point(3, 4)
}

void test()
{
    cout << "sizeof(vector<int>) = " << sizeof(vector<int>) << endl;
    cout << "sizeof(vector<double>) = " << sizeof(vector<double>) << endl;
    cout << "sizeof(vector<long>) = " << sizeof(vector<long>) << endl;

    cout << endl;
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
    
    //vector为何不支持在头部进行插入与删除呢？
    //vector是一端开口的，如果在头部插入一个元素，那么会将后面
    //所有的元素都后移一位，然后将最开始的位置空出来，存新插入
    //的元素。如果在头部进行删除的话，后面的元素都要向前挪动
    //一个，这样时间复杂度就是O(N)，效率比较低
    //
    //如何获取vector的第一个元素的地址？
    /* &number;//error获取不是第一个元素的地址 */
    /* &*number;//error,语法报错 */
    &*number.begin();//ok
    &number[0];//ok

    int *pdata = number.data();//ok

    cout << endl << "在vector的任意位置进行插入" << endl;
    //重新置位迭代器
    vector<int>::iterator it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    //1、在某个位置插入一个元素
    number.insert(it, 300);
    display(number);
    cout << "*it = " << *it << endl;
    cout << "number.size() = " << number.size() << endl;
    cout << "number.capacity() = " << number.capacity() << endl;

    cout << endl;
    //2、在某个位置插入count个元素
    //重新置位迭代器
    it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    number.insert(it, 5, 40);
    display(number);
    cout << "*it = " << *it << endl;
    cout << "number.size() = " << number.size() << endl;
    cout << "number.capacity() = " << number.capacity() << endl;

    cout << endl;
    vector<int> vec = {11, 55, 88, 44};
    //3、在某个位置插入迭代器范围的元素
    //重新置位迭代器
    it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    number.insert(it, vec.begin(), vec.end());
    display(number);
    cout << "*it = " << *it << endl;
    cout << "number.size() = " << number.size() << endl;
    cout << "number.capacity() = " << number.capacity() << endl;

    cout << endl;
    //4、在某个位置插入迭代器范围的元素
    //重新置位迭代器
    it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    number.insert(it, {200, 600, 500, 300});
    display(number);
    cout << "*it = " << *it << endl;
    number.shrink_to_fit();//回收多余的空间
    cout << "number.size() = " << number.size() << endl;
    cout << "number.capacity() = " << number.capacity() << endl;

    cout << endl << "vector元素的清空" << endl;
    number.clear();//清空元素
    number.shrink_to_fit();//回收多余的空间
    cout << "number.size() = " << number.size() << endl;
    cout << "number.capacity() = " << number.capacity() << endl;
}

void test2()
{
    deque<int> number = {1, 3, 7, 9, 5, 8, 2, 6};
    display(number);

    cout << endl << "在deque的尾部进行插入与删除" << endl;
    number.push_back(10);
    number.push_back(4);
    display(number);
    number.pop_back();
    display(number);

    cout << endl << "在deque的头部进行插入与删除" << endl;
    number.push_front(100);
    number.push_front(400);
    display(number);
    number.pop_front();
    display(number);

    cout << endl << "在deque的任意位置进行插入" << endl;
    deque<int>::iterator it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    //1、在某个位置插入一个元素
    number.insert(it, 300);
    display(number);
    cout << "*it = " << *it << endl;

    cout << endl;
    //2、在某个位置插入count个元素
    number.insert(it, 5, 40);
    display(number);
    cout << "*it = " << *it << endl;

    cout << endl;
    vector<int> vec = {11, 55, 88, 44};
    //3、在某个位置插入迭代器范围的元素
    number.insert(it, vec.begin(), vec.end());
    display(number);
    cout << "*it = " << *it << endl;

    cout << endl;
    //4、在某个位置插入迭代器范围的元素
    number.insert(it, {200, 600, 500, 300});
    display(number);
    cout << "*it = " << *it << endl;

    cout << endl << "deque元素的清空" << endl;
    number.clear();//清空元素
    number.shrink_to_fit();//回收多余的空间
    cout << "number.size() = " << number.size() << endl;
}

void test3()
{
    list<int> number = {1, 3, 7, 9, 5, 8, 2, 6};
    display(number);

    cout << endl << "在list的尾部进行插入与删除" << endl;
    number.push_back(10);
    number.push_back(4);
    display(number);
    number.pop_back();
    display(number);

    cout << endl << "在list的头部进行插入与删除" << endl;
    number.push_front(100);
    number.push_front(400);
    display(number);
    number.pop_front();
    display(number);

    cout << endl << "在list的任意位置进行插入" << endl;
    list<int>::iterator it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    //1、在某个位置插入一个元素
    number.insert(it, 300);
    display(number);
    cout << "*it = " << *it << endl;

    cout << endl;
    //2、在某个位置插入count个元素
    number.insert(it, 5, 40);
    display(number);
    cout << "*it = " << *it << endl;

    cout << endl;
    vector<int> vec = {11, 55, 88, 44};
    //3、在某个位置插入迭代器范围的元素
    number.insert(it, vec.begin(), vec.end());
    display(number);
    cout << "*it = " << *it << endl;

    cout << endl;
    //4、在某个位置插入迭代器范围的元素
    number.insert(it, {200, 600, 500, 300});
    display(number);
    cout << "*it = " << *it << endl;

    cout << endl << "list元素的清空" << endl;
    number.clear();//清空元素
    cout << "number.size() = " << number.size() << endl;
}

int main(int argc, char **argv)
{
    cout << "测试vector..." << endl;
    test();

    cout << endl << "测试deque..." << endl;
    test2();

    cout << endl << "测试list..." << endl;
    test3();

    return 0;
}

