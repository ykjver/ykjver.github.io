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

Spring AOP 前置增强

添加需要增强的类和接口
```java
//服务员接口
public interface Waiter {
    void greetTo(String name);
    void serveTo(String name);
}

// 实际需要增强的类
public class NativeWaiter implements Waiter {
    @Override
    public void greetTo(String name) {
        System.out.println("greet to..." + name);
    }

    @Override
    public void serveTo(String name) {
        System.out.println("serve to..." + name);
    }
}

//增强类，前置增强，在增强目标的每隔方法执行前都执行一句“你好”
public class GreetingBeforeAdvice implements MethodBeforeAdvice {
    @Override
    public void before(Method method, Object[] objects, Object o) throws Throwable {
        String clientName = (String) objects[0];
        System.out.println("你好，" + clientName);
    }
}

//增强和目标接口，并执行代理类
public class BeforeAdviceTest {
    @Test
    public void before() {
        Waiter waiter = new NativeWaiter();
        BeforeAdvice advice = new GreetingBeforeAdvice();
        ProxyFactory proxyFactory = new ProxyFactory();

        proxyFactory.setTarget(waiter);
        proxyFactory.addAdvice(advice);

        Waiter proxy = (Waiter) proxyFactory.getProxy();
        proxy.greetTo("ykjver");
        proxy.serveTo("ykjver");

    }
}
```

Spring AOP 实际上是使用了 `CglibAopProxy` 和 `JdkDynamicAopProxy` 两种形式


Spring 使用 AspectJ 的语法

```java
//定义接口
public interface UserDao {

    int addUser();

    void updateUser();

    void deleteUser();

    void findUser();

}

//实现接口
@Repository
public class UserDaoImpl implements UserDao {
    @Override
    public int addUser() {
        System.out.println("addUser...");
//        int i = 1 / 0;
        return 111;
    }

    @Override
    public void updateUser() {
        System.out.println("updateUser...");
    }

    @Override
    public void deleteUser() {
        System.out.println("deleteUser...");
    }

    @Override
    public void findUser() {
        System.out.println("findUser...");
    }
}

//定义切面，和切面方法
@Aspect
public class MyAspect {

    /**
     * 前置通知
     */
    @Before("execution(* com.ykjver.learnspring.springaopdemo.lesson3.UserDao.addUser(..))")
    public void before() {
        System.out.println("前置增强...");
    }

    /**
     * 在返回后增强
     * @param returnVal
     */
    @AfterReturning(value = "execution(* com.ykjver.learnspring.springaopdemo.lesson3.UserDao.addUser(..))", returning = "returnVal")
    public void afterReturning(Object returnVal) {
        System.out.println("返回后增强..." + returnVal);
    }

    @Around("execution(* com.ykjver.learnspring.springaopdemo.lesson3.UserDao.addUser(..))")
    public Object around(ProceedingJoinPoint pj) throws Throwable {
        System.out.println("环绕增强前...");
        Object obj = pj.proceed();
        System.out.println("环绕增强后...");
        return obj;
    }

    @AfterThrowing(value = "execution(* com.ykjver.learnspring.springaopdemo.lesson3.UserDao.addUser(..))", throwing = "e")
    public void afterThrowing(Throwable e) {
        System.out.println("出现异常: msg = " + e.getMessage());
    }


    @After("execution(* com.ykjver.learnspring.springaopdemo.lesson3.UserDao.addUser(..))")
    public void after() {
        System.out.println("后置增强...");
    }
}
```


如果是使用 XML 配置配型，则首相要定义一个用于装增强方法的切面类，也就是说这个类中的方法就是前置增强，后置增强方法等，然后定义一个切点，就是哪些地方需要切入，比如 com.ykjver.UserDao 这个类需要切入，或者 com.ykjver.** 包下所有类需要切入。然后再配置是 before 类型的切入，还是 around 类型的切入。

