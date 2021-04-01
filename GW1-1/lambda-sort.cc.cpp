#include <algorithm>
#include <cmath>
#include <array>
#include <iostream>
#include <string>
using namespace std;

void pri(int arr1[])
{
    for (int i = 0; i < 10; i++)
    {
        cout << arr1[i] << endl;
    }
}//打印数组

class     
{

public:
    bool operator()(int a, int b)const 
    {
        return a < b;
    };//仿函数，返回bool型

}customless;//对象建立，匿名的对象为customless

void abssort(int* x, unsigned N)
{
    sort(x, x + N, [](int a, int b){ return abs(a) < abs(b); });
}//绝对值排序


int main()
{
    int arr[] = { 5,7,-4,2,8,-6,1,-9,0,3 };//建立数组
    cout << "排序前的数组情况" << endl;
    pri(arr);

    sort(arr, arr+10);                   //利用sort排序
    cout << "使用默认运算符排序<" << endl;
    pri(arr);

    sort(arr, arr + 10,greater<int>());  //利用标准库里的比较排序
    cout << "使用标准库比较功能对象排序" << endl;
    pri(arr);

    sort(arr, arr + 10,customless);   //利用类和仿函数排序
    cout << "使用自定义功能对象排序" << endl;
    pri(arr);

    sort(arr, arr+10, [](int a, int b) {return a > b; });//利用匿名函数排序
    cout << "使用lambda表达式排序" << endl;
    pri(arr);

    abssort(arr, 10);      //调用函数排序
    cout << "使用lambda表达式排序" << endl;
    pri(arr);
  

    system("pause");
    return 0;
}