---
layout: post
title:  "重新学习 Java"
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

> 根据 Java Language Specification 的要求，Java 源代码的字符串中的反斜线被解释为 Unicode 转义或其他字符转义。因此必须在字符串字面值中使用两个反斜线，表示正则表达式受到保护，不被 Java 字节码编译器解释。例如，当解释为正则表达式时，字符串字面值 "\b" 与单个退格字符匹配，而 "\\b" 与单词边界匹配。字符串字面值 "\(hello\)" 是非法的，将导致编译时错误；要与字符串 (hello) 匹配，必须使用字符串字面值 "\\(hello\\)"


#### 匹配索引

- `public int start()`：返回匹配到的首字符的索引
- `public int end()`：返回匹配到的尾字符索引加一

```java
    public static void test2() {
        String str = "dog dog dog happy dog year";
        String reg = "\\bdog\\b";

        Pattern p = Pattern.compile(reg);
        Matcher m = p.matcher(str);

        int count = 0;
        while (m.find()) {
            count++;
            System.out.println(count + " " + m.start() + " " + m.end());
        }
    }
```

#### 判断是否匹配

- `public boolean lookingAt()`：从头开始匹配模式
- `public boolean find()`：尝试匹配下一个
- `public boolean matches`：将整个区域和模式进行匹配

```java
String str = "cat cat cat";
String reg = "cat";

//匹配整个字符串
boolean isMatches = Pattern.matches(reg, str);

Matcher m = Pattern.compile(reg).matcher(str);
//在字符串序列中查找是否有匹配模式的部分
boolean isFound = m.find();
boolean isLookingAt = m.lookingAt();
```

#### 字符串替换

- `public String replaceAll`：替换所有匹配到的字符串


```java
String str = "lion lion lion, I'm a lion";
String reg = "lion";

Matcher m = Pattern.compile(reg).matcher(str);
//cat cat cat, I'm a cat
String replaceStr = m.replaceAll("cat");
```


`String` 类也有这个方法

```java
String replaceStr1 = "lion lion lion, I'm a lion".replaceAll(reg, "dog");

//String#replaceAll(String replacement) 方法的实现也是通过 Pattern 和 Matcher 类实现的
public String replaceAll(String regex, String replacement) {
    return Pattern.compile(regex).matcher(this).replaceAll(replacement);
}
```
## Spring

Ant 风格的资源匹配符号
- ?：匹配文件名中的一个字符
- *：匹配文件名中任意字符
- **：匹配多次路径


`BeanFactory` 和 `ApplicationContext`，为 Web 专门准备的是 `WebApplicationContext`

先设置一个学生类，将学生类注入到 spring 的 IoC 容器中
```java
public class Student {
    private String name;
    private Integer age;

    //setter 和 getter 方法省略
}
```

spring 配置文件，定义 spring 容器中的类
```xml
<bean name="student" class="com.ykjver.learnspring.controller.Student"></bean>
```

IoC 容器的基本使用

```java
//加载配置文件的 resource
ResourcePatternResolver resolver = new PathMatchingResourcePatternResolver();
Resource resource = resolver.getResource("classpath:springConf.xml");

//初始化 BeanFactory 工厂
DefaultListableBeanFactory factory = new DefaultListableBeanFactory();
XmlBeanDefinitionReader reader = new XmlBeanDefinitionReader(factory);
reader.loadBeanDefinitions(resource);

//从工厂中获取类
Student student = factory.getBean("student", Student.class);
```

`ApplicationContext` 的基本使用
```java
ClassPathXmlApplicationContext ctx = new ClassPathXmlApplicationContext("springConf.xml");
Student student = ctx.getBean("student", Student.class);

System.out.println(student.getName() + " " + student.getAge());
```

基于 Annotation 的 ApplicationContext

使用 Java 类配置
```java
@Configuration
public class MyBeans {

    @Bean(name = "student2")
    public Student buildStudent() {
        Student student = new Student();
        student.setName("NashYoung");
        student.setAge(12);
        return student;
    }
}
```

```java
ApplicationContext ctx = new AnnotationConfigApplicationContext(MyBeans.class);
Student student = ctx.getBean("student2", Student.class);
```

获取 `WebApplicationContext` 的方法

```java
@RequestMapping("hello")
@ResponseBody
public String hello(HttpServletRequest request) {

    //WebApplicationContext 实际上是放在 ServletContext 里面的。
    ServletContext context = request.getServletContext();
    WebApplicationContext wac = (WebApplicationContext) context.getAttribute(WebApplicationContext.ROOT_WEB_APPLICATION_CONTEXT_ATTRIBUTE);
    Dog dog = wac.getBean("bigDog", Dog.class);
    dog.say();

    return "you";
}
```

Bean 配置信息
- xml
- Groovry
- Java Class Java 类
- Annotation 注解


依赖注入的方式
- 属性注入
- 构造函数注入
    - 参数类型
    - 索引位置
    - 索引位置和参数类型
    - 类型反射
- 工厂方法注入，静态工厂和非静态工厂

方法注入

- lookup 方法注入
- 方法替换


## AOP

JDK 动态代理，CGLib 动态代理

JDK 动态代理通过实现 `java.lang.reflect.InvocationHandler` 生成代理类

```java
public class MyJDKInvocationHandler implements InvocationHandler {
    private Object target;

    public MyJDKInvocationHandler(Object target) {
        //方法调用者
        this.target = target;
    }

    @Override
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
        System.out.print("参数是:" + Arrays.toString(args));
        System.out.println("调用前" + proxy.getClass().getName() + "." + method.getName());
        //获取调用的结果，并返回
        Object result = method.invoke(target, args);
        System.out.println("调用后");
        return result;
    }
}
```

使用代理调用 say 方法

```java
@Test
public void test4() {

    MyInterface target = new MyInterfaceImpl();

    MyJDKInvocationHandler handler = new MyJDKInvocationHandler(target);

    //JDK 代理必须使用 interface 进行调用
    MyInterface proxy = (MyInterface) Proxy.newProxyInstance(
            target.getClass().getClassLoader(),
            target.getClass().getInterfaces(),
            handler
    );

    proxy.say();
}
```

使用 CGlib 做代理，是通过动态修改字节码技术，需要代理类实现 `MethodInterceptor` 接口，通过返回一个 `Enhancer` 产生了的代理类

```java
// MyCglibProxy 实现了接口 MethodInterceptor
MyCglibProxy methodInterceptor = new MyCglibProxy();
Enhancer enhancer = new Enhancer();
//设置代理类的父类
enhancer.setSuperclass(MyInterfaceImpl.class);
//设置调用
enhancer.setCallback(methodInterceptor);
MyInterfaceImpl proxy = (MyInterfaceImpl) enhancer.create();
proxy.say();
```


2018-02-20
Updating...