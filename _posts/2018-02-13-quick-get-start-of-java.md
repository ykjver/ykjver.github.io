---
layout: post
title:  "Java 快速入门"
date:   2018-02-13 00:12:00
categories:  java
author : ykjver
---


### 进制

`0b` 开头代表二进制，`0` 开头代表八进制，`0x` 开头代表十六进制

```java
System.out.println(0b100); // 4
System.out.println(0100); // 64
System.out.println(100); // 100
System.out.println(0x100); // 256
```

### 数据类型

1. 基本类型：4类8种
2. 引用类型：类，接口，数组。

| 类型     | 占用   |
| -------- | ------ |
| byte     | 1字节  |
| short    | 2字节  |
| int      | 4 字节 |
| long     | 8 字节 |
| float    | 4 字节 |
| double   | 8 字节 |
| char     | 2 字节 |
| boolean | 1 字节 |

整数默认是int类型，浮点数默认是double类型，long类型的变量，要加l或者L,float类型的变量，要加f或者F。程序中的整数字面值 `1` 为 int 类型，浮点字面值 `1.1` 为 double 类型，如果其他类型和字面类型做四则运算，则会提升值 int 或者 double

```java
short s1 = 1, s2 = 2;
//short 和 short 相加为 int
//short s3 = s1 + s2;
int s3 = s1 + s2;

s1 += 1;
//short 和字面值相加为 int
//s1 = s1 + 2;
int s4 = s1 + 2;
```

`Java` 实际上只有值传递，如果是基本类型

```java
//byte char short int long 等基本类型作为参数，在方法内改变值，外部并不收到影响
public void param(int foo, int bar){
    foo = 3;
    bar = 4;
}

//作为字符串参数，由于 java 内部最字符串作为常量池，所以如果传入的字符串参数不变化，字符串的地址不会变化，如果在方法内字符串变化过，那么参数地址变化，但并不影响方法调用者的入参变量
public void param(String foo, String bar){
    System.out.println("a change before : " + a.hashCode());
    a = "spring";
    System.out.println("a change after : " + a.hashCode());

    System.out.println("b: " + b.hashCode());
}

//对于引用类型，实际上是传入堆引用地址，在调用方法内部改变了参数，外部也会改变。这里只能通参数本事能改变自己的方法改变。
public static void change(List<Integer> accountList) {
    //这里调用 add 方法的地址和外部一一样，所以外部会改变
    accountList.add(9527);

    //这里使得参数在调用方法内的地址改变，而外部不变，不能影响到外部
    accountList = null;
}
```


### 位运算

针对同一个数据异或两次，值不变。

交换两个变量的值
```java
int temp = a;
a = b;
b = temp;
```

使用 `^` 实现
```java
a = a ^ b;
b = a ^ b;
b = a ^ b;
```

数组初始化


方法重载：一个类中允许有方法名相同，但参数不同的同名方法。

```java
public class MethodOverloadDemo {

    public void summer() {}

    public void summer(int val) {}

    public void summer(String val) {}

    public void summer(char val) {}

    public void summer(int val, int i) {}
    
}
```
访问数组异常
- `ArrayIndexOutOfBoundsException`，访问了不存在的数组索引
- `NullPointerException`，访问的数组元素不再指向堆中有效地址


### 内部类

#### 成员内部类
```java
public class InnerClassDemo {

    //定义内部类
    public class Inner {
        private void show() {
            System.out.println("winter");
        }
    }

    public static void main(String[] args) {

        //实例化外部类，再实例化内部类
        Inner inner = new InnerClassDemo().new Inner();
        inner.show();
        //输出 winter
    }
}
```

#### 局部类
```java
public class LocalClassDemo {
    public static void main(String[] args) {

        //网上说这里需要使用 final 关键字，但是这里并没有
        String summer = "summer";

        //声明局部类，再外部并不可见
        class LocalClass {
            //局部类不能使用 static 关键字
            public void show() {
                System.out.println("winter");
                System.out.println(summer);
            }
        }

        LocalClass localClass = new LocalClass();
        localClass.show();
        //输出 winter
        // summer
    }
}
```

#### 匿名类
```java
public class AnonymousClass {

    public static void main(String[] args) {

        //实例一个 Runnable 的匿名类，一次使用
        new Thread(new Runnable() {
            @Override
            public void run() {
                System.out.println("winter");
            }
        }).start();
    }
}
```

### 字符串

#### 字符串的常用构造方法

```java
//"你好"的 UTF-8 字节数组
byte[] bytes = new byte[]{-28, -67, -96, -27, -91, -67};
String str1 = new String(bytes);
String str2 = new String(bytes, "UTF-8");

//"你好"的 字符数组
char[] chars = new char[]{'你', '好'};
String str3 = new String(chars);
String str4 = new String(chars, 0, 2);

StringBuilder sb = new StringBuilder("你好");
String str5 = new String(sb);
```

### String,StringBuilder,StringBuffer

`String` 为不可变的字符串，`StringBuffer` 为线程安全的可变字符串，`StringBuilder` 为线程非安全的可变字符串

```java

// JDK 中的 Sring 对象
public final class String
    implements java.io.Serializable, Comparable<String>, CharSequence {
    /** The value is used for character storage. */
    private final char value[];
```

这里存储的是用 char 数组存储字符串的，不过是 final 类型，所以不可变，所以对字符串做增加不是对 char 数组做改变。

StringBuffer 和 StringBuilder 都集成自 AbstractStringBuilder，由于 StringBuffer 的方法加了 sychronized 关键字，所以使得 StringBuffer 操作底层的 char 数组变得线程安全。

### 正则表达式


