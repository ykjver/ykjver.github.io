---
layout: post
title:  "java基础-框架中运用到的反射和注解"
date:   2015-12-13 03:30:00
categories: java
author : 自来也
---

java中的框架很多都会用到反射(reflect)和注解(annotion)，可以这样说，如果要清楚框架的很多用法，和实现原理就需要搞清楚反射和注解的使用和实现原理。

###反射

通过java类类型获取java类的基本信息，如属性信息，方法信息，构造方法信息，这些信息包括属性作用域，属性类型，或者方法的返回值类型，方法名称，方法的测试，生命抛出的异常等。同时，通过方法信息可以执行对特定对象的方法调用，从而动态的对类进行加载和对方法的调用


###注解

注解的是java5.0后的才有的，注解通常的作用是用作描述一个类、字段、方法、构造器、参数、变量所带有的特殊属性，例如，在下面`Student`类要和数据库中的student表进行映射从而可以通过传入Student实例动态生产查询语句。就需要用注解对每个字段还有类描述

@Table("student")
public class Student {
	private String name;
	private String email;
	private int age;

	public Student() {
		super();
	}

	public Student(String name, String email, int age) {
		super();
		this.name = name;
		this.email = email;
		this.age = age;
	}

	@Column("name")
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	@Column("email")
	public String getEmail() {
		return email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	@Column("age")
	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}
}


因为通过反射机制可以对类进行动态加载，对方法进行动态的调用，分析类信息，其中。类信息就可以通过注解来携带对类和类中的方法、构造器、属性、方法参数等描述信息，从而达到通过自定义注解和反射帮我们做类似于下面的事情

1. 在spring中通过`@Autowire`自动注入其他类到该类中，通过`@Service`来表明一个业务逻辑类，通过`@Entity`表示一个实体类
2. 在Hibernate中在实体类中通过`@Table`代表该类对应数据库中的表名称，通过`@Column`表明一个实体类属性和数据库中表字段映射关系


大多数框架都允许通过xml,property,text,注解等多种方式来对框架进行配置，在这里可以这样理解，注解其实就是和xml文件的作用是一样的，提过框架中反射需要用到的信息，只不过xml文件是把这些类信息独立到单独的文件中去了，而注解则是把需要的类描述信息独立到了类中的费业务逻辑代码区域。

待续~~



###REFERENCE

- (深入理解Java：注解（Annotation）--注解处理器)[http://www.cnblogs.com/peida/archive/2013/04/26/3038503.html]