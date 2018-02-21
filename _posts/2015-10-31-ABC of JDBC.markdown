---
layout: post
title:  "JDBC的一些知识"
date:   2015-10-31 23:10:45
categories: java
author : 自来也
---


###什么是JDBC（简介）

JDBC 从字面上理解应该是Java DataBase Connectivity（Java 数据库连接），可是Oracle却声明，其并非是JavaDataBase Connectivity 首字母缩写，只是向ODBC致敬而已:)。

JDBC是Java连接数据库的API，通过JDBC执行SQL对数据库进行查找与更新。与之类似的犹如PHP中的mysql扩展类似，使得本语言有了一套访问数据库的通用方法，不同的是，JDBC更统一，它提供了一套标准的数据库访问协议，每个数据库厂商都符合JDBC标准的数据库驱动程序，这样的驱动程序就能够想JDBC的驱动管理器注册自己，然后Java程序员就可以通过这个驱动管理区管理不同的数据库驱动（例如Mysql，DB2等）进而与其对应的数据库进行通信

####JDBC驱动

上面提到每个数据库供应商提供的数据驱动程序随着时间的发展主要是分下面4种

- JDBC-ODBC桥，这类驱动就是将JDBC翻译成ODBC,ODBC负责和数据打交道的，现在基本都不用了
- Java代码和一部分本地代码组合工作，与数据库进行通信，这类驱动除了需要安装Java类库之外，还需要安装本地程序与之一起工作
- 纯Java客户端类库，使用此类驱动，客户端将JDBC请求转化为协议无关请求发送到服务器，服务器再转化为不同数据库的协议请求，这种模式相当于把各种协议的兼容放在了服务端做
- 纯Java类库，和第三种驱动相比，这种驱动程序直接将JDBC请求转化为数据库相关协议发送到数据库。

通过驱动这种方式，就如同PC机一样，在主板上定义一套标准接口，然后显卡厂商都准守这个接口，专门对显卡进行制作，优化，将主板生产和显卡生产分离开来。对于Java程序员来说，他们不必在意各种不同的数据库访问协议，只需要学习Java制定数据库连接标准接口，就可以使得程序用上数据库对数据进行存储，而对于不同数据库的优化，更新工作，则由各个数据库供应商负责咯。

###怎么样才能使用JDBC（配置）

在配置JDBC之前，需要先下载安装数据库系统程序，如IBM DB2， MySQL，Oracle，PostgreSql等，这里我使用MySQL，然后下载Mysql的数据库驱动，将jar包加入到CLASSPATH中，然后可以再程序中国使用MySQL，下面的例子操作数据库中jdbctest这种新建的表，数据库结构如下

	CREATE DATABASE jdbctest;

	CREATE TABLE `jdbctest`.`authors` ( 
		`id` INT NOT NULL AUTO_INCREMENT , 
		`name` VARCHAR(255) NOT NULL , 
		PRIMARY KEY (`id`)
	) ENGINE = InnoDB charset utf8;

	CREATE TABLE `jdbctest`.`books` ( 
		`id` INT NOT NULL AUTO_INCREMENT ,
		`name` VARCHAR(255) NOT NULL , 
		`isbn` VARCHAR(20) NOT NULL , 
		`publisher_id` INT NOT NULL , 
		`price` DECIMAL(6,2) NOT NULL , 
		PRIMARY KEY (`id`)
	) ENGINE = InnoDB charset utf8;

	CREATE TABLE `jdbctest`.`publisher` ( 
		`id` INT NOT NULL AUTO_INCREMENT , 
		`name` VARCHAR(255) NOT NULL , 
		`url` VARCHAR(255) NOT NULL , 
		PRIMARY KEY (`id`)
	) ENGINE = InnoDB charset utf8;


当把MySQL驱动程序加入到classpath中，静态加载数据库驱动

	Class.forName(com.mysql.jdbc.Driver);

