#include <math.h>
#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;
using std::function;

//要实现多态，可以使用以下两种方法
//面向对象的思维方式：虚函数 + 继承(面向对象的方式)
//面向过程的思维方式：std::bind + std::function(回调函数的注册与执行)(基于对象的方法)
//
class Figure
{
public:
    //C++11的标准进行重新定义
    using DisplayCallback = function<void()>;
    using AreaCallback = function<double()>;

    //回调函数的设计思想：回调函数的注册与执行
    //回调函数的注册
    void setDisplayCallback(DisplayCallback &&cb)
    {
        _displayCallback = std::move(cb);
    }

    void setAreaCallback(AreaCallback &&cb)
    {
        _areaCallback = std::move(cb);
    }
    
    //回调函数的执行
    void handlDisplayCallback() const
    {
        if(_displayCallback)
        {
            _displayCallback();
        }
    }

    double handlAreaCallback() const
    {
        if(_areaCallback)
        {
            return _areaCallback();
        }
        else
        {
            return 0.0;
        }
    }

private:
    DisplayCallback _displayCallback;
    AreaCallback _areaCallback;
};

class Rectangle
{
public:
    Rectangle(double length = 0, double width = 0)
    : _length(length)
    , _width(width)
    {
        cout << "Rectangle(double = 0, double = 0)" << endl;
    }

    void display(int x) const 
    {
        cout << "Rectangle";
    }

    double area() const 
    {
        return _length * _width;
    }

    ~Rectangle()
    {
        cout << "~Rectangle()" << endl;
    }
private:
    double _length;
    double _width;
};

class Circle
{
public:
    Circle(double radius = 0)
    : _radius(radius)
    {
        cout << "Circle(double = 0)" << endl;
    }

    void print() const 
    {
        cout << "Circle";
    }

    double printArea() const 
    {
        return 3.14 * _radius *_radius;;
    }

    ~Circle()
    {
        cout << "~Circle()" << endl;
    }
private:
    double _radius;
};

class Triangle
{
public:
    Triangle(double a = 0, double b = 0, double c = 0)
    : _a(a)
    , _b(b)
    , _c(c)
    {
        cout << "Triangle(double = 0, double = 0, double = 0)" << endl;
    }

    void show() const 
    {
        cout << "Triangle";
    }

    double showArea() const 
    {
        //海伦公式
        double tmp = (_a + _b + _c)/2;

        return sqrt(tmp * (tmp - _a) * (tmp - _b) * (tmp - _c));
    }

    ~Triangle()
    {
        cout << "~Triangle()" << endl;
    }
private:
    double _a;
    double _b;
    double _c;
};

void func(const Figure &fig)
{
    fig.handlDisplayCallback();
    cout << "的面积 : " << fig.handlAreaCallback() << endl;
}

int main(int argc, char **argv)
{
    Rectangle rectangle(10, 20);
    Circle circle(10);
    Triangle triangle(3, 4, 5);

    //Figure是具体的类
    Figure fig;
    fig.setDisplayCallback(bind(&Rectangle::display, &rectangle, 10));
    fig.setAreaCallback(bind(&Rectangle::area, &rectangle));
    func(fig);

    fig.setDisplayCallback(bind(&Circle::print, &circle));
    fig.setAreaCallback(bind(&Circle::printArea, &circle));
    func(fig);

    fig.setDisplayCallback(bind(&Triangle::show, &triangle));
    fig.setAreaCallback(bind(&Triangle::showArea, &triangle));
    func(fig);

    return 0;
}

