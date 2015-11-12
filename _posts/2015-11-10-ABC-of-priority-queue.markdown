---
layout: post
title:  "Learn Data Structures And Algorithm -- ABC Of Priority Queue"
date:   2015-11-10 23:10:45
categories:  Data Structures And Algorithm
author : 自来也
---

##简介

Priority Queue优先队列，队列就队列，还有什么优先级别。当然有啦，比如在银行办业务排队时，每个人就领一个号乖乖的坐到等候区等广播叫号，这时突然来了个一身黑的美女，拿出黑卡往取票机一刷，接下来第一空的柜台就是给她留着的，强行插你的队。同理，对于cpu也是一样的，cpu资源只有那么多，不可能每个线程都把其资源占着，有一个设计思路就是，优先级高的程序可能获得更多的资源，这就是优先队列，代表着一种设计生活中很普通的思路，重要紧急的事情优先做，不重要不紧急的时候退后再做。

##模型和一种实现二叉堆

对于Priority Queue来说，至少就要支持两种操作，Insert(入队)和DeleteMin(出队)，其中一种实现方式叫做二叉堆，使用二叉查找树来实现优先队列，二叉堆又叫做堆。

###结构性质

二叉堆要求必须满足是完全二叉树，因为完全二叉树很有规律，所以二叉堆用数组来存储，不需要指针。在这个数组中，任意位置i上的元素的左儿子在数组的2i位置上，右儿子在2i+1上

###堆序性

在堆中，任意一个元素都应该小于他的后裔

###实现


	#include <stdio.h>
	#include <stdlib.h>
	#define MAXSIZE 10000
	#define Min (-32767)

	struct Heap;
	typedef int ElementType;
	typedef struct Heap *PriorityQueue;

	struct Heap {
	    int capacity;
	    int size;
	    ElementType *data;
	};

	PriorityQueue init(int Max);
	PriorityQueue insert(PriorityQueue Q, ElementType e);
	void printPriorityQueue(PriorityQueue Q, int i);

	int main() {
	    int N, M, i;
	    ElementType e;
	    scanf("%d %d", &N, &M);
	    PriorityQueue Q = init(N);
	    int output[M];
	    for(i=0;i<N;i++){
	        scanf("%d", &e);
	        insert(Q, e);
	    }
	    
	    for(i=0;i<M;i++){
	        scanf("%d", output+i);   
	    }
	    for(i=0;i<M;i++){
	        printPriorityQueue(Q, output[i]);
	    }
	    
	    /*for(i=0;i<=N;i++){
	        printf("%d ", Q->data[i]);    
	    }*/
	    return 0;
	}

	PriorityQueue init(int Max) {
	    PriorityQueue Q;
	    Q = (PriorityQueue)malloc(sizeof(struct Heap));
	    
	    Q->data = (ElementType*)malloc(sizeof(ElementType) * (Max + 1));
	    
	    Q->size = 0;
	    Q->capacity = Max;
	    (Q->data)[0] = Min;
	    return Q;
	}

	PriorityQueue insert(PriorityQueue Q, ElementType e) {
	    if(Q->size >= Q->capacity) {
	        return Q;   
	    }
	    
	    int i = Q->size + 1;
	    for(;e < Q->data[(int)(i / 2)]; i = (int)(i / 2)) {
	        Q->data[i] = Q->data[(i / 2)];
	    }
	    Q->size++;
	    Q->data[i] = e;
	    return Q;
	}

	void printPriorityQueue(PriorityQueue Q, int i) {
	    
	    while(i > 1) {
	        printf("%d ", Q->data[i]);
	        i = (int)(i / 2);   
	    }
	    
	    printf("%d\n", Q->data[1]);
	}
