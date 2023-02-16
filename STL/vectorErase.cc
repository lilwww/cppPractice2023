#include <iostream>
#include <vector>

using std::cout;
using std::endl;
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
    vector<int> number = {1, 3, 5, 5, 5, 6, 6, 7, 5, 5};
    display(number);

    //删除所有的元素值为5(不能删除连续重复的元素)
    for(auto it = number.begin(); it != number.end(); ++it)
    {
        if(5 == *it)
        {
            number.erase(it);
        }
    }
    display(number);
}

void test2()
{
    vector<int> number = {1, 3, 5, 5, 5, 6, 6, 7, 5, 5};
    display(number);

    //删除所有的元素值为5
    for(auto it = number.begin(); it != number.end(); )
    {
        if(5 == *it)
        {
            number.erase(it);
        }
        else
        {
            ++it;
        }
    }
    display(number);
}
int main(int argc, char **argv)
{
    test2();
    return 0;
}

