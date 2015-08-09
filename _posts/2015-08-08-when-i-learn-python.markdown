---
layout: post
title:  "python学习笔记"
date:   2015-08-08 23:10:45
categories: python
author : snow0x01
---

学习python已经大概有一个月了吧，整理下学习的这个月学习成果。

###基本数据类型

####数字类型

- int
- float 
- complex number 用j或者J结尾来表示虚数部分,例如3+5j

    >>> 2 + 2
    4
    >>> 2 / 2
    1.0
    >>> 1 / 2
    0.5
    >>> 2 - 2
    0
    >>> 2 * 2
    4
    >>> 2 ** 10
    1024
    >>> 1 / 2
    0.5
    >>> 0.5 * 3
    1.5
    >>> 1 / 3
    0.3333333333333333
    >>> 2 ** 20
    1048576
    >>> 2 ** 50
    1125899906842624
    >>> 2 ** 100
    1267650600228229401496703205376
    >>> 2 ** 200
    1606938044258990275541962092341162602522202993782792835301376
    >>> 2 ** 300
    2037035976334486086268445688409378161051468393665936250636140449354381299763336706183397376
    

以上就是python中数字类型的一般操作，其中比较特殊的是2的300次方居然都不溢出，OMG，以前学过的语言中就没有语言原生支持这样的大数运算

####字符串类型

在python中用双引号或者但引号来表示字符串，双引号和单引号基本相同

    >>> 'yangke' 'ke'
    'yangkeke'
    >>> 'yangke' + 'ke'
    'yangkeke'
    >>> 'yangke' + 'ke' == 'yangke' 'ke'
    True
    >>> 'yangke' * 3
    'yangkeyangkeyangke'
    >>> 'yangke'[0]
    'y'
    >>> 'yangke'[0:4]
    'yang'
    >>> yangke = 'yangke'
    >>> yangke
    'yangke'
    >>> print('''muti line
    ... line1
    ... line2
    ... line3
    ... ''')
    muti line
    line1
    line2
    line3

字符串字面量和字符串字面量链接可以不需要+，但是有字符窜变量就必须+，字符串还可以做乘法，表示该字符串重复n次，在python中没有字符，长度为1的字符串表示一个字符如果表示多行文本，使用trible quotes， """xxxx"""或者'''xxxx'''

如果是要打断一个很长的字符串，使用下面这种方式非常方便

    text = ('when i was young, i have a dream '
            ', to become a program engineer')


在字符串切片中，切片参数可以超过字符串长度下标，但是字节访问字符串下标不能超过,表示字符串长度用len(yangke)

    >>> yangke
    'yangke has is a handsome man'
    >>> len(yangke)
    28
    >>> yangke[1]
    'a'
    >>> yangke[28]
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    IndexError: string index out of range
    >>> yangke[28:]
    ''
    >>> yangke[:28]
    'yangke has is a handsome man'

###List

List是一种有序集合，把一系列数据组织到一起，就像其他语言中数组一样，不过python的一个List中可以有不同的数据类型


     
    >>> score = [100, 95, 80, 88, 92]
    >>> score
    [100, 95, 80, 88, 92]
    >>> score[0]
    100
    >>> score[0:3]
    [100, 95, 80]
    >>> score[3:]
    [88, 92]
    >>> score[-2]
    88
    >>> score + [91, 70, 60, 54]
    [100, 95, 80, 88, 92, 91, 70, 60, 54]
    >>> score.append(100)
    >>> score
    [100, 95, 80, 88, 92, 100]
    >>> mutiType = [100, ['yangke', 'le'], 'python']
    >>> mutiType
    [100, ['yangke', 'le'], 'python']

在List中，同样支持slice切片功能和字符串中的使用方法是一样的，同样，如果是通过下标访问List中某个元素，下标一样不能越界的

###tuple

tuple初始化后就不能改变了，这里指的是tuple中每个元素的handle不会改变，如果在tuple中有一个list，那么这个list的内容也可以改变，而在该tuple中list的引用是不会改变的

    >>> mytuple = ('python', 'java', 'php', 'javascript', 'c', 'html', 'css')
    >>> mytuple.append('c#')
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    AttributeError: 'tuple' object has no attribute 'append'
    >>> mytuple[0]
    'python'
    >>> mytuple[0:3]
    ('python', 'java', 'php')
    >>> oneElement = (1)
    >>> type(oneElement)
    <class 'int'>
    >>> oneElementTuple = (1,)
    >>> type(oneElementTuple)
    <class 'tuple'>


###dict

在python中类似于java中的map的一种数据类型为dict，使用键值对的方式存储，dict和list的区别为，dict查询速度快，但是占内存比list要多。dict的key只能使用不可变的值类型，如int，str，不能使用引用类型，如list，class等。dict基本操作如下


    >>> dict = {'yangke': 60, 'jiangrui': 70, 'super':50}
    >>> dict
    {'super': 50, 'yangke': 60, 'jiangrui': 70}
    >>> dict['super']
    50
    >>> 'super' in dict
    True
    >>> 'zhou' in dict
    False
    >>> dict.get('super')
    50
    >>> dict.get('zhou')
    >>> dict.get('zhou', 100)
    100
    >>> dict.pop('yangke')
    60
    >>> dict
    {'super': 50, 'jiangrui': 70}
    >>> type(dict)
    <class 'dict'>
    >>> 

###set

