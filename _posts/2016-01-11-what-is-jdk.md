---
layout: post
title:  "JDK一些常识"
date:   2016-01-11 23:59:59
categories:  java
author : 自来也
---

###jdk简介

Java Development Kit (JDK)，是Oracle公司发布基于Linux，Mac OS X，Windows，Solaris操作系统用于JavaSE，EE，ME平台的实现，JDK包括JVM和一些完成Java开发的类库，工具等资源，

**基本术语**

- JDK，全称java develop kit，java软件语言开发工具包，包含java。
	- SE，标准版
	- EE，企业版
	- ME，移动版
- SDK，softwave deveplo kit，软件开发包，JDK以前叫做java softwave develop kit，在1.2版本后，改名java develop kit。
- JRE，java runtime environment，java运行环境，java程序都要运行在JRE上面，它主要包括，JVM（java虚拟机），java核心文件和类库，不包含JDK中的编译器，调试和其他工具。说白了JRE就是JVM和去掉开发工具的JDK。
- JVM，java virtual machine，java虚拟机，执行java程序，并调用native api，这正是java平台无关性的关键，JVM把java字节码解释成具体平台上面的机器指令执行。

###JDK目录结构

- bin java开发的各种工具和核心的可执行文件
	- jar java程序打包程序，将先关的类打包成一个程序
	- java java解释器，执行javac生成的字节文件
	- javac java compiler java编译器，将java代码编译成字节码
	- javaw 和java类似，只不过是windows图形界面
	- jdb java debug java查错调试工具，可以进行断点
	- javadoc 文档程序，从源代码的主时钟提取注释，生成html文档

- db java实现的一个数据，不经常用到
- include 对java程序进行底层扩展，需要用到[JNI](https://en.wikipedia.org/wiki/Java_Native_Interface)技术。
- jre java运行环境，只包含供java程序运行的类库和可执行文件等
- lib java运行的基本类库
	- dt.jar 核心类库
	- tools.jar 工具包
- src 如果在安装jdk是选择了安装源码（开发人员建议安装上），就会有这个安装包。

以上，就是jdk目录的基本结构，和基本介绍。


具体深入待续~

###REFERENCE
- [JDK、SDK、JRE、JVM概念详解](http://developer.51cto.com/art/200907/134755.htm)
- [JDK](https://en.wikipedia.org/wiki/Java_Development_Kit)
