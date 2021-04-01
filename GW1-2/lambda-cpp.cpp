#include <iostream>
using namespace std;

int main()
{
    // 高阶函数
    auto connect = [](string value) {
        auto new_value = "I got :" + value;
        return [=](auto call) {
            call(new_value);
        };
    };
    connect("Hello World")([](auto new_value) {
        cout << new_value << endl;
    }); // I got : Hello World


    
    int a = 0;
    // 使用非局部变量
    // 值传递方式捕捉， 值捕捉发生在函数定义时而不是函数调用时
    auto print_a = [a] { cout << "a=" << a << endl; };
    print_a();//a=0
    a++;
    print_a();//a=0

    // 修改非局部变量
    auto increase_a = [&a] { a++; };
    cout << "修改前a=" << a << endl; // a=1
    increase_a(); // a=a+1
    cout << "修改后a=" << a << endl; // a=2

    //归约策略
    int x = [](int x) {cout << "外层函数运行...: x="<<x << endl; return x+1; }([](int x) {  cout << "内层函数运行...: x=" << x << endl; return  x+1; }(0));
    cout << "全部运行结束x=" << x << endl;
    // 先运行内层函数，再运行外层函数，表明归约策略为application-order

    return 0;
}

