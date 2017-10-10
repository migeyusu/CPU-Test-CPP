#include "stdafx.h"
#include "I_DataStructrue.h"

//单链表-----------------------------------------------
void Oneway_List::nodeAppend(nodes *&nds, int x)
{
	if (nds ==NULL)
	{
		nodes *nd1 = new nodes;
		nd1->data = x;
		nd1->next = NULL;
		nds = nd1;
		return;
	}
	else
	{
		nodeAppend(nds->next, x);
	}
}

void Oneway_List::createList(nodes *&nds, int ary[], int size)
   {
	nds = NULL;
	for (int i = 0; i < size; i++)
		nodeAppend(nds, ary[i]);
   }

void Oneway_List::listPrint(nodes *nds, int ary[], int size)
{
	int i = 0;
	while (i <= size && nds != NULL)
	{
		ary[i] = nds->data;
		nds = nds->next;
		++i;
	}
}

int Oneway_List::listCount(nodes *nds)
{
	if (nds == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + listCount(nds->next);
	}
}

bool Oneway_List::nodeSearch(nodes *nds, int finder)
{
	if (nds == NULL)
	{
		return false;
	}
	else if (nds->data == finder)
		return true;
	else
	{
		return nodeSearch(nds->next, finder);
	}
}

bool Oneway_List::nodeInsert(nodes *&nds, int prenode, int nextnode)
{
	if (nds == NULL)
	{
		return false;
	}
	else if (nds->data == prenode)
	{
		if (nds->next == NULL)
		{
			 nodeAppend(nds->next, nextnode);
			 return true;
		}
		else
		{
			nodes *p;
			p = nds->next;
			nodes *q = new nodes;
			q->data = nextnode;
			q->next = p;
			nds->next = q;
			return true;
		}
	}
	else
	{
		return nodeInsert(nds->next, prenode, nextnode);
	}
}

bool Oneway_List::nodeDelete(nodes *&nds, int delenode)
{
	//头结点判断
	if (nds == NULL)
	{
		return false;
	}
	else if (nds->data == delenode)
	{
		if (nds->next == NULL)
		{
			delete nds;
			nds = NULL;
		}
		else
		{
			nodes *p = nds->next;
			delete nds;
			nds = NULL;
			nds = p;
		}
		return true;
	}//先判断头结点存在，然后判断头结点是否符合，然后判断下一个节点是否为空，然后判断下一个节点是否有值符合
	else
	{
		return nodeNextDele(nds, delenode);
	}
}

void Oneway_List::nodeClean(nodes *&nds)
{
	if (nds != NULL)
	{
		nodeClean(nds->next);
		delete nds;
		nds = NULL;
	}
}

bool Oneway_List::nodeNextDele(nodes *&nds, int delenode)
{
	if (nds->next == NULL)
	{
		return false;
	}
	else if (nds->next->data == delenode)
	{
		if (nds->next->next == NULL)//删除节点位于最后
		{
			delete nds->next;
			nds->next = NULL;
		}
		else
		{
			nodes *p;
			p = nds->next->next;
			delete nds->next;
			nds->next = NULL;
			nds->next = p;
		}
		return true;
	}
	else
	{
		return nodeNextDele(nds->next, delenode);
	}
}

//b树-------------------------------------------------------
void B_tree::btreebuild(roots *&bst, tnode a[], int n)
{
	bst = NULL;
	for (int i = 0; i<n; i++)
		InsertIn(bst, a[i]);
}

