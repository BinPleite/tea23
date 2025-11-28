/**
 * list.cpp
 * 
 * Implementierung der einfach verketteten Liste.
 * Hier befindet sich die Programlogik (das "Wie"), passend zum Header (das "Was").
 */

#include "list.hpp"   // Wir binden unsere eigene Header-Datei ein, um List_t und ListNode_t zu kennen.
#include <stdlib.h>   // Wird benötigt für malloc (Speicher reservieren) und free (Speicher freigeben).
#include <stdio.h>    // (Optional) Hilft manchmal, falls NULL nicht definiert ist.

// Sicherheitsnetz: Falls der Compiler NULL nicht kennt, definieren wir es als 0.
#ifndef NULL
#define NULL 0
#endif

// =========================================================
// 2.1 KNOTENVERWALTUNG
// =========================================================

/**
 * Erstellt einen neuen, leeren Knoten auf dem "Heap" (dynamischer Speicher).
 * Rückgabe: Zeiger auf den neuen Knoten oder NULL, wenn der Speicher voll ist.
 */
ListNode_t* NewListNode(void) {
    // 1. Wir bitten das Betriebssystem um Speicherplatz für genau EINEN Knoten.
    // sizeof(ListNode_t) berechnet automatisch die benötigte Byte-Größe.
    // (ListNode_t*) castet den allgemeinen Zeiger (void*) in unseren spezifischen Typ.
    ListNode_t* newNode = (ListNode_t*)malloc(sizeof(ListNode_t));

    // 2. Wir prüfen, ob wir den Speicher wirklich bekommen haben.
    if (newNode != NULL) {
        newNode->data = 0;      // Wir initialisieren den Wert sicherheitshalber mit 0.
        newNode->pNext = NULL;  // WICHTIG: Der Zeiger muss auf NULL gesetzt werden, 
                                // sonst zeigt er irgendwohin (Zufallswert) -> Absturzgefahr!
    }

    return newNode; // Wir geben die Adresse des neuen Knotens an den Aufrufer zurück.
}

/**
 * Gibt den Speicher eines einzelnen Knotens wieder frei.
 * Wichtig: Kümmert sich NICHT um die Liste, sondern löscht nur dieses eine Element.
 */
void FreeListNode(ListNode_t* elem) {
    // Nur freigeben, wenn der Zeiger auch wirklich auf etwas zeigt.
    if (elem != NULL) {
        free(elem); // Sag dem Betriebssystem: "Diesen Speicher brauche ich nicht mehr."
    }
}


// =========================================================
// 2.2 LISTENVERWALTUNG
// =========================================================

/**
 * Erstellt eine neue Listen-Verwaltungsstruktur.
 * Das ist quasi der "Kopf", der weiß, wo die Liste anfängt und aufhört.
 */
List_t* NewList(void) {
    // Speicher für die Verwaltungsstruktur (List_t) holen.
    List_t* newList = (List_t*)malloc(sizeof(List_t));

    if (newList != NULL) {
        newList->pHead = NULL; // Am Anfang zeigt Head auf nichts (Liste leer).
        newList->pTail = NULL; // Tail zeigt auch auf nichts.
        newList->size = 0;     // Größe ist 0.
    }

    return newList;
}

/**
 * Löscht die gesamte Liste und alle darin enthaltenen Knoten.
 * Das ist wichtig, um "Memory Leaks" (Speicherlecks) zu verhindern.
 */
void FreeList(List_t* list) {
    // Wenn die Liste gar nicht existiert, brechen wir ab.
    if (list == NULL) return;

    // Wir starten ganz vorne beim Head.
    ListNode_t* current = list->pHead;
    ListNode_t* nextNode = NULL;

    // Schleife: Solange wir noch Knoten haben...
    while (current != NULL) {
        // TRICK: Wir müssen uns den Nächsten merken, BEVOR wir den aktuellen löschen.
        nextNode = current->pNext; 
        
        // Jetzt können wir den aktuellen Knoten gefahrlos löschen.
        FreeListNode(current);     
        
        // Wir springen zum gemerkten Nächsten.
        current = nextNode;        
    }

    // Ganz am Ende löschen wir noch die Verwaltungsstruktur (den "Kopf") selbst.
    free(list);
}


// =========================================================
// 2.3 EINFÜGEN
// =========================================================

/**
 * Fügt ein neues Element am ENDE der Liste ein.
 * Rückgabe: 0 bei Erfolg, -1 bei Fehler.
 */
