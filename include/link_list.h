#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "types.h"

#define LINKLIST_ENABLE_EXAMPLE

/*
ADT 线性表（List）
Data
    线性表的数据对象集合为{a1, a2, ..., an}，每个元素的类型均为DataType。其中，除了第一个数据对象a1外，其余每个数据对象都有且仅有一个直接前驱，除了最后一个数据对象an外，其余每个数据对象都有且仅有一个直接后继。数据元素之间的关系是一对一的关系。
Operation
    InitList(*L):初始化操作，建立一个空的线性表L。
    ListEmpty(L):判断线性表L是否为空，若为空返回true，否则返回false。
    ClearList(*L):将线性表L重置为空表。
    GetElem(L, i, *e):将线性表L中的第i个位置元素返回给e.
    LocateElem(L, e):在线性表L中查找与定值e相等的元素，返回该元素在线性表中序号表示成功，否则，返回0表示失败
    ListInsert(*L, i, e):在线性表L的第i个位置插入新的数据元素e.
    ListDelete(*L, i, *e):删除线性表L的第i个位置的数据元素，并用e返回其值。
    ListLength(L):返回线性表L中数据元素的个数.
*/

/*
对于插入或删除数据越频繁的操作，单链表的效率就越高
如果希望从第i个位置，插入10个结点，
对于顺序表存储结构意味着，每一次插入都需要移动n-i个元素，每次都是O(n)
而单链表，只需要在第一次时，找到第i个位置的指针，此时为O(n)，接下来就是简单地通过赋值移动指针而已，时间复杂度为O(1)

对比: 
存储分配方式：
顺序存储结构用一段连续的存储单元依次存放线性表的数据元素，
单链表采用链式存储结构，用一组任意的存储单元存放线性表的元素
时间性能：
查找：
顺序存储结构O(1)
单链表O(n)
插入和删除：
顺序存储结构需要平均移动表长一半的元素，时间复杂度为O(n)
单链表在找出位置的指针后，插入和删除的时间复杂度仅为O(1)
空间性能：
顺序存储结构需要预分配存储空间，分大了，浪费;分小了易发生上溢
单链表不需要分配存储空间，只要有就可以分配，元素个数也不受限制
*/

typedef struct LINKLIST_Node {
    ElemType data;
    struct LINKLIST_Node *next;
} LINKLIST_Node;

typedef struct {
    int length;
    struct LINKLIST_Node *data;
} LinkList;

// 初始化链表list
extern void LINKLIST_InitList(LinkList *list);

extern bool LINKLIST_ListEmpty(const LinkList *list);

// 单链表的整表删除
/*
初始条件：链式线性表list已存在
操作结果：将list置为空表
思路：
1. 声明一指针p和q
2. 将第一个结点赋值给p
3. 循环：
    1. 将p的下一个结点赋值给q
    2. 释放结点p
    3. 将q赋值给p，继续循环
*/
extern Status LINKLIST_ClearList(LinkList *list);

// 获取链表第i个数据
// 时间复杂度 O(n)
/*
初始条件：链式线性表L已存在，1 <= pos <= ListLength(list)
操作结果：用out_elem返回L中第pos个数据元素的值
思路：
1. 声明一个指针p指向链表的第一个结点，初始化i从1开始
2. 当i<pos时，就遍历链表，让p的指针向后移动，不断指向下一结点，i累加1
3. 若到链表末尾p为空，则说明第i个元素不存在
4. 否则查找成功，返回结点p的数据
*/
extern Status LINKLIST_GetElem(const LinkList *list, int pos, ElemType *out_elem);

// 在表list中查找与定值e相等的元素，返回该元素在线性表中序号表示成功，否则，返回0表示失败
extern int LINKLIST_LocateElem(const LinkList *list, const ElemType e);

// 单链表第pos个数据插入结点
/*
初始条件：链式线性表L已存在，1 <= pos <= ListLength(list) + 1
操作结果：在list中第pos个位置之前插入新的数据元素e，L的长度加1
思路：
1. 声明一指针p指向链表的第一个结点，初始化i从1开始
2. 当i<pos时，就遍历链表，让p的指针向后移动，不断指向下一结点，i累加1
3. 若到链表末尾p为空，则说明第pos个结点不存在
4. 否则查找成功，在系统中生成一个空结点s.
5. 将数据元素e赋值给s->data
6. 单链表的插入标准语句s->next = p->next; p->next = s;
7. 返回OK
复杂度：O(n)
*/
extern Status LINKLIST_ListInsert(LinkList *list, int pos, const ElemType e);

// 单链表第pos个数据删除结点
/*
初始条件：链式线性表list已存在，1 <= pos <= ListLength(list)
操作结果：删除L中第pos个位置的数据元素，并用e返回其值，list的长度减1
思路：
1. 声明一指针p指向链表的头结点，初始化i从1开始
2. 当i<pos时，就遍历链表，让p的指针向后移动，不断指向下一结点，i累加1
3. 若到链表末尾p为空，则说明第pos个结点不存在
4. 否则查找成功，将欲删除结点p->next赋值给q
5. 单链表分删除标准语句p->next = q->next
6. 将结点q中的数据赋值给e,作为返回
7. 释放结点q的空间
8. 返回OK
复杂度：O(n)
*/
extern Status LINKLIST_ListDelete(LinkList *list, int pos, ElemType *e);

// 返回单链表中数据元素的个数。
extern int LINKLIST_ListLength(const LinkList *list);

// 打印线性表元素
extern void LINKLIST_PrintList(const LinkList *list);

extern void LINKLIST_example();


#endif