void B_tree::InsertIn(roots *&bst, tnode x)
{
	if (bst == NULL)
	{
		roots *p = new roots;
		p->data = x;
		p->lchild = p->rchild = NULL;
		bst = p;
	}
	else if (x<bst->data)
		InsertIn(bst->lchild, x);
	else
		InsertIn(bst->rchild, x);
}
//顺序输出
void B_tree::Inorder(roots *bst)
{
	Current_SN = 0;
	outInorder(bst);
}
//b树查找
bool B_tree::FindData(roots *bst, tnode &x)
{
	if (bst == NULL)
		return false;
	else  if (x == bst->data)
	{
		x = bst->data;
		return true;
	}
	else if (x<bst->data)
		return FindData(bst->lchild, x);
	else
		return FindData(bst->rchild, x);
}
//指定节点删除
bool B_tree::DeleteOn(roots *&bst, tnode x)
{
	roots *t = bst, *s = NULL;
	while (t != NULL)
	{
		if (x == t->data)  break;
		else if (x<t->data)
		{
			s = t; t = t->lchild;
		}
		else
		{
			s = t; t = t->lchild;
		}
	}
	if (t == NULL)  return 0;
	if (t->lchild == NULL&&t->rchild == NULL)
	{
		if (t == bst)
			bst = NULL;
		else if (t == s->lchild)
			s->lchild = NULL;
		else
			s->rchild = NULL;
		delete t;
	}
	else if (t->lchild == NULL || t->rchild == NULL)
	{
		if (bst == t)
		{
			if (t->lchild == NULL)
				bst = t->rchild;
			else
				bst = t->lchild;
		}
		else {
			if (t == s->lchild&&t->lchild != NULL)
				s->lchild = t->lchild;
			else if (t == s->lchild&&t->rchild != NULL)
				s->lchild = t->rchild;
			else if (t == s->rchild&&t->lchild != NULL)
				s->rchild = t->lchild;
			else if (t == s->rchild&&t->rchild != NULL)
				s->rchild = t->rchild;
		}
		delete t;
	}
	else if (t->lchild != NULL&&t->rchild != NULL)
	{
		roots *p = t, *q = t->lchild;
		while (q->rchild != NULL)
		{
			p = q;
			q = q->rchild;
		}
		t->data = q->data;
		if (p == t) t->lchild = q->lchild;
		else p->rchild = q->lchild;
		delete q;
	}
	return true;
}
//节点数量输出
int B_tree::NodeCount(roots *bst)
{
	if (bst == NULL)
		return 0;
	else
		return NodeCount(bst->lchild) + NodeCount(bst->rchild) + 1;

}
//清空b树
void B_tree::clearbstree(roots *&bst)
{
	if (bst != NULL)
	{
		clearbstree(bst->lchild);
		clearbstree(bst->rchild);
		delete bst;
		bst = NULL;
	}
}
//顺序输出
void B_tree::outInorder(roots *bst)
{
	if (bst != NULL)
	{
		outInorder(bst->lchild);
		*(Result_Ary + Current_SN) = bst->data;
		Current_SN++;
		outInorder(bst->rchild);
	}
}

//int单链表作队列，前进后出----------------------------------------------------------
bool I_Queue::createQueue()
{
	queueAry = NULL;
	queueLength = 0;
	return true;
}

bool I_Queue::push(int x)//增加头结点
{
	nodes *p = new nodes;
	p->data = x;
	if (queueLength==0)
		p->next = NULL;
	else
		p->next = queueAry;
	queueAry = p;
	++queueLength;
	return true;
}

bool I_Queue::pop(int &x)
{
	if (queueLength == 0)
	{
		return false;
	}
	else if (queueAry->next == NULL)
	{
		x = queueAry->data;
		delete queueAry;
		queueAry = NULL;
		queueLength = 0;
		return true;
	}
	else
	{
		nodes *p = new nodes;
		p = queueAry;
		while (p->next->next != NULL)
		{
			p = p->next;
		}
		x = p->next->data;
		delete p->next;
		p->next = NULL;
		--queueLength;
		return true;
	}
}

bool I_Queue::peek(int &x)
{
	if (queueLength == 0)
	{
		return false;
	}
	nodes *p = new nodes;
	p = queueAry;
	while (p->next != NULL)
	{
		p = p->next;
	}
	x = p->data;
	return true;
}

void I_Queue::queueClear()
{
	clears(queueAry);
	queueLength = 0;
}

void I_Queue::clears(nodes *&nds)
{
	if (nds!=NULL)
	{
		clears(nds->next);
		delete nds;
		nds = NULL;
	}
}