调用驱动管理器注册驱动
	
	/**
	 * url-MySQL数据库连接地址
	 * user-数据库用户名
	 * password-数据库密码
	 */
	DriverManager.getConnection(url, user, password);

整个数据库连接过程如下
	Connection conn = null;
	try {
        Class.forName("com.mysql.jdbc.Driver").newInstance();

	    conn = DriverManager.getConnection("jdbc:mysql://localhost/test?" +
	                                   "user=minty&password=greatsqldb");

	    // Do something with the Connection

	} catch (SQLException ex) {
	    // handle any errors
	    System.out.println("SQLException: " + ex.getMessage());
	    System.out.println("SQLState: " + ex.getSQLState());
	    System.out.println("VendorError: " + ex.getErrorCode());
	}

###使用JDBC执行SQL（使用）

连接上数据库，就可以执行SQL语句对数据库操作，通常有三种执行SQL的方法。

boolean execute(String sqlStatement)：执行指定SQL，可能产生多个结果集（select）或多个更新计数（insert，delete，update等），如果返回的第一个结果是结果集，返回true，通过getResultSet得到第一个返回集。否则返回false，通过getUpdateCount得到第一个受影响行数。

	conn = getConnection();
	Statement stat = conn.createStatement();
	boolean isSelect = stat.execute("insert into authors (id, name) values (null, 'summer')");
	if(isSelect) {
		System.out.println("exec select statement");
		ResultSet resultSet = stat.getResultSet();
	}else {
		System.out.println("exec udpate delete insert or ddl statement");
		int affectedRows = stat.getUpdateCount();
	}


ResultSet executeQuery(String sqlStatement)：执行执行SQL，返回查询结果集，用于select查询

	//getConnection为获得数据库连接的方法
	conn = getConnection();
	Statement stat = conn.createStatement();
	int affected = stat.executeUpdate("insert into authors (id, name) values (null, 'summer')");
	System.out.println(affected);

int executeUpdate(String sqlStatement)：执行udpate，insert，delete，SQL语句，还有DDL语句，例如create table， 返回受影响行数，如果没有更新数据，返回0。

###使用JDBC执行带参数的SQL prepared statement

执行带参数SQL查询写法如下

	conn = getConnection();
	PreparedStatement pstat = conn.prepareStatement("select title from news limit ?");
	pstat.setInt(1, 3);
	ResultSet rs = pstat.executeQuery();

使用conn.prepareStatement，来获取预备语句对象PreparedStatment,然后把要加入SQL如遇中的参数用"?"代替，然后使用setXXX来给预备语句添加参数的值，第一个参数是?的位置，第二个参数是SQL中欧参数的值，使用预备查询主要有三个优点

- 程序中不用每次去拼查询语句的的参数，查询语句只需要写一次，可以多次使用，遇到不同的参数直接通过方法修改参数的值就可以再次执行，给程序减少了代码量，也更清晰了
- 效率比起查询对象Statement高，因为数据库会缓存查询策略，不用每次把SQL语句转化为查询策略。
- 安全性更高，防止SQL注入


###返回数据处理（结果集） ResultSet

执行查询语句后返回的查询结果 
	ResultSet rs = stat.executeQuery();

通过 boolean next()，将当查询结果行移动到下一行，如果是随后一行则返回false，如果是初次使用，移动到第一行

通过getXXX来获取每一行中的的值，参数如果是整数，就是获取第几个的值（这里的下标是从1开始的），如果是字符串则是获得每一行字段名称对应的值。

	rs.getString("titile");

通过 T getObject(String columeLabel, Class<T> type)，通列标签（字符串）或者序列号获取列值，并转化为制定的类型

###可滚动可更新的的结果集

	Statement stat = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);

第一个参数制定是否可以滚动和对数据库变化敏感，第二参数用于制定是否可更新到数据库中

	Statement stat = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
	ResultSet rs = stat.executeQuery("select * from news limit 10");
	while(rs.next()){
		System.out.println(rs.getString("title"));
		System.out.println(rs.getRow());
	}
	rs.relative(-3);
	System.out.println(rs.getString(1));
	rs.updateString("title", "summer");
	rs.updateRow();

