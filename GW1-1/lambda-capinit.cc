#include <iostream>
using namespace std;

void test()
{
	int x = 4;
	auto y = [&r = x, x = x + 1]()//将x+1赋值给x，在引用x换名为r
	{
		r += 2;                   //r+2赋值给r
		return x + 2;             //返回x+2，因为换名x为r，
		                          //所以改变r等于改变x
	}();                          //所以x=4+2=6,而返回值是4+1+2=7
	cout << "x是" << x << endl;   //显示x、y,
	cout << "y是" << y << endl;
	
}


int main()
{
	test();
	

	system("pause");
	return 0;
}