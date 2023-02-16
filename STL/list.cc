#include <iostream>
#include <list>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::vector;


template <typename Container>
void display(const Container &con)
{
    for (auto &elem : con)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

// 函数对象
template <class T>
class CompareList
{
public:
    bool operator()(const T &lhs, const T &rhs) const
    {
        //cout << "bool operator()(const T &, const T &) const" << endl;
        return lhs < rhs;
    }
};
void testcmp()
{
    list<int> number = {3, 5, 7, 9, 8, 8, 5, 10, 300, 8};
    display(number);

    cout << endl
         << "测试unique函数" << endl;
    number.unique();
    display(number);

    cout << endl
         << "测试reverse函数" << endl;
    number.reverse();
    display(number);

    cout << endl
         << "测试sort函数" << endl;
    number.sort();
    /* std::less<int> les; */
    /* number.sort(les); */
    /* number.sort(std::less<int>()); */
    /* number.sort(std::greater<int>()); */
    number.sort(CompareList<int>());
    display(number);
}
void test()
{
    list<int> number = {3, 5, 7, 9, 8, 8, 5, 10, 300, 8};
    display(number);

    cout << endl
         << "测试unique函数" << endl;
    number.unique();
    display(number);

    cout << endl
         << "测试reverse函数" << endl;
    number.reverse();
    display(number);

    cout << endl
         << "测试sort函数" << endl;
    number.sort();
    /* std::less<int> les; */
    /* number.sort(les); */
    /* number.sort(std::less<int>()); */
    /* number.sort(std::greater<int>()); */
    /*number.sort(CompareList<int>()); */
    display(number);

    cout << endl
         << "测试unique函数" << endl;
    number.unique();
    display(number);

    cout << endl
         << "测试merge函数" << endl;
    list<int> number2 = {30, 50, 4, 6, 2};
    number2.sort(); // 先排序
    /* number.sort(std::greater<int>());//先排序 */
    /* number2.sort(std::greater<int>());//先排序 */
    /* display(number); */
    display(number2);
    number.merge(number2);
    display(number);
    display(number2);

    cout << endl
         << "测试splice函数" << endl;
    list<int> number3 = {444, 888, 999, 111, 333};
    display(number3);
    auto it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    number.splice(it, number3);
    display(number);
    display(number3);

    cout << endl
         << endl
         << "测试splice........" << endl;
    list<int> number4 = {1000, 8000, 9000, 6000, 3000};
    display(number4);
    it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    auto it2 = number4.begin();
    ++it2;
    ++it2;
    cout << "*it2 = " << *it2 << endl;
    number.splice(it, number4, it2);
    display(number);
    display(number4);

    cout << endl
         << endl
         << "----------" << endl;
    it = number.begin();
    ++it;
    ++it;
    it2 = number4.begin();
    auto it3 = number4.end();
    --it3;
    --it3;
    cout << "*it = " << *it << endl;
    cout << "*it2 = " << *it2 << endl;
    cout << "*it3 = " << *it3 << endl;
    number.splice(it, number4, it2, it3); //[it2, it3)
    display(number);
    display(number4);

    cout << endl
         << "测试splice的别致用法" << endl;
    list<int> numberList =
        {1, 3, 5, 7, 9, 8, 6, 100, 300, 600};
    display(numberList);
    auto it4 = numberList.begin();
    ++it4;
    ++it4;
    cout << "*it4 = " << *it4 << endl;
    auto it5 = numberList.end();
    --it5;
    --it5;
    cout << "*it5 = " << *it5 << endl;
    numberList.splice(it4, numberList, it5);
    display(numberList);
}

int main(int argc, char **argv)
{
    testcmp();
    return 0;
}