如果是可滚动的那，那么就可以执行ResultSet的一些滚动才做方法如relative，制定向前或者向后滚动Row，如果是可更新的就可以执行ResultSet的一些更新操作，如updateString， updateInt，等，在滚动到其他行之前，执行updateRow方法更新修改过的数据库

###行集

结果集ResultSet在整个与数据库交互总时总是保持连接，如果与客户端的交互不是集中一次完成，而是分时段随机交互，那么如果使用结果集ResultSet在整个过程都会与数据库保持连接，但是，数据库连接资源是稀缺资源，在这种情况下，就可以使用行集RowSet，他可以不用时刻都和数据库保持连接，行集的CachedRowSet简单使用如下

	RowSetFactory factory = RowSetProvider.newFactory();
	CachedRowSet crs = factory.createCachedRowSet();
	crs.setUrl(url);
	crs.setUsername(user);
	crs.setPassword(password);
	crs.setCommand("select * from news");
	crs.setPageSize(20);
	crs.execute();
	while(crs.next()){
		System.out.println(crs.getString("title"));
	}


###元数据 MetaData

描述数据库组或者其组成部分的数据叫做元素据MetaData，区别于正真存储的数据，在JDBC中大致可以获得三种元数据

- 数据库相关的元数据 DataBaseMetaData
- 结果集相关的元数据 ResultSetMetaData
- 预备语句prepareStatement中设置的参数元数据

如下

	//数据库相关元数据
	conn = getConnection();
	DatabaseMetaData databaseMetaData = conn.getMetaData();
	ResultSet mrs = databaseMetaData.getTables(null, null, null, new String[]{"TABLE"});
	while(mrs.next()){
		//获得连接数据库所有表名
		System.out.println(mrs.getString(3));
	}

	
	//结果集元数据
	conn = getConnection();
	Statement stat = conn.createStatement();
	ResultSet rs = stat.executeQuery(" select * from news limit 10");
	ResultSetMetaData meta = rs.getMetaData();
	//注意：结果集的元数据下标是从1开始
	for(int i=1;i<=meta.getColumnCount();i++){
		System.out.println(meta.getColumnLabel(i));
		System.out.println(meta.getColumnDisplaySize(i));
	}


###在JDBC中使用事务

在JDBC中使用事务如下

	conn = getConnection();
	//关闭自动提交 
	conn.setAutoCommit(false);
	Statement stat = conn.createStatement();
	ResultSet rs = stat.executeQuery("select id, title from news limit 3");
	while(rs.next()){
		System.out.println(rs.getString(1) + "-->" + rs.getString(2));
	}
	int affectedRows = stat.executeUpdate("update news set title='summer' where id=1");
	affectedRows = stat.executeUpdate("update news set title='snow0x01' where id=2");
	affectedRows = stat.executeUpdate("update news set title='summer' where id=3");

	//回滚事务
	conn.rollback();

	//提交事务
	conn.commit();

除此之外，还有保存点，回滚到制定的保存点使用创建保存点如下

	Savepoint save1 = conn.setSavepoint();

如果要回滚到指定的保存点

	conn.rollback(save1);

JDBC还提供了批量执行SQL语句和DDL，提高程序性能，批量查询被视为单次事务，如果一条查询异常，就会回滚到查询之前。使用如下
	conn = getConnection();
	Statement stat = conn.createStatement();
	//创建批量查询
	stat.addBatch("update news set title='coco' where id=1");
	stat.addBatch("update news set title='coco' where id=2");
	stat.addBatch("update news set title='coco' where id=3");
	
	//执行批量查询
	int count[] = stat.executeBatch();
	
	ResultSet rs = stat.executeQuery("select id, title from news limit 3");
	while(rs.next()){
		System.out.println(rs.getString(1) + "-->" + rs.getString(2));
	}

