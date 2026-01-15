#include <stddef.h>
#include <assert.h>
#include <stdio.h>

#include "sqlist.h"
#include "types.h"

void SQLIST_unionL(SqList *a, const SqList *b) {
    assert(a != NULL && b != NULL);
    const int blen = SQLIST_ListLength(b);
    for (int i = 0; i < blen; ++i) {
        const ElemType e = b->data[i];
        if (SQLIST_LocateElem(a, e) != 0) {
            continue;
        }
        const int insert_pos = SQLIST_ListLength(a) + 1;
        const Status ret = SQLIST_ListInsert(a, insert_pos, e);
        if (ret != OK) {
            return;
        }
    }
}

void SQLIST_InitList(SqList *list) {
    assert(list != NULL);
    list->length = 0;
}

bool SQLIST_ListEmpty(const SqList *list) {
    assert(list != NULL);
    return (SQLIST_ListLength(list) == 0 ? true : false);
}

void SQLIST_ClearList(SqList *list) {
    assert(list != NULL);
    list->length = 0;
}

Status SQLIST_GetElem(const SqList *list, const int pos, ElemType *out_elem) {
    assert(list != NULL && out_elem != NULL);
    const int len = SQLIST_ListLength(list);
    if (0 == len) {
        return EMPTY;
    }
    if (pos < 1 || pos > len) {
        return OVERFLOW;
    }
    *out_elem = list->data[pos - 1];
    return OK;
}

int SQLIST_LocateElem(const SqList *list, const ElemType e) {
    assert(list != NULL);
    const int len = SQLIST_ListLength(list);
    for (int i = 0; i < len; ++i) {
        if (list->data[i] != e) {
            continue;
        }
        return i + 1;
    }
    return 0;
}

Status SQLIST_ListInsert(SqList *list, const int pos, const ElemType e) {
    assert(list != NULL);
    const int len = SQLIST_ListLength(list);
    if (SQLIST_MAXSIZE == len) {
        return FULL;
    }
    if (pos < 1 || pos > len + 1) {
        return OVERFLOW;
    }
    if (pos != len + 1) {
        for (int i = len; i >= pos; --i) {
            list->data[i] = list->data[i - 1];
        }
    }
    list->data[pos - 1] = e;
    ++(list->length);
    return OK;
}

Status SQLIST_ListDelete(SqList *list, const int pos, ElemType *out_elem) {
    assert(list != NULL);
    const int len = SQLIST_ListLength(list);
    if (0 == len) {
        return EMPTY;
    }
    if (pos < 1 || pos > len) {
        return OVERFLOW;
    }
    if (out_elem != NULL) {
        *out_elem = list->data[pos - 1];
    }
    if (pos != len) {
        for (int i = pos; i < len; ++i) {
            list->data[i - 1] = list->data[i];
        }
    }
    --(list->length);
    return OK;
}

int SQLIST_ListLength(const SqList *list) {
    assert(list != NULL);
    return list->length;
}

void SQLIST_PrintList(const SqList *list) {
    assert(list != NULL);
    const int len = SQLIST_ListLength(list);
    printf("List length: [%d]\n", len);
    printf("List elements: ");
    for (int i = 0; i < len; ++i) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

void SQLIST_example() {
#ifdef SQLIST_ENABLE_EXAMPLE
    printf("========================\n");
    printf("in %s::%d::\n", __func__, __LINE__);

    SqList a;
    SQLIST_InitList(&a);

    printf("before insert 5 elements:\n");
    SQLIST_PrintList(&a);

    for (int i = 1; i <= 5; ++i) {
        Status ret = 
            SQLIST_ListInsert(&a, i, i * 10);
        assert(OK == ret);
    }
    printf("List a after insert 5 elements:\n");
    SQLIST_PrintList(&a);
    ElemType tmp_elem;
    Status ret = 
        SQLIST_ListDelete(&a, 3, &tmp_elem);
    assert(OK == ret);
    printf("List a after delete element at pos 3 (elem=%d):\n", tmp_elem);
    SQLIST_PrintList(&a);
    ret = SQLIST_ListInsert(&a, 1, 21);
    printf("List a after insert 21 at pos 1 :\n");
    SQLIST_PrintList(&a);

    SqList b;
    SQLIST_InitList(&b);
    for (int i = 3; i <= 5; ++i) {
        SQLIST_ListInsert(&b, i-2, i * 10); // b = [30,40,50]
    }
    SQLIST_unionL(&a, &b);
    printf("After union: ");
    SQLIST_PrintList(&a);
#endif
}
