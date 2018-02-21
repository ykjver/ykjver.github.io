---
layout: post
title:  "平衡树"
date:   2015-10-24 23:10:45
categories: Data Structures And Algorithm
author : 自来也
---

如果一个二叉查找树不断的执行insert和delete操作，如果delete操作总是让左儿子来代替删除的节点，那么右子树上的节点就会越来越多，如果用右儿子来代替删除的节点，则会出现相反的情况。当一颗二叉查找树出现非常不平衡的情况时（当向一棵树输入排序好的数据时），它将只会出现左子树或者右子树，这时，所有的操作将会是最坏的情形，此时就相当于一个链表。

- 一种解决办法就是添加一个平衡条件，让任何节点都不至于过深，如果某个节点不符合这个条件，就需要对改节点进行调节。Avl 树
- 还有种办法就是不对树的深度进行限制，每次操作后都根据相应的规则对树进行相应的调整，使得后面的操作效率更高，虽然在单个的操作不保证在logn时间界完成，但是对于连续m次操作下的最坏情形保证在mlogn，这叫伸展树（splay tree）

### 定义

Avl Tree 是一个带有平衡条件是二叉查找树，这个平衡条件是--树上的每个节点的左子树和右子树的高度最多差1(空树的高度定义为-1)。

### Avl树的insert操作（一般，简单的实现）

Avl Tree 除insert操作，其他操作都将是logn的操作时间界，insert操作可能会破坏节点的平衡条件，平衡条件被破坏的路径只能是插入点到根节点的这段路径，所以只要沿着插入节点到根节点去修复平痕条件就可以再次得到瞒住Avl条件的树，在下面这四种情况下做了insert操作，需要对其进项调整。

1. 对节点左儿子的左儿子进行插入
2. 对节点左儿子的右儿子进行插入
3. 对节点右儿子的右儿子进行插入
4. 对节点右儿子的左儿子进行插入

按第一种情况解释：如果该节点没有右儿子，有一个左儿子，那么再对其进项左儿子插入的话就会导致左儿子的高度为1，右字数高度为-1，大于1了，就不满住条件了，就要进行调整了，这里调整也有4中形式对应上面的4中情况，其中1、3和2、4分别是对称的。

####旋转

单旋转对应的是左左插入和右右插入，旋转其实就是对链表结构的调整，以右右插入为例，右右插入其实就是右子树过高，将该节点的右儿子放在该节点的位子，然后该节点充当左儿子，如果其右儿子在调整前已经有左儿子，那么这个左儿子要放在该节点的右儿子上。这样右子树高度减一，左子树加一，就符合Avl条件了。代码如下

	Position
	SingleRotateWithRight(Position P){
		//调整后新节点指针
		Position newRoot;
		
		//把旧节点的右子树搞起来当新节点
		newRoot = P->right;
		//新节点的左子树放在旧节点右子树
		P->right = newRoot->left;
		//旧节点成为新节点的左子树
		newRoot->left = P;
		
		//更新高度
		P->height = Max(Height(P->left), Height(P->right)) + 1;
		newRoot->height = Max(Height(newRoot->right), P->height) + 1;
		
		//返回新节点指针
		return newRoot;
	}

双旋转就是两次旋转，单旋转操作，如果是a节点的左右插入的话，如果只进行一次左左旋转的话，那么a节点左儿子的右儿子附带插入在右儿子上的节点将全部被放到a节点的左儿子上，这样，左子树高度减一，右子树高度则加二了还是不满足条件。正确的调整操作应该是这样的，先对a的节点的左儿子进行一次右右单旋转操作，将这个不平衡调整到a节点左左子树上，然后再执行一次左左单旋转将左子树的不平衡调整回来，使得该树满足Avl条件，这叫做左右双旋转。

	Position
	DoubleRotateWithLeft(Position P){
		
		P->left = SingleRotateWithRight(P->left);
		return SingleRotateWithLeft(P);
	}


值得注意：节点入了left、right指针和数据域，还需要一个height变量来记录节点高度，这样在insert操作后才能进行判断是否符合Avl条件

链表实现的插入操作的所有代码如下

	#include <stdio.h>
	#include <stdlib.h>
	typedef int ElementType;
	struct AvlNode;
	typedef struct AvlNode *AvlTree;
	typedef struct AvlNode *Position;

	static int Height(Position P);
	static Position insert(ElementType Element, AvlTree T);
	static Position SingleRotateWithLeft(Position P);
	static Position DoubleRotateWithLeft(Position P);
	static Position SingleRotateWithRight(Position P);
	static Position DoubleRotateWithRight(Position P);
	static int Max(int i, int j);
	void reverse(Position P);

	struct AvlNode {
		ElementType Element;
		AvlTree left;
		AvlTree right;
		int height;
	};


	int main(){
		int n, m,i;
		scanf("%d", &n);
		AvlTree T = NULL;
		AvlTree *head = &T;
		for(i=0;i<n;i++){
			scanf("%d", &m);
			T = insert(m, T);
		}
		
		printf("%d", (*head)->Element);
		return 0;
	}


	static int
	Height(Position P){
		if (P == NULL){
			return -1;
		}else{
			return P->height;
		}
	}


	static int
	Max(int i, int j){
		return i > j ? i : j;
	}

	AvlTree
	insert(ElementType Element, AvlTree T){
		//空节点创造root
		if(T == NULL){
			T = (AvlTree)malloc(sizeof(struct AvlNode));
			T->left = NULL;
			T->right = NULL;
			T->Element = Element;
		} else if (Element > T->Element) {
			T->right = insert(Element, T->right);
			if(Height(T->right) - Height(T->left) == 2){
				if(Element > T->right->Element){
					T = SingleRotateWithRight(T);
				}else{
					T = DoubleRotateWithRight(T);
				}
			}
		} else if(Element < T->Element){
			T->left = insert(Element, T->left);
			if(Height(T->left) - Height(T->right) == 2){
				if(Element < T->left->Element ){
					T = SingleRotateWithLeft(T);
				}else{
					T = DoubleRotateWithLeft(T);
				}
			}
		}

		T->height = Max(Height(T->left), Height(T->right)) + 1;
		return T;
	}

	static Position
	SingleRotateWithLeft(Position P){
		Position newRoot;
		
		newRoot = P->left;
		P->left = newRoot->right;
		newRoot->right = P;
		
		//update height
		P->height = Max(Height(P->left), Height(P->right)) + 1;
		newRoot->height = Max(Height(newRoot->left), P->height) + 1;
		
		return newRoot;
	}

	static Position
	DoubleRotateWithLeft(Position P){
		P->left = SingleRotateWithRight(P->left);
		return SingleRotateWithLeft(P);
	}

	static Position
	SingleRotateWithRight(Position P){
		Position newRoot;

		newRoot = P->right;
		P->right = newRoot->left;
		newRoot->left = P;
		
		P->height = Max(Height(P->left), Height(P->right)) + 1;
		newRoot->height = Max(Height(newRoot->right), P->height) + 1;
		return newRoot;
	}

	static Position
	DoubleRotateWithRight(Position P){
		P->right = SingleRotateWithLeft(P->right);
		return SingleRotateWithRight(P);
	}

