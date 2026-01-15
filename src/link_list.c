#include "link_list.h"
#include "types.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef LINKLIST_Node Node;

void LINKLIST_InitList(LinkList *list) {
    assert(list != NULL);
    list->data = NULL;
    list->length = 0;
}

bool LINKLIST_ListEmpty(const LinkList *list) {
    assert(list != NULL);
    return (LINKLIST_ListLength(list) == 0 ? true : false);
}

Status LINKLIST_ClearList(LinkList *list) {
#ifndef NDEBUG
    int delcnt = 0;
#endif
    Node *p = list->data;
    while (p != NULL) {
        Node *q = p->next;
        free(p);
        p = q;
#ifndef NDEBUG
        ++delcnt;
#endif
    }
#ifndef NDEBUG
    assert(delcnt == list->length);
#endif
    list->data = NULL;
    list->length = 0;
    return OK;
}

Status LINKLIST_GetElem(const LinkList *list, int pos, ElemType *out_elem) {
    assert(list != NULL && out_elem != NULL);
    if (pos < 1 || pos > LINKLIST_ListLength(list)) {
        return OVERFLOW;
    }
    const Node *p = list->data;
    for (int i = 0; i < pos; ++i) {
        assert(p != NULL);
        p = p->next;
    }
    *out_elem = p->data;
    return OK;
}

int LINKLIST_LocateElem(const LinkList *list, const ElemType e) {
    assert(list != NULL);
    const Node *node = list->data;
    const int len = LINKLIST_ListLength(list);
    for (int i = 0; i < len; ++i) {
        assert(node != NULL);
        if (node->data != e) {
            continue;
        }
        return i + 1;
    }
    return 0;
}

Status LINKLIST_ListInsert(LinkList *list, int pos, const ElemType e) {
    assert(list != NULL);
    const int len = LINKLIST_ListLength(list);
    if (pos < 1 || pos > len + 1) {
        return OVERFLOW;
    }
    Node *s = (Node*)malloc(sizeof(Node));
    if (NULL == s) {
        return SYSERR;
    }
    s->data = e;
    // 由于没有头结点，所以这里需要特殊处理
    if (1 == pos) {
        s->next = list->data;
        list->data = s;
    } else {
        Node *p = list->data;
        for (int i = 1; i < pos - 1; ++i) {
            assert(p != NULL);
            p = p->next;
        }
        assert(p != NULL);
        s->next = p->next;
        p->next = s;
    }
    ++(list->length);
    return OK;
}

Status LINKLIST_ListDelete(LinkList *list, int pos, ElemType *e) {
    assert(list != NULL);
    if (pos < 1 || pos > LINKLIST_ListLength(list)) {
        return OVERFLOW;
    }
    // 由于没有头结点，所以这里需要特殊处理
    Node *q = NULL;
    if (1 == pos) {
        q = list->data;
        assert(q != NULL);
        list->data = q->next;
    } else {
        Node *p = list->data;
        for (int i = 1; i < pos - 1; ++i) {
            p = p->next;
        }
        q = p->next;
        p->next = q->next;
    }
    assert(q != NULL);
    if (e != NULL) {
        *e = q->data;
    }
    free(q);
    --(list->length);
    return OK;
}

int LINKLIST_ListLength(const LinkList *list) {
    return list->length;
}

void LINKLIST_PrintList(const LinkList *list) {
    assert(list != NULL);
    const int len = LINKLIST_ListLength(list);
    printf("List length: [%d]\n", len);
    printf("List elements: ");
    const Node *p = list->data;
    for (int i = 0; i < len; ++i) {
        assert(p != NULL);
        printf("%d ", p->data);
        p = p->next;
    }
    assert(NULL == p);
    printf("\n");
}

void LINKLIST_example() {
#ifdef LINKLIST_ENABLE_EXAMPLE
    printf("========================\n");
    printf("in %s::%d::\n", __func__, __LINE__);

    LinkList a;
    LINKLIST_InitList(&a);

    printf("before insert 5 elements:\n");
    LINKLIST_PrintList(&a);

    for (int i = 1; i <= 5; ++i) {
        Status ret = 
            LINKLIST_ListInsert(&a, i, i * 10);
        assert(OK == ret);
    }
    printf("List a after insert 5 elements:\n");
    LINKLIST_PrintList(&a);
    ElemType tmp_elem;
    Status ret = 
        LINKLIST_ListDelete(&a, 3, &tmp_elem);
    assert(OK == ret);
    printf("List a after delete element at pos 3 (elem=%d):\n", tmp_elem);
    LINKLIST_PrintList(&a);
    ret = LINKLIST_ListInsert(&a, 1, 21);
    printf("List a after insert 21 at pos 1 :\n");
    LINKLIST_PrintList(&a);
    LINKLIST_ClearList(&a);
#endif
}