#ifndef MY_FANCY_LINKED_LIST_H__
#define MY_FANCY_LINKED_LIST_H__

typedef struct ListNode {
    unsigned int data;
    struct ListNode* pNext;
} ListNode_t;

typedef struct List {
    ListNode_t* pHead;
    ListNode_t* pTail;
    unsigned int size;
} List_t;

ListNode_t* NewListNode(void);
void FreeListNode(ListNode_t* elem);

List_t* NewList(void);
void FreeList(List_t*);

int InsertIntoLinkedList(List_t* list, ListNode_t* elem);
int InsertIntoLinkedListAfterNode(List_t* list, ListNode_t* node /* the node we insert the element into */, ListNode_t* elem);
int RemoveFromList(List_t* list, ListNode_t* elem);
ListNode_t* GetNext(const List_t* list, ListNode_t* elem);

#endif