int InsertIntoLinkedList(List_t* list, ListNode_t* elem) {
    // Sicherheitscheck: Sind Liste und Element gültig?
    if (list == NULL || elem == NULL) {
        return -1; // Fehlercode zurückgeben
    }

    // Fall 1: Die Liste ist noch komplett leer.
    if (list->pHead == NULL) {
        list->pHead = elem; // Der neue Knoten ist jetzt der Anfang...
        list->pTail = elem; // ...und gleichzeitig das Ende.
    } 
    // Fall 2: Es sind schon Elemente da.
    else {
        // Der bisherige letzte Knoten (Tail) soll auf den Neuen zeigen.
        list->pTail->pNext = elem;
        
        // Der Zeiger für das Ende (Tail) wird auf den neuen Knoten aktualisiert.
        list->pTail = elem;
    }

    // Der neue letzte Knoten zeigt immer auf NULL (Ende der Fahnenstange).
    elem->pNext = NULL;
    
    // Wir erhöhen den Zähler für die Anzahl der Elemente.
    list->size++;
    
    return 0; // Erfolg
}

/**
 * Fügt ein Element GENAU NACH einem bestimmten anderen Knoten ein.
 * Nützlich, um mitten in die Liste zu schreiben.
 */
int InsertIntoLinkedListAfterNode(List_t* list, ListNode_t* node, ListNode_t* elem) {
    // Sicherheitscheck: Wir brauchen Liste, Vorgänger-Knoten (node) und neuen Knoten (elem).
    if (list == NULL || node == NULL || elem == NULL) {
        return -1;
    }

    // 1. Der neue Knoten übernimmt den Nachfolger vom alten Knoten.
    // (Er "greift" sich die Hand des Nächsten).
    elem->pNext = node->pNext;
    
    // 2. Der alte Knoten zeigt jetzt auf den Neuen.
    // (Er lässt den Alten los und "greift" sich den Neuen).
    node->pNext = elem;

    // Sonderfall: Wenn wir ganz am Ende eingefügt haben (hinter dem bisherigen Tail)...
    if (node == list->pTail) {
        list->pTail = elem; // ...dann ist der Neue jetzt der offizielle Tail.
    }

    list->size++;
    return 0;
}


// =========================================================
// 2.4 ENTFERNEN
// =========================================================

/**
 * Entfernt ein bestimmtes Element aus der Liste.
 * Schwierigkeit: Wir brauchen den Vorgänger, um die Kette wieder zu schließen!
 */
int RemoveFromList(List_t* list, ListNode_t* elem) {
    // Check ob Liste existiert, leer ist oder Element ungültig ist.
    if (list == NULL || list->pHead == NULL || elem == NULL) {
        return -1;
    }

    ListNode_t* current = list->pHead; // Startläufer
    ListNode_t* prev = NULL;           // Merker für den Vorgänger

    // Wir laufen durch die Liste und suchen 'elem'.
    // Gleichzeitig merken wir uns immer, wo wir gerade herkommen (prev).
    while (current != NULL && current != elem) {
        prev = current;           // Aktuellen als "Vorgänger" merken
        current = current->pNext; // Einen Schritt weitergehen
    }

    // Wenn 'current' NULL ist, sind wir am Ende rausgefallen -> Element nicht gefunden.
    if (current == NULL) {
        return -1; 
    }

    // Jetzt wird gelöscht (ausgekettet).
    
    // Fall A: Wir löschen das allererste Element (Head).
    if (current == list->pHead) {
        list->pHead = current->pNext; // Head rückt einfach eins weiter.
        
        // Wenn das das einzige Element war, ist die Liste jetzt leer.
        // Dann muss auch Tail auf NULL gesetzt werden.
        if (list->pHead == NULL) {
            list->pTail = NULL;
        }
    } 
    // Fall B: Wir löschen ein Element aus der Mitte oder vom Ende.
    else {
        // Der Vorgänger überspringt den zu Löschenden und zeigt direkt auf den Nachfolger.
        prev->pNext = current->pNext;
        
        // Wenn wir zufällig das letzte Element (Tail) gelöscht haben...
        if (current == list->pTail) {
            list->pTail = prev; // ...dann ist der Vorgänger jetzt das neue Ende.
        }
    }

    // Speicher des gelöschten Knotens freigeben.
    FreeListNode(current);
    list->size--; // Größe anpassen.

    return 0;
}


// =========================================================
// 2.5 TRAVERSIEREN (Hilfsfunktion)
// =========================================================

/**
 * Gibt den nächsten Knoten zurück.
 * Dient dazu, durch die Liste zu iterieren (For-Schleife).
 */
ListNode_t* GetNext(const List_t* list, ListNode_t* elem) {
    if (list == NULL) return NULL;

    // Wenn 'elem' NULL ist, bedeutet das: "Gib mir den allerersten Knoten".
    if (elem == NULL) {
        return list->pHead;
    }

    // Ansonsten gib einfach den Nachfolger zurück.
    return elem->pNext;
}
