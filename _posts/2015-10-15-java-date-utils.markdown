---
layout: post
title:  "Date Util"
date:   2015-10-15 23:10:45
categories: java
author : 自来也
---


写一个 日期工具类，需要用到的类有 `java.text.SimpleDateFormat`, `java.util.Date`, `java.util.Calendar`

##java.text.SimpleDateFormat

`SimpleDateFormat`继承自`DateFormat`，用来格式化(format, date->text)日期类(`Date`)或者解析(parse, text->date)日期字符串。

[SimpleDateFormat](https://docs.oracle.com/javase/8/docs/api/java/text/SimpleDateFormat.html)中指出:

>Date formats are not synchronized. It is recommended to create separate format instances for each thread. If multiple threads access a format concurrently, it must be synchronized externally.

说明`SimpleDateFormat`是非线程安全的，所以下面这段代码在并发状态下是错误的，而且引发的bug也很难发现

	class DateUtil {
		public final static SimpleDateFormat SDF = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		
		public static String format(Date date){
			/*
			*return new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(date)
			*这样是没有问题的，但是实例化SimpleDateformat开销较大,这样效率不好,但是总比有问题好 - -||
			*/

			return SDF.format(date);
		}
		
		public static Date parse(String dateStr) throws ParseException{
			return SDF.parse(dateStr);
		}
	}

在上一段代码中，为了节省实例化`SimpleDateFormat`时间，就设置了一个公用的`SimpleDateFormat`实例，这也是问题所在，在JDK源码中`SimpleDateFormat.format`是这样实现的， [SimpleDateFormat的源码](http://www.docjar.com/html/api/java/text/SimpleDateFormat.java.html):

	private StringBuffer format(Date date, StringBuffer toAppendTo,
	                             FieldDelegate delegate) {
	    // Convert input date to time field list
	    //在这里这个Calendar是SimpleDateFormat父类DateFormat中的一个属性
	    calendar.setTime(date);

	    boolean useDateFormatSymbols = useDateFormatSymbols();

	    for (int i = 0; i < compiledPattern.length; ) {
	        int tag = compiledPattern[i] >>> 8;
	        int count = compiledPattern[i++] & 0xff;
	        if (count == 255) {
	            count = compiledPattern[i++] << 16;
	            count |= compiledPattern[i++];
	        }

	        switch (tag) {
	        case TAG_QUOTE_ASCII_CHAR:
	            toAppendTo.append((char)count);
	            break;

	        case TAG_QUOTE_CHARS:
	            toAppendTo.append(compiledPattern, i, count);
	            i += count;
	           	break;

	       	default:
	       		//在这个方法中又使用了calendar这个属性
	           	subFormat(tag, count, delegate, toAppendTo, useDateFormatSymbols);
	          	break;
	      	}
	  	}
	    return toAppendTo;
	}


发现问题了吧，`subFormat`方法为了省一个参数，导致这个方法线程不安全的咯，发生问题情境如下

1. Thread-1进入format并设置了calendar
2. Thread-1进入subFormat，还没有使用calendar
3. Thread-2进入format并设置了calendar
4. Thread-1使用calendar，此时的calendar已被Thread-2修改


## java.util.Date

在这个类中，仅有`before`, `after`, `getTime`, `compareTo`还在使用，其他的已经被`Calendar`类代替


## java.util.Calendar

对Date的替代，在Date中的很多方法已被Calendar中的方法替代,Calendar是一个抽象类，通过Calendar.getInstance获取Calendar实例，Canlendar有一个子类


### Date和Calendar的互相转化


	//得到现在的时间
	Calendar c = Calendar.getInstance();
	Date date = c.getTime();

	//和这个一样
	Date date = new Date();
	c.setTime(date);

### Calendar和时间戳的互相转化

	long milliseconds = c.getTimeInMillis();
	c.setTimeInMillis(1445667314543)



### Calendar时间域的设置、操作和取得时间域

返回每个时间域的之 int get(int field) 例如返回该天数在一月中的天数，参数filed位Calendar类中的静态变量

	c.get(Calendar.DAY_OF_MONTH)

设置时间，void set(int field, int value) set方法还有很多重载方法，本方法为设置制定数据域的值，在setLenient(boolean lenient)设置为true或者为默认状态下，即使设置的改数据域超过了本身大小，也能自动转换

	//这样相当于这个月加上下个月的天数，默认状态，或者
	//setLenient(true)
	c.set(Calendar.DAY_OF_MONTH, 50);

	//如果是下面这种请过就必须准守严格是时间域设置，将会java.lang.IllegalArgumentException异常
	c.setLenient(false)
	c.set(Calendar.DAY_OF_MONTH, 50);

设置一周的第一天是星期几，比如我们国家的一周的第一天是星期一，而美国一周的第一天是星期天，void setFirstDayOfWeek(int value)

	c.setFirstDayOfWeek(Calendar.SUNDAY);


增加或减少制定时间域的数值 void add(int field, int amount) field为时间域，amount为时间增加减少量，正数为增加，负数为减少

	c.add(Calendar.YEAR, 2);
	c.add(Calendar.MONTH, -3);

比较两Calendar之间的前后，时间前后 boolean before(Object when), boolean after(Object when)，int compareTo(Calendar anotherCalendar)
	
	c.after(c1);
	c.before(c1);

	//比较两个Calendar，如果牵着大于后者就返回1，相等返回0，小于返回-1
	c.compareTo(c1)

让时间清零，让时间回到1970-01-01 00:00:00 ，void clean()，或者是让指定的时间域清零

	c.clean()
	c.clear(Calendar.MONTH);


得到时间域的最大值和最小值int getActualMaximum(int field), int getActualMinimum(int field)

	c.getMaximum(Calendar.YEAR)
	c.getMinimum(Calendar.YEAR)


### 地区化

得到所有可用地区Local[] getAvailableLocales()

得到失去信息 TimeZone getTimeZone(), 设置失去信息 void setTimeZone(TimeZone value)