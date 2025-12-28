#include <stddef.h>
#include <assert.h>
#include <stdio.h>

#include "sqlist.h"
#include "types.h"

void SQLIST_unionL(SqList *a, const SqList *b) {
    assert(a != NULL && b != NULL);
    const int blist_len = SQLIST_ListLength(b);
    for (int i = 1; i <= blist_len; ++i) {
        ElemType elem;
        Status ret = SQLIST_GetElem(b, i, &elem);
        assert(OK == ret);
        if (SQLIST_LocateElem(a, elem) != 0) {
            continue;
        }
        const int pos = SQLIST_ListLength(a) + 1;
        ret = SQLIST_ListInsert(a, pos, elem);
        if (ret != OK) {
            assert(FULL == ret);
            break;
        }
    }
}

void SQLIST_InitList(SqList *list) {
    assert(list != NULL);
    list->length = 0;
}

bool SQLIST_ListEmpty(const SqList *list) {
    assert(list != NULL);
    return (SQLIST_ListLength(list) == 0);
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
        if (e == list->data[i]) {
            return i + 1; // 返回位置，位置从1开始
        }
    }
    return 0; // 未找到
}

Status SQLIST_ListInsert(SqList *list, const int pos, const ElemType e) {
    assert(list != NULL);
    const int len = SQLIST_ListLength(list);
    if (LINEAR_LIST_MAXSIZE == len) {
        return FULL;
    }
    if (pos < 1 || pos > len + 1) {
        return OVERFLOW;
    }
    // 将要插入位置后的元素向后移一位
    for (int i = len - 1; i >= pos - 1; --i) {
        list->data[i + 1] = list->data[i];
    }

    list->data[pos - 1] = e; // 插入新元素
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
        *out_elem = list->data[pos - 1]; // 取出删除元素
    }
    for (int i = pos; i < len; ++i) {
        // 将删除位置后的元素向前移一位
        list->data[i - 1] = list->data[i];
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

#endif
}
