# 作业1-Lambda表达式与简单语言的形式描述

**组员：邵期翔** 
**栾飞**
**王培**

## 作业要求
- 理解并调试运行提供的C++ Lambda表达式相关的程序，
修正lambda-capture-err.cc中的错误，将修正后的程序更名为lambda-capture.cc，在文档中说明各种错误产生的原因以及解决思路（负责人：栾飞）</br>

- 用C++和Python编写反映多种lambda表达式特征的程序，例如包含高阶函数、lambda表达式使用和修改非局部的变量等，分析说明C++、Python中的lambda表达式所采用的归约策略，它们与lambda演算的异同。
注：可以先编译运行lambda-capstarthis.cc，来加以理解，然后再试着编写自己的应用实例程序。（负责人：王培）</br>

- 理解interpreter.ml,安装OCaml并运行之；进一步扩展interpreter.ml，增加课堂上介绍的L{num,str}语言的num类型及其表达式，进行类型检查和翻译。（负责人：邵期翔）
 
### part1 改错

```
auto qqq = [x, &y]         //变量值抓取无法改变,可修改的必须为左值
	{                          //因为抓取的x为0是常量，所以无法修改，需要去掉++x
		++y; 
	};
```


```
auto qqq1 = [=]          //这里匿名函数赋值名和上面的匿名函数相同
	{                        //所以在下面的调用时，两个均可调用，发生冲突，需要去掉++x和++y

	};
```
```
auto qqq5 = [=,&x](int z) mutable  //创建了一个变量z来调用函数运行，否则函数无法调用
	{                                  //用mutable可变y，使y也能前置++

		++y; ++x;
	};
//最后每个函数名要不一样，否则系统不知道调用那个函数，函数调用失败。
```

### part 2 编写lambda表达式
#####归约策略

实验中发现，无论是在c++ 还是 python 中， 所采用的归约策略都是application-order

#####与lambda演算的异同
形式上，c++与python中lambda函数的定义和使用方式和lambda演算类似，即大致遵循 （lambda 变量 表达式）的格式，
并且它们都可以嵌套使用。</br>

c++中，还包括对非局部变量的值传递捕捉和引用传递捕捉，python中对非局部变量的捕捉可以认为是引用传递捕捉。
而在lambda表达是中，则不涉及非局部变量。默认不能捕捉非局部变量。</br>

C++的lambda表达式中，可以像普通函数那样包含多条语句。而python中的lambda表达式则只能包含一条语句，更接近lambda演算的形式。</br>

代码中也包含了相关注释

### part3 Ocaml扩展interpreter.ml
基于原来的代码，扩展部分新增了Type.Num，Term.N，Term.Plus，Term.Times。</br>
Type.Num指代新加入的Num类型，Term.N与代码中存在的Term.Z功能大致相同，判断是否为Num类型。</br>
Term.Plus和Term.Times用于接收两个参数，并判断其类型，如果全是Num则输出的类型也为Num，如果全是Int则输出的类型也是Int，否则输出None。