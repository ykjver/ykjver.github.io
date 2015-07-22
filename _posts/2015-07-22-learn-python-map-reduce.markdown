---
layout: post
title:  "python学习笔记"
date:   2015-07-22 23:11:45
categories: python
author : snow0x01
---


`map/reduce` 来源自google的一片论文
`map()`函数接口两个参数，第一个参数为函数，第二参数为`Iterable`,`map()`函数依次把函数作用到传入的`Iterable`上，并把更新的`Iterable`返回例如下面

{% highlight python %}

def sq(x):
	return x * x

print(list(map(sq, [1, 2, 3, 4, 5, 6, 7, 8, 9])))

#output
#[1, 4, 9, 16, 25, 36, 49, 64, 81]


{% endhighlight %}

函数`sq()`依次`map()`作用到`[1, 3, 4, 5, 6, 7, 8, 9]`上，然后返回更新后的结果

对于`reduce()`函数带有两个参数，第一个参数为函数，该函数拥有两个参数，第二个为`Iterable`，`reduce`将函数作用到`Iterable`上，并累计效果如下所示

`reduce(f, [1, 2, 3, 4]) = f(f(f(1, 2),3),4)`







