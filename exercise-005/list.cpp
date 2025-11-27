#include "list.hpp"
#include <stdlib.h>   /* Achte auf < vorne und > hinten */
#include <stdio.h>    /* Hilft manchmal bei NULL Definitionen */

/* Falls NULL immer noch nicht erkannt wird, definieren wir es zur Sicherheit selbst: */
#ifndef NULL
#define NULL 0
#endif

// ---------------------------------------------------------
// 2.1 Knotenverwaltung
// ---------------------------------------------------------

ListNode_t* NewListNode(void) {
    // Speicher reservieren
    ListNode_t* newNode = (ListNode_t*)malloc(sizeof(ListNode_t));

    // Wenn Speicher erfolgreich reserviert wurde
    if (newNode != NULL) {
        newNode->data = 0;      // Standardwert 0
        newNode->pNext = NULL;  // Kein Nachfolger
    }

    return newNode;
}

void FreeListNode(ListNode_t* elem) {
    // Nur freigeben, wenn der Zeiger gültig ist
    if (elem != NULL) {
        free(elem);
    }
}

// ---------------------------------------------------------
// 2.2 Listenverwaltung
// ---------------------------------------------------------

List_t* NewList(void) {
    // Speicher für die Listen-Struktur reservieren
    List_t* newList = (List_t*)malloc(sizeof(List_t));

    if (newList != NULL) {
        newList->pHead = NULL;
        newList->pTail = NULL;
        newList->size = 0;
    }

    return newList;
}

void FreeList(List_t* list) {
    if (list == NULL) return;

    // Alle Knoten durchgehen und löschen
    ListNode_t* current = list->pHead;
    ListNode_t* nextNode = NULL;

    while (current != NULL) {
        nextNode = current->pNext; // Nächsten merken
        FreeListNode(current);     // Aktuellen löschen
        current = nextNode;        // Weiterspringen
    }

    // Die Liste selbst löschen
    free(list);
}

// ---------------------------------------------------------
// 2.3 Einfügen
// ---------------------------------------------------------

int InsertIntoLinkedList(List_t* list, ListNode_t* elem) {
    // Sicherheitscheck
    if (list == NULL || elem == NULL) {
        return -1; // Fehlercode
    }

    // Fall 1: Liste ist noch leer
    if (list->pHead == NULL) {
        list->pHead = elem;
        list->pTail = elem;
    } 
    // Fall 2: Liste hat schon Elemente
    else {
        list->pTail->pNext = elem; // Alten Tail auf neuen Knoten zeigen lassen
        list->pTail = elem;        // Neuer Knoten ist jetzt Tail
    }

    elem->pNext = NULL; // Das Ende zeigt immer auf NULL
    list->size++;
    
    return 0; // Erfolg
}

int InsertIntoLinkedListAfterNode(List_t* list, ListNode_t* node, ListNode_t* elem) {
    // Sicherheitscheck
    if (list == NULL || node == NULL || elem == NULL) {
        return -1;
    }

    // Einfügen zwischen 'node' und 'node->pNext'
    elem->pNext = node->pNext;
    node->pNext = elem;

    // Wenn wir nach dem Tail eingefügt haben, müssen wir den Tail aktualisieren
    if (node == list->pTail) {
        list->pTail = elem;
    }

    list->size++;
    return 0;
}

// ---------------------------------------------------------
// 2.4 Entfernen
// ---------------------------------------------------------

int RemoveFromList(List_t* list, ListNode_t* elem) {
    if (list == NULL || list->pHead == NULL || elem == NULL) {
        return -1;
    }

    ListNode_t* current = list->pHead;
    ListNode_t* prev = NULL;

    // Suchen des Elements und seines Vorgängers
    while (current != NULL && current != elem) {
        prev = current;
        current = current->pNext;
    }

    // Element nicht gefunden
    if (current == NULL) {
        return -1;
    }

    // Fall A: Wir löschen den Kopf (Head)
    if (current == list->pHead) {
        list->pHead = current->pNext;
        
        // Wenn die Liste jetzt leer ist, muss auch Tail NULL sein
        if (list->pHead == NULL) {
            list->pTail = NULL;
        }
    } 
    // Fall B: Wir löschen aus der Mitte oder am Ende
    else {
        prev->pNext = current->pNext;
        
        // Wenn wir den Tail gelöscht haben, ist der Vorgänger der neue Tail
        if (current == list->pTail) {
            list->pTail = prev;
        }
    }

    FreeListNode(current);
    list->size--;

    return 0;
}

// ---------------------------------------------------------
// 2.5 Traversieren
// ---------------------------------------------------------

ListNode_t* GetNext(const List_t* list, ListNode_t* elem) {
    if (list == NULL) return NULL;

    // Wenn elem NULL ist, gib den Start der Liste zurück
    if (elem == NULL) {
        return list->pHead;
    }

    // Sonst den Nachfolger
    return elem->pNext;
}
