---
layout: post
title:  "Learn Data Structures And Algorithm -- ABC Of Priority Queue"
date:   2015-11-10 23:10:45
categories:  Data Structures And Algorithm
author : 自来也
---


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
