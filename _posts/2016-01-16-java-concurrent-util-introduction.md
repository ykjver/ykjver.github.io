---
layout: post
title:  "java并发工具包之同步器-修改"
date:   2016-01-16 23:59:59
categories:  java
author : 自来也
---

java并发工具包主要包含下面内容

- 同步器：为特定条件的同步问题提供的解决方案
	- Semaphore（计数信号量）
	- CountDownLatch（计数栓）
	- CyclicBarrier
	- ExChanger
	- Phaser
- 执行器：用来管理线程的执行，典型的应用就是线程池
- 并发集合：提供集合框架中的集合的并发版本
- Fork/Join框架：提供对并行编程的支持
- atomic包：提供不需要锁就可以完成并发原子性操作的变量
- locks包：synchronized的一种替代解决方案

###Semaphore，计数信号量同步器

Semaphore同步器，主要解决控制某个资源最多被同时访问的线程数，通过`acquire`获取许可，当许可被领取完后需要领取许可的线程就等待拥有许可的线程释放许可。

就例如，在银行中的服务人员是一定数量的，同一时间只能服务一个客户，来一个客户就减少一个空闲的服务人员，当没有空闲的服务人员时，这是客户就需要排队等待了，就是这样一个模型。

Semaphore带两个参数的构造器`public Semaphore(int permits, boolean fair)`，第一个参数是许可（信号量）的个数，第二个参数是是否公平，如果为true，将线程FIFO获取信号量许可，为false则不保证FIFO。

