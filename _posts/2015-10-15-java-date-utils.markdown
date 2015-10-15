---
layout: post
title:  "Date Util"
date:   2015-10-15 23:10:45
categories: java
author : 自来也
---


写一个 日期工具类，需要用到的类有 `java.text.SimpleDateFormat`, `java.util.Date`, `java.util.Calendar`

###java.text.SimpleDateFormat

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