set和dict都是使用hash来存储唯一key的，不过set不存value只存key，同理在set中也只能存储值类型，用于生成hash，set的基本操作如下


    >>> s = set([1, 2, 3, 4, 5])
    >>> s
    {1, 2, 3, 4, 5}
    >>> s1 = set([1, 1, 1, 1, 1, 2])
    >>> s1
    {1, 2}
    >>> s2 = set([1, 1, [1, 2, 3], (1, 2)])
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    TypeError: unhashable type: 'list'
    >>> s
    {1, 2, 3, 4, 5}
    >>> s.remove(1)
    >>> s
    {2, 3, 4, 5}
    


###python中的函数

在python中函数使用def来定义如下，缩进为函数体

    >>> def sum(x, y):
    ...     return x + y
    ... 
    >>> sum(10, 10)
    20

如果参数个数不正确，会抛出错误

    >>> sum(10)
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    TypeError: sum() missing 1 required positional argument: 'y'
    >>> sum(10, 10, 10)
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    TypeError: sum() takes 2 positional arguments but 3 were given

但是，如果参数类型不正确，python并不会主动去检查

    >>> sum('python', ' is good')
    'python is good'

可以使用内置函数isinstance主动检查参数类型是否正确

    >>> def sumCheckType(x, y):
    ...     if not (isinstance(x, (int, float)) and isinstance(y, (int, float))):
    ...         raise TypeError('band params type')
    ...     return x + y
    ... 
    >>> sumCheckType(50, 50)
    100
    >>> sumCheckType('java', ' oh! my god!')
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
      File "<stdin>", line 3, in sumCheckType
    TypeError: band params type

在python中函数是可以返回多个值，不过一般情况还是返回一个值比较清晰，如果有多个值可以放在一个list中或者是tuple中之类的，因为返回多个值其实就是返回的一个tuple

    >>> def mutiReturnFunc():
    ...     return 1, [1, 2], (3, 4), {'song':'Hey, Sold Sister'}
    ... 
    >>> val, l, t, d = mutiReturnFunc()
    >>> val
    1
    >>> l
    [1, 2]
    >>> t
    (3, 4)
    >>> d
    {'song': 'Hey, Sold Sister'}

函数参数的默认值使用

    >>> def defaultParams(n = 3):
    ...     return n ** 2
    ... 
    >>> defaultParams()
    9

如果是引用类型的默认参数，在函数内部有改变其值的动作，那么这个参数的改变将会被记忆下来，影响到后面的调用

    >>> def complexDefaultParam(l = []):
    ...     l.append(['python'])
    ...     return l
    ... 
    >>> complexDefaultParam()
    [['python']]
    >>> complexDefaultParam()
    [['python'], ['python']]


函数中可变参数，如果函数参数个数不确定，一种解决方法是将参数组装成list或者是tuple传给函数，还有一种方案是使用可变参数

使用第一中方式实现方式如下

    >>> def mutiParas(l):
    ...     sum = 0
    ...     for e in l:
    ...         sum = sum + e
    ...     return sum
    ... 
    >>> mutiParas([1, 2, 3, 4, 5])

使用可变参数如下

    >>> def mutiParams(*numbers):
    ...     sum = 0
    ...     for number in numbers:
    ...         sum = sum + number
    ...     return sum
    ... 
    >>> 
    >>> mutiParams(1, 2, 3, 4, 5)
    15

其实可变参数传入的就是tuple

    >>> def mutiParamsType(*numbers):
    ...     print(type(numbers))
    ...     return None
    ... 
    >>> mutiParamsType(1, 2, 3, 4, 5)
    <class 'tuple'>

如果想要传入一个list作为可变参数，则在实参前面加上×号

    >>> mutiParams(*l)
    15

在python中，可变参数如果是键值对参数，那么需要用××双星号来表明键值对可变参数

    >>> mutiParams(*l)
    15
    >>> person('yange', 21, height=173, weight=60)
    {'name': 'yange', 'age': 21, 'other': {'weight': 60, 'height': 173}}
    >>> 

传入的键值对可变参数被构建成一个dict类型在函数内部

    >>> def person(name, age, **other):
    ...     print(type(other))
    ... 
    >>> person('php', 20, c=True, sina='good')
    <class 'dict'>

同理，也可以用××来用dict传入键值对可变参数

    >>> person('php', 20, **{'summer':'you', 'winter':'i'})
    <class 'dict'>

用×来分来一般参数和关键字参数，位置参数必须先传入，传入位置参数后，关键字参数的位置就随意了

    >>> def person(name, age, *, city, job):
    ...     print(name, age, city, job)
    >>> person('yangke', 21, job='engineer', city='chengdu')
    yangke 21 chengdu engineer


可以把必选参数，默认参数，可变参数/命名关键字参数和关键字参数组合使用，


    >>> def f1(name, age=21, *other, **dict):
    ...     print(name, age, other, dict)
    ... 
    >>> f1('python', 21)
    python 21 () {}
    >>> f1('python')
    python 21 () {}
    >>> f1('python', 21, 'a', 'b', x=1, y=2)
    python 21 ('a', 'b') {'y': 2, 'x': 1}

python中，任何参数都可以通过func(*tuple, **dict)来调用，如调用f1函数的调用方式如下

    >>> f1(*('java', 33, 'a', 'b'), **{'x':1, 'y':2})
    java 33 ('a', 'b') {'y': 2, 'x': 1}