先定义切面类
```java
public class MyAspectXML {

    public void before() {
        System.out.println("XML 前置增强...");
    }
}
```

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:aop="http://www.springframework.org/schema/aop"
       xsi:schemaLocation="
       http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd
       http://www.springframework.org/schema/aop http://www.springframework.org/schema/aop/spring-aop.xsd">

    <!-- 切入的对象类 -->
    <bean id="userDao" class="com.ykjver.learnspring.springaopdemo.lesson3.UserDaoImpl" />
    <!-- 定义装增强方法的类，切面 -->
    <bean id="myAspectXML" class="com.ykjver.learnspring.springaopdemo.lesson3.MyAspectXML" />

    <!-- aop 配置 -->
    <aop:config>
        <!-- 切点配置 -->
        <aop:pointcut id="addUserCut" expression="execution(* com.ykjver.learnspring.springaopdemo.lesson3.UserDaoImpl.*(..))"></aop:pointcut>

        <!-- 切面配置，就是说在这个切面上，有哪些切点，如 在 log 日志记录这个切面上，前置增强的目标类为 addUserCut 定义的切点所包含的类 -->
        <aop:aspect ref="myAspectXML">

            <!-- before 类型的增强，使用的是 myAspectXML 切面中的 before 方法，有 addUserCut 中定义的切点被挂在了这个切面上。 -->
            <aop:before method="before" pointcut-ref="addUserCut"></aop:before>
        </aop:aspect>
    </aop:config>
</beans>
```

#### Thread Local 使用
`java.lang.ThreadLocal` 变量，对于每隔线程都是有一个副本的。

在 Thread 类中右一个这样的成员变量，非静态，所以每一个 Thread 实例都有一份 threadLocals 的成员变量，这样就保证每个线程独一份，而 ThreadLocalMap 是类似于Map一样的东西，每个 ThreadLocal 都有自己的一个 Hash 值，把这个 Hash 值和要存储的的值作为键值对，每次调用 `ThreadLocal#get()` 方法就用 ThreadLocal 实例的 Hash 做为键取值。
```java
/* ThreadLocal values pertaining to this thread. This map is maintained
    * by the ThreadLocal class. */
ThreadLocal.ThreadLocalMap threadLocals = null;
```



简单的使用如下

```java
public class ThreadLocalDemo {

    //线程本地变量，重置了 initialValue 方法，方便加一的操作
    public static ThreadLocal<Integer> seqNum = new ThreadLocal<Integer>() {
        @Override
        protected Integer initialValue() {
            return 0;
        }
    };

    //每次给 threadLocal 加一
    public static int getNextNum() {
        seqNum.set(seqNum.get() + 1);
        return seqNum.get();
    }

    public static void main(String[] args) {
        new ClientTest().start();
        new ClientTest().start();
        new ClientTest().start();
    }

    //内部线程类，用作执行每隔线程对 threadLocal 静态变量的取值
    public static class ClientTest extends Thread {
        @Override
        public void run() {
            for (int i = 0; i < 3; i++) {
                System.out.println(Thread.currentThread().getName() + " " +  ThreadLocalDemo.getNextNum());
            }
        }
    }
}
```

#### 泛型

方法或者是类声明的时候，带尖括号的里面声明泛型类型表示符号，如果有多个，就用 `,` 隔开，每种类型都可以用来表明返回类型,泛型类型只能表明是应用类型，不能是原始类型

方法使用泛型
```java

//方法中有两种泛型，其中 T 用来当做返回类型了
public static <T, K> T out(T t, K k) {
    System.out.println(t);
    System.out.println(k);
    return t;
}
```

在方法上使用泛型

```java
public class List<T> {

//用作声明变量
    private T item;

//用作返回类型
    T get() {
        return item;
    }
}
```

也可以使用 `extends` 关键字表明，泛型类型只能为哪些类的子类

