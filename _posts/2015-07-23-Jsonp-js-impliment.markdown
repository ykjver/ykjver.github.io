---
layout: post
title:  "Jsonp的js实现"
date:   2015-07-23 23:10:45
categories: javascript
author : snow0x01
---

`jsonp` 叫做`json with padding`，用来解决现有浏览器ajax请求不能跨域的一种技术

但是`<script src="xxx.js"></script>`是可以跨域的，利用这一特性，可以完成跨域请求动态数据, 如果在jQuery中，只需要利用`$.ajax`方法就能比较容易做jsonp，下面主要介绍js原生实现。

###创建js全局作用回调方法

首先创建一个全局作用域的回调方法供动态加入`<script>`标签加入时调用此方法,如下
{% highlight javascript %}
window['callbackName'] = function(data){
    console.log(data);
    window['callbackName'] = null //执行完了删除这个方法的引用，下次调用好生新的回调方法
}
{% endhighlight %}

###动态加入script标签到head中

当全局有一个`window.callbackName`这样的函数时，此时加入把一个带服务端的`jsonp`地址的`script`标签动态的加入到`head`中

{% highlight javascript %}
var scriptDom = document.createElement('script'),
headDom = document.getElementsByTagName('head')[0];
scriptDom.src = "http://ex.server.com?callback=callbackName";
headDom.appendChild(headDom);
{% endhighlight %}

###服务端的jsonp输出

请求`http://ex.server.com?callback=callbackName`就是关键了，返回回来的数据需要执行刚才定义的`window.callbackName`,服务端需要如下格式的数据
{% highlight javascript %}
callbackName({name : "yangke", age : 21})
{% endhighlight %}
这里服务端(php)这样写的
{% highlight php %}
<?php
echo $_GET['callback'].'({name:"yangke",age:21})';
{% endhighlight %}
这样，只要动态添加src为`http://ex.server.com?callback=callbackName`的`script`标签到head中，就能动态的执行定义的全局方法（名称与请求参数callback的值一样），这样既能获取到不在同一域名下的服务端动态数据

###Demo

下面是整个js demo
{% highlight javascript %}
    var Jsonp = function(options){
        this.url = !!options.url ? options.url : "";
        this.queryCbName = !!options.queryCbName ?  options.queryCbName : "callback";
        this.success = !!options.success ? options.success : function(){};
        this.error = !!options.error ? options.error : function(){};
        this.cbName = !!options.cbName ? options.cbName : "cbName";
        this.queryParams = !!options.queryParams ? options.queryParams : "";
        this.getJsonp();
    }

    Jsonp.prototype.hash = Math.random();
    Jsonp.prototype.getJsonp = function(){
        var self = this,
        d = document,
        scriptDom = d.createElement('script'),
        oFragment = d.createDocumentFragment();

        scriptDom.src = self.url + "?" + self.queryParams + "&" + self.queryCbName + "=" + self.cbName;
        window[self.cbName] = function(result){
            try{
                self.success(result);
            }catch(error){
                options.error();
            }finally{
                oFragment.appendChild(scriptDom);
                window[self.cbName] = null;
            }
        }
        d.getElementsByTagName('head')[0].appendChild(scriptDom);
    }
{% endhighlight %}

使用
{% highlight javascript %}

var jsonp = new Jsonp({
    url : 'http://localhost/dom/json.php',
    queryParams : 'name=y&id=3',
    queryCbName : 'callback',
    success : function(result){
        console.log(result);
    },
    error :function(result){
        alert('error');
    }
});
{% endhighlight %}



