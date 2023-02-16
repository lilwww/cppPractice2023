#include <math.h>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::set;
using std::pair;
using std::vector;

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
    //set的特征
    //1、元素是唯一的，不能重复
    //2、默认情况下，会按照key值升序排列（从小到大）
    //3、底层使用的是红黑树结构
    set<int> number = {1, 3, 5, 7, 9, 7, 5, 3, 1, 100};
    /* set<int, std::greater<int>> number = {1, 3, 5, 7, 9, 7, 5, 3, 1, 100}; */
    display(number);

    cout << endl << "set的查找操作" << endl;
    size_t cnt1 = number.count(1);
    size_t cnt2 = number.count(10);
    cout << "cnt1 = " << cnt1 << endl;
    cout << "cnt2 = " << cnt2 << endl;

    cout << endl;
    /* auto it = number.find(8); */
    set<int>::iterator it = number.find(8);
    if(it == number.end())
    {
        cout << "该元素不存在set中" << endl;
    }
    else
    {
        cout << "该元素存在set中 = "<< *it << endl;
    }

    cout << endl << "set的insert操作" << endl;
    //1、插入一个元素
    pair<set<int>::iterator, bool> ret = number.insert(8);
    if(ret.second)
    {
        cout << "插入成功 " << *ret.first << endl;
    }
    else
    {
        cout << "插入失败" << endl;
    }
    display(number);

    cout << endl << endl;
    //2、插入迭代器范围的
    vector<int> vec = {2, 11, 6, 3, 8, 29, 200};
    number.insert(vec.begin(), vec.end());
    display(number);

    cout << endl << endl;
    //3、大括号的形式
    number.insert({4, 22, 88, 66, 3, 4, 7, 10});
    display(number);

    cout << endl << "set的删除操作" << endl;
    it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    number.erase(it);
    display(number);
    
    cout << endl << "set的下标操作" << endl;
    /* cout << "number[4] = " << number[4] << endl;//error，不支持下标 */

    cout << endl << "set的修改操作" << endl;
    it = number.begin();
    ++it;
    cout << "*it = " << *it << endl;
    /* *it = 300;//不能进行修改 */
}

class Point
{
public:
    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {
        /* cout << "Point(int = 0, int = 0)" << endl; */
    }

    double getDistance() const
    {
        return hypot(_ix, _iy);
    }

    ~Point()
    {
        /* cout << "~Point()" << endl; */
    }

    int getX() const
    {
        return _ix;
    }

    int getY() const
    {
        return _iy;
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &rhs);
    friend bool operator<(const Point &lhs, const Point &rhs);
    friend struct ComparePoint;//友元

private:
    int _ix;
    int _iy;
};

std::ostream &operator<<(std::ostream &os, const Point &rhs)
{
    os << "(" << rhs._ix
       <<", "<< rhs._iy
       << ")";

    return os;
}

//针对两个Point进行比较，重载operator<
bool operator<(const Point &lhs, const Point &rhs)
{
    cout << "bool operator<(const Point &, const Point &)" << endl;
    if(lhs.getDistance() < rhs.getDistance())
    {
        return true;
    }
    else if(lhs.getDistance() == rhs.getDistance())
    {
        if(lhs._ix < rhs._ix)
        {
            return true;
        }
        else if(lhs._ix == rhs._ix)
        {
            if(lhs._iy < rhs._iy)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

//函数对象（伪函数）
struct ComparePoint
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        cout << "bool operator()(const Point &, const Point &) const" << endl;
        if(lhs.getDistance() < rhs.getDistance())
        {
            return true;
        }
        else if(lhs.getDistance() == rhs.getDistance())
        {
            if(lhs._ix < rhs._ix)
            {
                return true;
            }
            else if(lhs._ix == rhs._ix)
            {
                if(lhs._iy < rhs._iy)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};

//命名空间的扩展
namespace  std
{
//模板的特化
template <>
struct less<Point>
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        cout << "bool struct less::operator()(const Point &, const Point &) const" << endl;
        return lhs < rhs;
#if 0
        if(lhs.getDistance() < rhs.getDistance())
        {
            return true;
        }
        else if(lhs.getDistance() == rhs.getDistance())
        {
            if(lhs.getX() < rhs.getX())
            {
                return true;
            }
            else if(lhs.getX() == rhs.getX())
            {
                if(lhs.getY() < rhs.getY())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
#endif
    }

};
}//end of namespace std

void test2()
{
    /* set<Point> number = { */
    set<Point, ComparePoint> number = {
        Point(1, 2),
        Point(1, -2),
        Point(-1, 2),
        Point(1, 2),
        Point(3, 2),
        Point(-5, 2),
        Point(3, 2)
    };
    display(number);
}
int main(int argc, char **argv)
{
    test2();
    return 0;
}

