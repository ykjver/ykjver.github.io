---
layout: post
title:  "servelt学习（一）-servelt初步"
date:   2015-11-16 23:10:45
categories: java 
author : 自来也
---

##servlet初级


servlet和applet相对，前者运行在服务端而后则运行在客户端。作为java web服务端开发人员，或多或少或了解并且使用过servlet，简单的理解servlet就是准守 java servlet api所编写的类，只要是准守这一api的类就就可以放在servlet容器中，如tomcat、jetty等，这样servlet容器就能把解析到的http协议信息通过事先定义好的java servlet api调用传给我们写的servlet类中，在类中我们队http请求做出相应请求，然后产生相应的返回信息传给servlet容器，servlet容器帮我们转化成http协议然后返回给服务端。

只要实现了servlet，servlet容器就能够调用servlet实现类进行处理请求

servlet主要包含下面一些类型的功能

- 处理http请求 servlet
	- servlet 初始化 ini
	- servlet 处理 service
	- servlet 销毁 destory
- 统一过滤、处理http请求 filter
	- filter 初始化 init
	- filter 处理 dofilter
	- filter 销毁 destory
- http请求过程中的事件监听 listener
	- listerner 初始化 init
	- listerner 销毁 desctory




编写servlet所要用到的接口和类javax.servlet这个包中，具体包含哪些接口、类看官方文档[tomcat-7.0-doc](https://tomcat.apache.org/tomcat-7.0-doc/)

先编写一个能运行起来的servlet类

	package com.ykjver.summer.web;

	import java.io.IOException;
	import java.io.PrintWriter;

	import javax.servlet.http.HttpServlet;
	import javax.servlet.http.HttpServletRequest;
	import javax.servlet.http.HttpServletResponse;

	public class MyFirstServlet extends HttpServlet{

		private static final long serialVersionUID = 1L;
		
		@Override
		public void doGet(HttpServletRequest request, HttpServletResponse response) {
			PrintWriter out = null;
			try {
				out = response.getWriter();
				out.println("<h1>Hello Summer</h1>");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally{
				try {
					out.close();
				} catch (Exception e2) {
					// TODO: handle exception
				}
			}
		}

	}


然后再在web.xml中配置servlet，为了在浏览器中输入相应的url能找到上面的servlet类来处理，即可以理解成在web.xml中配置url路径和servlet类的映射关系,web.xml配置如下

	<?xml version="1.0" encoding="UTF-8"?>
	<web-app xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns="http://xmlns.jcp.org/xml/ns/javaee" xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd" id="WebApp_ID" version="3.1">
	  <display-name>servlet1</display-name>
	  
	<servlet>
		<servlet-name>myFirstServlet</servlet-name>
	 	<servlet-class>com.ykjver.summer.web.MyFirstServlet</servlet-class>
	</servlet> 
	 
	<servlet-mapping>
		<servlet-name>myFirstServlet</servlet-name>
		<url-pattern>/myFirstServlet</url-pattern>
	</servlet-mapping>
	  
	  <welcome-file-list>
	    <welcome-file>index.jsp</welcome-file>
	  </welcome-file-list>
	</web-app>

servlet便签是用来配置servlet类，相当于注册一个名字叫“myFirstServlet”的servlet，对应处理他的类是com.ykjver.summer.web.MyFirstServlet，这个servlet对应的url为 /myFirstServlet

当然，如果不通过xml这种方式进行配置的话，还可以同的annotation注解的方式来配置servlet方式如下,通过@WebServlet注解

	@WebServlet(name="annocationServlet", urlPatterns="/annocationServlet")
	public class AnnocationServlet extends HttpServlet{

		private static final long serialVersionUID = 1L;

		public void doGet(HttpServletRequest request, HttpServletResponse response) {
			PrintWriter out = null;
			try {
				out = response.getWriter();
				out.println("<h1>Hello Summer</h1>");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally{
				try {
					out.close();
				} catch (Exception e2) {
					// TODO: handle exception
				}
			}
		}

	}

通过上面的配置，就可以完成一个servlet的初步编写配置，通过IDE编译后就可以在servlet容器中运行了。



-- 待续





###Reference

- [Java Servlet完全教程](http://www.importnew.com/14621.html)