# 高阶函数
connect = lambda value : lambda call : call("I got : " + value)
connect("Hello World")(lambda x : print(x))

# 使用非局部变量值
# 会以引用传递方式捕捉非局部变量
a=0
print_a = lambda : print("a=",a)
print_a() # a=0
a+=1
print_a() # a=1


# 修改非局部变量值
someone=dict(age=20,name='Xiao Ming')
increase_a  = lambda : someone.update(age=21)
increase_a()
print(someone['age']) # 21

# 归约策略
(lambda x : print('外层函数运行...: 输入=',x))((lambda x:print('内层函数运行...: 输入=',x))(0))
# 先运行内层函数，再运行外层函数，表明归约策略为application-order



