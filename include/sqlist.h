#ifndef LINEAR_LIST_H
#define LINEAR_LIST_H

#include "types.h"

#define SQLIST_ENABLE_EXAMPLE

/*
线性表抽象数据类型定义如下

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
    ListLength(L):返回线性表L中数据元素的个数。
*/

/*
顺序表优点
1. 无需为表示表中元素之间的逻辑关系而增加额外的存储空间
2. 可以快速地存取表中的任一元素
缺点：
1. 插入和删除操作需要移动大量元素
2. 当线性表长度变化较大时，难以确定存储空间的容量
3. 造成存储空间的碎片
*/

// example

#define LINEAR_LIST_MAXSIZE 20

typedef struct {
    ElemType data[LINEAR_LIST_MAXSIZE];
    int length;
} SqList;

// 初始化操作，建立一个空的线性表L。
extern void SQLIST_InitList(SqList *list);

// 判断线性表L是否为空，若为空返回true，否则返回false。
extern bool SQLIST_ListEmpty(const SqList *list);

// 将线性表L重置为空表。
extern void SQLIST_ClearList(SqList *list);

// 将线性表L中的第i个位置元素返回给e
/*
初始条件：顺序表已存在，1 <= pos <= ListLength(list)
操作结果：用e返回L中第pos个数据元素的值，注意pos是指位置，第1个位置的数组是从0开始
*/
extern Status SQLIST_GetElem(const SqList *list, const int pos, ElemType *out_elem);

// 在线性表L中查找与定值e相等的元素，返回该元素在线性表中序号表示成功，否则，返回0表示失败
extern int SQLIST_LocateElem(const SqList *list, const ElemType e);

// 在线性表L的第i个位置插入新的数据元素e
/*
初始条件：顺序表L已存在，1 <= pos <= ListLength(L)
操作结果：在list的第pos个位置之前插入新的数据元素e，list的长度加1
思路：
1. 如果插入位置不合理，抛出异常
2. 如果线性表长度大于等于数组长度，则抛出异常或动态增加容量
3. 从最后一个元素开始向前遍历到第i个位置，分别将它们都向后移动一个位置
4. 将要插入元素填入位置处
5. 表长加1
复杂度：O(n)
*/
extern Status SQLIST_ListInsert(SqList *list, const int pos, const ElemType e);

// 删除线性表L的第i个位置的数据元素，并用e返回其值。
/*
初始条件：顺序表L已存在，1 <= pos <= ListLength(list)
操作结果：删除L的第pos个位置的数据元素，并在e!=NULL时用e返回其值,L的长度减1
思路：
1. 如果删除位置不合理，抛出异常
2. 取出删除元素
3. 从删除元素位置开始遍历到最后一个元素，分别将它们都向前移动一个位置
4. 表长减1
复杂度：O(n)
*/
extern Status SQLIST_ListDelete(SqList *list, const int pos, ElemType *out_elem);

// 返回线性表L中数据元素的个数。
extern int SQLIST_ListLength(const SqList *list); 

// 将所有的在线性表b中但不在线性表a中的元素插入到线性表a中
extern void SQLIST_unionL(SqList *a, const SqList *b);

// 打印线性表元素
extern void SQLIST_PrintList(const SqList *list);

extern void SQLIST_example();

#endif