```java
//泛型类型只能为 Comparable 的子类
public static <T extends Comparable<T>> T max(T t1, T t2, T t3) {
    T max = t1;
    if (max.compareTo(t2) < 0) {
        max = t2;
    }
    if (max.compareTo(t3) < 0) {
        max = t3;
    }
    return max;
}
```

同时也可以使用通配符 `?`

```java

//比较器类型必须是所比较数组 a 的父类比较器
public static <T> void sort(T[] a, Comparator<? super T> c) {
    if (c == null) {
        sort(a);
    } else {
        if (LegacyMergeSort.userRequested)
            legacyMergeSort(a, c);
        else
            TimSort.sort(a, 0, a.length, c, null, 0, 0);
    }
}
```


### 网络编程

得到本机的 IP 地址

```java
InetAddress addr = InetAddress.getByName(null);
```

`ServerSocket` 的作用是用来等待一个 socket 连接上来，并产生一个 socket，ServerSocket 并不对连接做什么事情。

简单的 ServerSocket 和 Socket 的交互，这里是一对一的连接，即一个 ServerSocket 同时只能处理一个 Socket 连接

```java
// ServerSocket 用于监听连接请求
public class SimpleServerSocketDemo {

    public static final int PORT = 9999;

    public static void main(String[] args) {

        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(PORT);
            System.out.println("started: " + serverSocket);
            //这里接受到 socket 请求就可以送给一个线程管理，那样就能同时处理多个请求
            Socket socket = serverSocket.accept();

            try {
                BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);

                while (true) {
                    String line = br.readLine();
                    if ("END".equals(line)) break;
                    System.out.println("echo:" + line);
                    pw.println("echo:" + line);
                }
            } finally {
                socket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (serverSocket != null) {
                try {
                    serverSocket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
```

socket 用于连接

```java
public class SimpleSocketClientDemo {

    public static void main(String[] args) throws IOException {
        InetAddress inetAddress = InetAddress.getByName(null);
        System.out.println("address:" + inetAddress);
        Socket socket = new Socket(inetAddress, SimpleServerSocketDemo.PORT);
        System.out.println(socket);
        try {
            BufferedReader in =  new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);

            Scanner scanner = new Scanner(System.in);
            while (scanner.hasNext()) {
                String line = scanner.nextLine();
                if ("END".equals(line)) break;
                out.println(line);
                System.out.println(in.readLine());
            }
            out.println("END");
        } finally {
            socket.close();
        }
    }
}

```


### 一个请求发送到 Spring Mvc 到请求返回请求的整个过程


TomCat 容器调用 Filter `ApplicationFilterChain.internalDoFilter(request, response)` 
-> `org.springframework.web.filter.OncePerRequestFilter`;

```java
// OncePerRequestFilter 只支持 httpServlet
// 将 强转成 HttpServletRequest
HttpServletRequest httpRequest = (HttpServletRequest)request;
HttpServletResponse httpResponse = (HttpServletResponse)response;

//只经过一次，设置标记
String alreadyFilteredAttributeName = this.getAlreadyFilteredAttributeName();
boolean hasAlreadyFilteredAttribute = request.getAttribute(alreadyFilteredAttributeName) != null;
if (!hasAlreadyFilteredAttribute && !this.skipDispatch(httpRequest) && !this.shouldNotFilter(httpRequest)) {
request.setAttribute(alreadyFilteredAttributeName, Boolean.TRUE);

try {
    this.doFilterInternal(httpRequest, httpResponse, filterChain);
} finally {
    request.removeAttribute(alreadyFilteredAttributeName);
}
} else {
filterChain.doFilter(request, response);
}
```

-> `org.springframework.web.filter.CharacterEncodingFilter`

```java

//得到编码格式，springboot 默认 utf-8
String encoding = this.getEncoding();
if (encoding != null) {
    if (this.isForceRequestEncoding() || request.getCharacterEncoding() == null) {
        request.setCharacterEncoding(encoding);
    }

// 如果要设置了强转就要强制转换成 utf-8
    if (this.isForceResponseEncoding()) {
        response.setCharacterEncoding(encoding);
    }
}

filterChain.doFilter(request, response);
```