实例如下，银行只能同时接待两个客户。

	public class Test1 {
		public static void main(String[] args) {
			Semaphore semaphore = new Semaphore(-1, true);
			new Person(semaphore, "A").start();
			new Person(semaphore, "B").start();
			new Person(semaphore, "C").start();
			new Person(semaphore, "D").start();
		}
	}

	class Person extends Thread {
		private Semaphore semaphore;

		public Person(Semaphore semaphore, String name) {
			this.semaphore = semaphore;
			setName(name);
		}

		@Override
		public void run() {
			try {
				System.out.println(getName() + " is waiting....");
				semaphore.acquire();
				System.out.println(getName() + " is serving....");
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			
			System.out.println(getName() + " is done");
			semaphore.release();
		}
	}


###CountDownLatch，计数栓同步器

CountDownLatch主要解决的同步问题是，当某事件发生指定次数后，等待的线程被同时唤醒访问资源，例如运动员在听到倒计时时都在等待，当三声倒计时完后同时开跑。这里暗示着，某事件发生一次，计数就减少一次，当减少到0时，等待的线程就同时被唤醒。

例子如下，描述4位运动员等待3声枪响后开跑。

	public class CountDownLatchDemo {
		public static void main(String[] args) {
			CountDownLatch countDownLatch = new CountDownLatch(3);
			new Player(countDownLatch, "关羽").start();
			new Player(countDownLatch, "张飞").start();
			new Player(countDownLatch, "曹操").start();
			new Player(countDownLatch, "赵云").start();
			
			try {
				Thread.sleep(2000);

				for(int i=3; i>0;i--) {
					System.out.println(i);
					Thread.sleep(1000);
					countDownLatch.countDown();
				}
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}

	class Player extends Thread {
		private CountDownLatch countDownLatch;

		public Player(CountDownLatch countDownLatch, String name) {
			this.countDownLatch = countDownLatch;
			setName(name);
		}

		@Override
		public void run() {
			try {
				System.out.println(getName() + " 运动员就绪等待");
				countDownLatch.await();
				for (int i = 3; i >= 0; i--) {
					System.out.println(getName() + " 离终点还有" + i + "米");
				}
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}


###CyclicBarrier，循环屏障同步器

CyclicBarrier，主要解决的同步问题是，等待线程必须达到指定个数后开始执行所有等待线程，同时可以指定满足条件后的任务。要达到一定数量的线程等待后才开放让这些数量的线程同时一起访问，例如，打麻将，一个人来到牌桌前，等待，第二个人来也等待，等到第四个人来时，就开始搓麻将了

CyclicBarrier带两个参数的构造方法为`public CyclicBarrier(int parties, Runnable barrierAction)`，第一个参数是屏障打开前，`await()`方法必须被调用的次数，第二个参数则为满足前者条件后执行的命令。

例子如下，模拟4个人搓麻将，要等到4个人来齐了后，执行开始搓麻将的操作

	public class CyclicBarrierDemo {

		public static void main(String[] args) {
			CyclicBarrier cyclicBarrier = new CyclicBarrier(4, new Runnable() {

				@Override
				public void run() {
					System.out.println("4个人来齐了，开始搓麻将。");
				}
			});

			new MaJiangFriend(cyclicBarrier, "马努·吉诺比利").start();
			new MaJiangFriend(cyclicBarrier, "王珞丹").start();
			new MaJiangFriend(cyclicBarrier, "阿尔伯特·爱因斯坦").start();
			new MaJiangFriend(cyclicBarrier, "科比·布莱恩特").start();
		}
	}

	class MaJiangFriend extends Thread {

		private CyclicBarrier cyclicBarrier;

		public MaJiangFriend(CyclicBarrier cyclicBarrier, String name) {
			this.cyclicBarrier = cyclicBarrier;
			setName(name);
		}

		@Override
		public void run() {
			try {
				System.out.println(getName() + "，正在等待麻友。");
				cyclicBarrier.await();
			} catch (InterruptedException e) {
				e.printStackTrace();
			} catch (BrokenBarrierException e) {
				e.printStackTrace();
			}
		}
	}


###Exchanger，配对数据交换同步器。

Exchanger，是用来在两两配对的线程进行数据交换同步的，意思是，两两配对的线程都准备好交换的数据时，才进行交换，例如生活中，我们答应对方互相准备礼物，然后互相交换，如果只是单方面的准备好礼物，就还没有达到交换的条件，需要双方礼物都准备好了，约个时间地点进行交换。在实际应用中，例如一个线程的作用是专门做缓区器清理，一个线程使用需要使用清理好的缓冲区，使用完毕后需要交给清理线程做清理，这里就可以使用Exchanger同步器，如果单方面清理线程清理好缓冲区了，但是另一个线程不需要，此时改线程就进入等待。反之同理。

例子如下，模拟两个人一问一答，如果其中一个人没有回复，那么对方将等待其回答。

	public class ExchangerDemo {

		public static void main(String[] args) {
			Exchanger<String> exchanger = new Exchanger<>();
			new A(exchanger).start();
			new B(exchanger).start();
			new B(exchanger).start();
		}

	}

	class A extends Thread {

		private Exchanger<String> exchanger;

		public A(Exchanger<String> exchanger) {
			this.exchanger = exchanger;
		}

		@Override
		public void run() {
			try {
				String str = exchanger.exchange("Hello!");
				System.out.println(str);
				str = exchanger.exchange("oh! my god!");
				System.out.println(str);
				str = exchanger.exchange("我是歌手");
				System.out.println(str);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	class B extends Thread {

		private Exchanger<String> exchanger;

		public B(Exchanger<String> exchanger) {
			this.exchanger = exchanger;
		}

		@Override
		public void run() {
			try {
				String str = exchanger.exchange("Hi!");
				System.out.println(str);
				str = exchanger.exchange("oh! a u kidding me!");
				System.out.println(str);
				str = exchanger.exchange("我是演员");
				System.out.println(str);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

###Phaser

Phaser和CyclicBarrier有点类似，但是CyclicBarrier只有一次等待大家一起跑的同步，Phaser可以分阶段的同步，例如环法骑车比赛吧，分很多赛段，大家在单个赛段到达时间是不同的，但是，从这个赛段出发时同时的。先到达的需要等待其他参赛选手。通过`register()`方法将该线程注册到Phaser同步器中。通过`ArriverAndAwaitAdvance()`方法通知线程等待，通过`arriveAndDeregister()`方法作为最后一次同步，然后把改线程注销出Phaser同步器中。

下面的例子，模拟的是“厨师”、“服务员”、“收银员”，每次只能完成一个订单的所有内容才能继续服务下一个订单（这显然是有点不现实）

	public class PhaserDemo {

		public static void main(String[] args) throws InterruptedException {

			Phaser phaser = new Phaser(1);
			new Worker(phaser, "服务员").start();
			new Worker(phaser, "厨师").start();
			new Worker(phaser, "收银员").start();

			for (int i = 1; i <= 3; i++) {
				phaser.arriveAndAwaitAdvance();
				System.out.println("订单" + i + "完成");
			}

			phaser.arriveAndDeregister();
		}
	}

	class Worker extends Thread {
		private Phaser phaser;

		public Worker(Phaser phaser, String name) {
			setName(name);
			this.phaser = phaser;
			phaser.register();
		}

		@Override
		public void run() {
			for (int i = 1; i <= 3; i++) {
				System.out.println(getName() + "：这是第" + i + "个订单");
				if (i == 3) {
					phaser.arriveAndDeregister();
				} else {
					phaser.arriveAndAwaitAdvance();
				}
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}

###REFERENCE

- [Java：多线程，Semaphore同步器](http://www.cnblogs.com/nayitian/p/3317250.html)