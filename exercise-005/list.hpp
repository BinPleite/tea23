// Die .hpp (Header-Datei) ist im Grunde das Inhaltsverzeichnis 
// oder die Visitenkarte deines Codes. Sie ist dafür zuständig, 
// dem Compiler zu sagen, was existiert, ohne zu verraten, 
// wie es im Detail funktioniert.

// --- Include Guards ---
// Diese #ifndef, #define und das #endif am Ende verhindern, dass der Header
// versehentlich mehrfach eingebunden wird, was zu Fehlern führen würde.
#ifndef MY_FANCY_LINKED_LIST_H__
#define MY_FANCY_LINKED_LIST_H__

// --- Definition eines einzelnen Knotens ---
// Ein Knoten speichert einen Wert und weiß, wo der nächste Knoten liegt.
typedef struct ListNode {
    unsigned int data;       // Der Wert, den wir speichern (hier ein positiver Integer)
    struct ListNode* pNext;  // Ein Zeiger auf den *nächsten* Knoten in der Kette.
                             // 'struct ListNode*' bedeutet: Es zeigt auf ein Objekt desselben Typs.
} ListNode_t; // Wir nennen diesen Typ ab jetzt kurz 'ListNode_t'

// --- Definition der gesamten Liste ---
// Diese Struktur verwaltet die Liste als Ganzes.
typedef struct List {
    ListNode_t* pHead;  // Zeiger auf den ersten Knoten (Start der Liste)
    ListNode_t* pTail;  // Zeiger auf den letzten Knoten (Ende der Liste) -> Wichtig für schnelles Einfügen am Ende!
    unsigned int size;  // Zähler, wie viele Elemente gerade in der Liste sind
} List_t; // Wir nennen diesen Typ ab jetzt kurz 'List_t'


// --- Funktionsprototypen (Die API) ---
// Hier versprechen wir dem Compiler: "Es gibt diese Funktionen, der Code kommt später."

// 1. Knoten erstellen & löschen
ListNode_t* NewListNode(void);       // Erstellt einen neuen, leeren Knoten auf dem Heap (malloc)
void FreeListNode(ListNode_t* elem); // Gibt den Speicher eines einzelnen Knotens wieder frei (free)

// 2. Liste erstellen & löschen
List_t* NewList(void);    // Erstellt eine neue, leere Listen-Verwaltung (List_t)
void FreeList(List_t*);   // Löscht die ganze Liste inkl. aller Knoten darin

// 3. Einfügen
int InsertIntoLinkedList(List_t* list, ListNode_t* elem); // Fügt 'elem' am Ende (bei pTail) an
int InsertIntoLinkedListAfterNode(List_t* list, ListNode_t* node, ListNode_t* elem); 
// Fügt 'elem' mitten in der Liste ein, direkt hinter dem Knoten 'node'

// 4. Löschen
int RemoveFromList(List_t* list, ListNode_t* elem); // Sucht 'elem' in der Liste und entfernt es (verkettet Vorgänger mit Nachfolger)

// 5. Traversieren (Durchlaufen)
ListNode_t* GetNext(const List_t* list, ListNode_t* elem); 
// Hilfsfunktion zum Durchlaufen:
// - Wenn elem NULL ist -> Gib Start (pHead) zurück
// - Sonst -> Gib den Nachfolger (elem->pNext) zurück

#endif // Ende des Include Guards
