---
layout: post
title:  "Java中interface和abstract class的区别"
date:   2015-12-20 01:44:45
categories:  Data Structures And Algorithm
author : 自来也
---


###抽象类简单定义

抽象类是带有抽象方法的类，意思就是说，如果一个类带有抽象方法，就必须使用`abstract`关键字定义其为抽象方法，抽象方法是带有`abstract`关键字的方法，抽象方法是没有方法体的方法如下

	public abstract class Animal {
	    public abstract void voice();
	}

上面`Animal`类就是一个抽象类，他带有抽象方法`public abstract void voice()`，这个方法并没有具体的实现。

**抽象类不能被实例化，只能被子类继承，当父类所有的抽象方法都被实现并且子类并不带有自己的抽象方法，子类为具体类，否则子类还是抽象类。**

下面用几个类继承上面的`Animal`方法

	public class Cat extends Animal {

	    @Override
	    public void voice() {
	        System.out.println("miao miao miao miao miao");
	    }
	}


	public class Dog extends Animal {

	    @Override
	    public void voice() {
	        System.out.println("wang wang wang wang wang");
	    }
	}


`Animal`类中的`voice`方法被定义成抽象的，是因为找不到一个具体的voice方式，对于Animal（动物）来说，Animal类并不是一个具体的动物，这就是为什么把Animal类定义成一个抽象类的原因，任何继承Animal类的子类都必须满足一下**条件之一**

1. 子类必须实现voice抽象方法
2. 子类也是抽象类


###Java接口简单定义

接口不是一个类，这是和抽象类的区别之一，接口就是一种类型，可以被任何类所实现（具体类和抽象类）

任何类要实现一个接口必须实现这个接口中定义的所有方法，下面是一个简单的例子

	public interface Usb {
		//开始工作
		void start();
		//停止工作
		void stop();
	}

	public class Flash implements Usb {

		@Override
		public void start() {
			// TODO Auto-generated method stub
			System.out.println("U盘开始工作");
		}

		@Override
		public void stop() {
			// TODO Auto-generated method stub
			System.out.println("U盘停止工作");
		}

	}
	
	public class Printer implements Usb {

		@Override
		public void start() {
			// TODO Auto-generated method stub
			System.out.println("打印机开始工作");
		}

		@Override
		public void stop() {
			// TODO Auto-generated method stub
			System.out.println("打印机停止工作");
		}

	}


Usb是一个接口，定义了两个方法`start()`和`stop()`，开始工作和停止工作，`Flash`类和`Printer`都实现了他，即实现接口中定义的两个方法。





###接口和抽象类的不同


**1.接口只描述功能，抽象类更注重关系**

使用抽象类，意味着是使用继承实现子类，这就是一种关系的象征，比如`Animal`类和`Dog`类还有`Cat`类，后面两个类明显就是一种动物，他们之间有层级关系。在看接口，如果一个类去实现接口，仅仅表示他有这个接口功能，而不能表示实现类就是接口，例如`Flash`（U盘）实现了`Usb`接口，就表明他有Usb接口定义的功能，就能插到电脑的Usb插孔上，但是不代表Flash和Usb之间有什么关系，一个网上卖的小电风扇也可以实现一个Usb接口，就能插到Usb接口上吹风，但小电扇并不是Usb，他仅仅是拥有Usb功能。

**2.抽象类可以提供一些实现了的方法**

抽象类可以提供实现的方法和抽象方法，还有private方法等，但是接口只能提供抽象的public方法

**3.接口可以实现多继承**

在java中类之间只能单一继承extends，但是接口却可以多实现例如下面 

	public class Flash implements Usb, VideoCard {

		@Override
		public void start() {
			// TODO Auto-generated method stub
			System.out.println("U盘开始工作");
		}

		@Override
		public void stop() {
			// TODO Auto-generated method stub
			System.out.println("U盘停止工作");
		}

	}

明显上面的这个FlashU盘是技能插Usb也能插PCI插槽，因为实现了Usb接口也实现VideoCar接口，看起来有点奇怪的U盘，但只要实现了厂商固定的接口，确实就能插。


###啥时候用接口，啥时候用抽象类

下面几点总结关于接口和抽象类的使用

1. 当想要使用继承，并提供一个模板类来供子类继承，这时用抽象类好点。
2. 如果想要提供非public方法给子类，就要用抽象类，接口的方法都是public的。
3. 如果将来还要修改类中的某些方法，使用抽象类。
4. 当提供API时，突出某种功能，并不是层级关系时，一般不会修改方法，使用接口
5. 当要实现多继承时使用接口。



###REFERENCE

- [What’s the difference between an interface and an abstract class in Java?](http://www.programmerinterview.com/index.php/java-questions/interface-vs-abstract-class/)
- [How should I have explained the difference between an Interface and an Abstract class?](http://stackoverflow.com/questions/18777989/how-should-i-have-explained-the-difference-between-an-interface-and-an-abstract)