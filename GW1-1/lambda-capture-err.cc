#include <iostream>
using namespace std;


int main()
{
	int x = 0;
	int y = 42;

	auto qqq = [x, &y]         //变量值抓取无法改变,可修改的必须为左值
	{                          //因为抓取的x为0是常量，所以无法修改
		cout << "qqq下的x是" << x << endl;
		cout << "qqq下的y是" << y << endl;
		++y; 
	};
	qqq();
	auto qqq1 = [=]          //这里匿名函数赋值名和上面的匿名函数相同
	{                        //所以在下面的调用时，两个均可调用，发生冲突
		cout << "qqq1下的x是" << x << endl;
		cout << "qqq1下的y是" << y << endl;
	};
	qqq1();
	auto qqq2 = [&]
	{
		cout << "qqq2下的x是" << x << endl;
		cout << "qqq2下的y是" << y << endl;
		++y; ++x;
	};
	qqq2();
	auto qqq3 = [&, x]
	{
		cout << "qqq3下的x是" << x << endl;
		cout << "qqq3下的y是" << y << endl;
		++y; 
	};
	qqq3();
	auto qqq4 = [=, &x]
	{
		cout << "qqq4下的x是" << x << endl;
		cout << "qqq4下的y是" << y << endl;
	    ++x;
	};
	qqq4();
	auto qqq5 = [=,&x](int z) mutable  //创建了一个变量z来调用函数运行
	{                                  //用mutable可变y，使y也能前置++
		cout << "qqq5下的x是" << x << endl;
		cout << "qqq5下的y是" << y << endl;
		++y; ++x;
	};
	qqq5(0);
	
	cout << "x是" << x << endl;//显示x,y的值
	cout << "y是" << y << endl;

	system("pause");
	return 0;
}

