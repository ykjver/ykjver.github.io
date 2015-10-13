---
layout: post
title:  "spring mvc TIPS"
date:   2015-10-13 23:10:45
categories: article
author : 自来也
---

java开发遇到的问题

### Spring Mvc 表单提交400 The request sent by the client was syntactically incorrect.

这个问题是由于表单提交的字段类型和与其绑定的实体(Entity)的setter不符合导致的，也是spring mvc在绑定request参数时的错误。这时需要用注解`@RequestParam`，`@DateTimeFormat`来对其进行相应的转换，如果是接受的Entity实体类，则需要在其类中的setter方法上添加注解，例如：


    /**
    *实体类
    */
    @Entity
    public class Summer {

        private Date foo;

        //<input type="text" name="foo">可接正常转换为Date
        @DateTimeFormat(iso=ISO.DATE_TIME)
        @Temporal(TemporalType.DATE)
        public Date getFoo() {
            return foo;
        }

        public void setFoo(Date foo) {
            this.foo = foo;
        }

        //没有带注解会产生400 错误
        public Date getBar() {
            return bar;
        }

        public void setBar(Date bar) {
            this.bar = bar;
        }

        private Date bar;

    }


    /**
     * 控制器
     * @author snow0x01
     * @version 2015-10-13
     */

    @Controller
    public class SummerController {

        public String summer(Summer summer) {
            return "summer";
        }

    }


总之，这类问题是由于http参数类型和spring mvc controller所绑定的参数类型不一致造成。