-> `org.springframework.web.filter.HiddenHttpMethodFilter`

-> `org.springframework.web.filter.HttpPutFormContentFilter`
```java

// 处理 PUT 和 PATCH 

/**
PUT：client对一个URI发送一个Entity，服务器在这个URI下如果已经又了一个Entity，那么此刻服务器应该替换成client重新提交的，也由此保证了PUT的幂等性。如果服务器之前没有Entity ，那么服务器就应该将client提交的放在这个URI上。总结一个字：PUT.

OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT

PATCH 用于资源的部分内容的更新，例如更新某一个字段。具体比如说只更新用户信息的电话号码字段

https://unmi.cc/restful-http-patch-method/
*/
if (("PUT".equals(request.getMethod()) || "PATCH".equals(request.getMethod())) && this.isFormContentType(request)) {
    HttpInputMessage inputMessage = new ServletServerHttpRequest(request) {
        public InputStream getBody() throws IOException {
            return request.getInputStream();
        }
    };
    MultiValueMap<String, String> formParameters = this.formConverter.read((Class)null, inputMessage);
    if (!formParameters.isEmpty()) {
        HttpServletRequest wrapper = new HttpPutFormContentFilter.HttpPutFormContentRequestWrapper(request, formParameters);
        filterChain.doFilter(wrapper, response);
        return;
    }
}

filterChain.doFilter(request, response);

```

-> `org.springframework.web.filter.RequestContextFilter`
-> `org.apache.tomcat.websocket.server.WsFilter`

-> `javax.servlet.http` -> super `org.springframework.web.servlet.FrameworkServlet`
-> `javax.servlet.http.HttpServlet#service(HttpServletRequest req, HttpServletResponse resp)`
-> `javax.servlet.http.HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)`
-> `org.springframework.web.servlet.FrameworkServlet.processRequest(HttpServletRequest request, HttpServletResponse response)`
-> `org.springframework.web.servlet.DispatcherServlet.doService(HttpServletRequest request, HttpServletResponse response)`
-> `org.springframework.web.servlet.DispatcherServlet.doDispatch(HttpServletRequest request, HttpServletResponse response)`



通过 `org.springframework.web.servlet.mvc.method.RequestMappingInfo` 来记录 请求 与 Handler 的匹配条件

`org.springframework.web.servlet.handler.AbstractHandlerMethodMapping.MappingRegistry` 用来保存注册的信息，其中使用 Map 键值对保存




### java时间 处理

使用 `java.text.SimpleDateFormat` 格式化时间

```java
SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
String formatDateStr = sdf.format(date);
```

将字符串转化为 `Date` ，有 `ParseException` 异常抛出
```java
Date parseDate = sdf.parse("2018-02-27 22:11:40");
```

java 8 新增的时间处理类的一些使用列子

```java
LocalDate date = LocalDate.now();
LocalTime time = LocalTime.now();
LocalDateTime dateTime = LocalDateTime.now();

System.out.println("两小时后是： " + time.plusHours(2));

System.out.println("一周后的时间是： "+  date.plus(1, ChronoUnit.WEEKS));

LocalDate birthday = LocalDate.of(1994, 02, 18);
System.out.println("你的生日是: " + birthday);
LocalDate herBirthday = LocalDate.of(1993, 12, 05);
System.out.println(birthday.equals(herBirthday));

//判断日期是在前面还是在后面
System.out.println(birthday.isBefore(herBirthday));

//处理不同时区的时间

//当前时间戳
System.out.println(Instant.now());

//日期解析
String holidayStr = "1994/02/18";
DateTimeFormatter dateTimeFormatter = DateTimeFormatter.ofPattern("yyyy/MM/dd");
LocalDate holiday = LocalDate.parse(holidayStr, dateTimeFormatter);
System.out.println(holiday);

//日期格式化
System.out.println("我的生日是：" + birthday.format(dateTimeFormatter));
```

