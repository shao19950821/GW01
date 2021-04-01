#include <iostream>
#include <cmath>
#include <future>
using namespace std;


class task//定义一个对象
{

public:
	task():a(0.0),b(0.0)//构造函数
	{

	}
	~task()//析构函数
	{
		a = nan("");
		b = nan("");
	}
	void set_a(double A)//写a
	{
		a = A;
	}
	void set_b(double B)//写b
	{
		b = B;
	}
	
	future<double>run11()//调用future
	{
		task self = *this;
		return async(launch::async, [=]()
			{
				return sqrt(self.b * self.b + self.a * self.a);
			}//计算根号下a*a+b*b
		);
	}

	future<double>run14()
	{
		return async(launch::async, [=,self=*this]()
			{
				return sqrt(self.b * self.b + self.a * self.a);
			}
		);
	}

	future<double>run17()
	{
		return async(launch::async, [=,self=*this]()
			{
				return sqrt(a*a+b*b);
			}
		);	
	}

	future <double>start11(task& t)//执行run11函数
	{
		return t.run11();
	}


	future <double>start14(task& t)
	{
		return t.run14();
	}


	future <double>start17(task& t)
	{
		return t.run17();
	}

private:
	double a;
	double b;

};





int main()
{
	task t;
	t.set_a(5.0);
	t.set_b(10.0);

	cout << "t.start11(t)的返回值是" << t.start11(t).get() << endl;//显示ruu11返回值
	cout << "t.start14(t)的返回值是" << t.start14(t).get() << endl;//显示ruu14返回值
	cout << "t.start17(t)的返回值是" << t.start17(t).get() << endl;//显示ruu17返回值

	system("pause");
	return 0;
}