#### 参考
- http://blog.csdn.net/weixin_37577039/article/details/79229992
- http://blog.csdn.net/jiangxishidayuan/article/details/52049581


### HashMap 工作原理

push 操作 
```java
// 通过 hash() 方法 把 key 做 hash 当做 底层存储数组，或者链表的 index，利用 链表解决 hash 冲突
// 在 java 8 中 相同元素不再是按照链表存储在同一个桶中，以 红黑树的形式存在。
public V put(K key, V value) {
    return putVal(hash(key), key, value, false, true);
}

// hashmap 的初始值是 16
static final int DEFAULT_INITIAL_CAPACITY = 1 << 4; // aka 16

//通过这个算法能
static final int hash(Object key) {
    int h;
    return (key == null) ? 0 : (h = key.hashCode()) ^ (h >>> 16);
}
```


putVal 方法，可以看到，这里的方法是没有 同步 过程的，所以整个 HashMap 操作都是线程不安全的。如果每个方法都加关键字 synchronized 就编程 HashTable，如果采用 分段锁(1.7) CAS算法(1.8) 就是 ConcurrentHashMap，如果是 add emtpy bin 的情况，就不会锁
```java
final V putVal(int hash, K key, V value, boolean onlyIfAbsent,
                boolean evict) {
    Node<K,V>[] tab; Node<K,V> p; int n, i;
    if ((tab = table) == null || (n = tab.length) == 0)
        n = (tab = resize()).length;

        // 元素不存在就新建元素，存在就1， 放入到链表，2，放入到红黑树
    if ((p = tab[i = (n - 1) & hash]) == null)
        tab[i] = newNode(hash, key, value, null);
    else {
        Node<K,V> e; K k;
        if (p.hash == hash &&
            ((k = p.key) == key || (key != null && key.equals(k))))
            //hash 相同，直接替换
            e = p;
        else if (p instanceof TreeNode)
        // hash 不相同放入红黑树中
            e = ((TreeNode<K,V>)p).putTreeVal(this, tab, hash, key, value);
        else {
            for (int binCount = 0; ; ++binCount) {
                //循环找到链表尾巴
                if ((e = p.next) == null) {
                    p.next = newNode(hash, key, value, null);
                    //如果链表长度超过 8 就变形为 红黑树
                    if (binCount >= TREEIFY_THRESHOLD - 1) // -1 for 1st
                        treeifyBin(tab, hash);
                    break;
                }
                if (e.hash == hash &&
                    ((k = e.key) == key || (key != null && key.equals(k))))
                    break;
                p = e;
            }
        }
        if (e != null) { // existing mapping for key
            V oldValue = e.value;
            if (!onlyIfAbsent || oldValue == null)
                e.value = value;
            afterNodeAccess(e);
            return oldValue;
        }
    }
    ++modCount;

    //threshold=newThr:(int)(DEFAULT_LOAD_FACTOR * DEFAULT_INITIAL_CAPACITY);
        //默认0.75*16，大于threshold值就扩容
    if (++size > threshold)
        resize();
    afterNodeInsertion(evict);
    return null;
}
```


#### java 中单例模式的实现
```java

/**
 * 使用同步锁实现单例模式，线程安全
 */
public class Singleton {

    private static Singleton instance;

    public int count = 1;

    private Singleton() {
    }

    public static synchronized Singleton getInstance() {

        //这里可以使用双重校验来提高效率，只有第一次初始化会使用到同步锁
        if (instance == null) {
            instance = new Singleton();
        }
        return instance;
    }

}

/**
 * 静态属性实现
 */
class Singleton1 {
    private static final Singleton1 instance = new Singleton1();

    private Singleton1() {
    }

    public static Singleton1 getInstance() {
        return instance;
    }
}


/**
 * 静态内部类实现
 * 单例类初始化的时候可以做一些初始化动作
 */
class Singleton2 {
    private static class SingletonHandle {
        private static final Singleton2 INSTANCE = new Singleton2();
    }

    public Singleton2() {
        System.out.println("延迟加载");
    }

    public static Singleton2 getInstance() {
        return SingletonHandle.INSTANCE;
    }
}

/**
 * 枚举实现
 */
enum Singleton3 {
    INSTANCE;

    private int code = 0;

    public void otherMethod() {
        System.out.println("关于单例类的方法");
    }

    public int getCode() {
        return code;
    }

    public void setCode(int code) {
        this.code = code;
    }
}
```


### 面试

https://hacpai.com/article/1504434966657

#### 1. String 类为什么是 final 的。

String 是在开发中经常用到的， 所以需要效率，如果是 final 关键字就会直接定位到内存位置 ，还有就是 安全考虑

#### 2. HashMap 的源码，实现原理，底层结构。

HashMap 是基于 Hash 表的 Map 接口的非同步实现，HashTable 线程安全，但是不保证映射顺序，底层是一个数组 `transient Node<K,V>[] table;` 同时每隔数组的单元又是一个链表的头结点，当发生 Hash 冲突的时候，就会将元素存储在 链表的后继节上。在 JDK1.8 后，链表的长度超过 8 以后，就会转化成 红黑树进项保存 Hash 冲突的元素。Hash 的初始大小是 16， 如果超过 loadFacotr * table.length() 就会扩容，每次扩容的都是 2 的 n 次方倍，通过 key.hashCode 来计算放入 Node 数组的 index 值。

#### 3. 说说你知道的几个 Java 集合类：list、set、queue、map 实现类咯。。。
- public interface Collection<E> extends Iterable<E> 
    - List
        - `java.util.ArrayList` 底层实现 `transient Object[] elementData; // non-private to simplify nested class access` 一个 Object 数组，不过可以自动扩容。
        - `java.util.Vector`，线程安全，而 ArrayList 线程不安全, 当使用一个 Vector 的 Iterator 的时候，如果有线程正在修改 Vecotor 将跑出 `ConcurrentModificationException`，所以要捕获异常
        - `java.util.LinkedList` 线程不安全，底层是一个链表，ArrayList 读取最快，LinkedList 插入和删除最快
    - Set
        - `java.util.HashSet` 底层实现是把值存在 HashMap 的 key 上而所有的 Node 的 value 都是同一个对象 Object 线程不安全。
        - `java.util.LinkedHashSet` 按照插入顺序排列，底层就是用 LinkedHashMap 实现
        - `java.util.TreeSet` private transient NavigableMap<E,Object> m; 实现
    - Queue
        - `java.util.LinkedList`
        - LinkedBlockingQueue 同步
- Map
    - `java.util.HashMap`
    - weakhashMap
    - TreeMap
    - HashTable

#### 4. 描述一下 ArrayList 和 LinkedList 各自实现和区别

一个是 数组 一个是 Link 链表

#### 5. Java 中的队列都有哪些，有什么区别。
ConcurrentLinkedQueue， LinkedBlockingQueue， ArrayBlockingQueue， LinkedList


#### 6. 反射中，Class.forName 和 classloader 的区别

Class.forName 会初始化类 classloader 不会

```java
public class Hello {
    static{
        System.out.println("hello static block");
    }

    public Hello () {
        System.out.println("hello construct");
    }
}


public class Test {
    public static void main(String[] args) {
//        try {
    // 输出 hello static block
//            Class Hello = Class.forName("com.ykjver.demo.controller.Hello");
//        } catch (ClassNotFoundException e) {
//            e.printStackTrace();
//        }


        ClassLoader classLoader = ClassLoader.getSystemClassLoader();
        try {
            //不输出 hello static block
            classLoader.loadClass("com.ykjver.demo.controller.Hello");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
```


#### 7. Java7、Java8 的新特性 (baidu 问的, 好 BT)

#### 8. Java 数组和链表两种结构的操作效率，在哪些情况下 (从开头开始，从结尾开始，从中间开始)，哪些操作(插入，查找，删除) 的效率高

#### 9. Java 内存泄露的问题调查定位：jmap，jstack 的使用等等

#### 10. string、stringbuilder、stringbuffer 区别

String 不可变，StringBuilder 线程不安全，StringBuffer 线程安全

#### 11. hashtable 和 hashmap 的区别

HashTable 线程安全，HashMap 线程不安全

#### 13 . 异常的结构，运行时异常和非运行时异常，各举个例子

#### 14. String a= “abc” String b = “abc” String c = new String(“abc”) String d = “ab” + “c” . 他们之间用 == 比较的结果

#### 15. String 类的常用方法

indexOf, substring, charAt, length, valueOf, equals, equalsIgnoreCase, startsWith, endsWith, getBytes, getChars, split, toLowerCase, toUpperCase, replaceAll, replace, replaceFirst, trim, indexOf, lastIndexOf,isEmpty, join

#### 17. 抽象类和接口的区别
接口不能含有 静态代码块，不能有属性，只能有抽象方法。
#### 18. java 的基础类型和字节大小。


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

### 二、Java IO

#### 1. 讲讲 IO 里面的常见类，字节流、字符流、接口、实现类、方法阻塞。

面向字节，面向字符，
- OutputStream 
    - FileOutputStream
        - SocketInputSteam
    - ByteArrayOtputStream
    - FilterInputStream
        - BufferedInputStream
        - DataInputStream
        - ZipInputStream
    - ObjectInputStream
    - PipInputStream
- Writer
    - InputStreamWriter
    - BufferWriter
    - StringWriter
    - PipeWriter
    - PrintWriter
    - CharWriter

InputSreamReader 通过集成 Reader 组合 StreamDecoder 来讲字节流转化为字符流

#### 2. 讲讲 NIO。

noblocking IO,如果用一个线程对应一个连接，也可以使用非阻塞的 IO，基于事件，如果几百万的 HTTP 连接，只有少数在传输数据，那么久设计服务优先级，和资源竞争的问题。

#### 3.String编码UTF-8和GBK的区别



五、开源框架

1. hibernate 和 ibatis 的区别

2. 讲讲 mybatis 的连接池。

3. spring 框架中需要引用哪些 jar 包，以及这些 jar 包的用途

4. springMVC 的原理

5. springMVC 注解的意思

6. spring 中 beanFactory 和 ApplicationContext 的联系和区别

7. spring 注入的几种方式（循环注入）

8. spring 如何实现事物管理的

9. springIOC

10. spring AOP 的原理

11. hibernate 中的 1 级和 2 级缓存的使用方式以及区别原理（Lazy-Load 的理解）

12. Hibernate 的原理体系架构，五大核心接口，Hibernate 对象的三种状态转换，事务管理。

#### 2.什么是快速失败的故障安全迭代器?

快速失败的Java迭代器可能会引发ConcurrentModifcationException在底层集合迭代过程中被修改。故障安全作为发生在实例中的一个副本迭代是不会抛出任何异常的。快速失败的故障安全范例定义了当遭遇故障时系统是如何反应的。例如，用于失败的快速迭代器ArrayList和用于故障安全的迭代器ConcurrentHashMap。

#### 　3.Java BlockingQueue是什么?

Java BlockingQueue是一个并发集合util包的一部分。BlockingQueue队列是一种支持操作，它等待元素变得可用时来检索，同样等待空间可用时来存储元素。使用 ReentrantLock 实现了同步

#### 参考
- http://www.cnblogs.com/mxw00927/p/7171598.html

2018-02-27
Updating...