/**
 * main.cpp
 * 
 * Das Testprogramm.
 * Hier prüfen wir, ob unsere Liste (list.cpp) und unser Vektor (vector.cpp)
 * wirklich das tun, was sie sollen.
 */

#include <fmt/format.h> // Externe Bibliothek für einfache Textausgabe (wie printf, aber moderner)
#include "list.hpp"     // Damit wir die Listen-Funktionen kennen
#include "vector.hpp"   // Damit wir die Vektor-Funktionen kennen
#include <stdlib.h>     // Für NULL

int main() {
    // ==========================================
    // TEIL 1: TEST DER VERKETTETEN LISTE
    // ==========================================
    fmt::print("--- Start: Test der verketteten Liste ---\n");

    // 1. Wir erstellen eine leere Liste
    List_t* myList = NewList();

    // 2. Wir füllen die Liste mit 5 Elementen: 10, 20, 30, 40, 50
    for (unsigned int i = 1; i <= 5; i++) {
        ListNode_t* node = NewListNode(); // Neuen "Waggon" bauen
        node->data = i * 10;              // Ladung reinpacken
        InsertIntoLinkedList(myList, node); // An den Zug anhängen
    }

    // 3. Test: Einfügen mitten drin (nach der 20)
    // Dazu müssen wir erst zur 20 hinlaufen ("traversieren")
    ListNode_t* node1 = GetNext(myList, NULL);   // 1. Element holen (10)
    ListNode_t* node2 = GetNext(myList, node1);  // 2. Element holen (20) - DAS ist unser Ziel
    
    if (node2 != NULL) {
        ListNode_t* newNode = NewListNode();
        newNode->data = 999; // Wir nehmen einen auffälligen Wert
        // Einfügen genau hinter node2
        InsertIntoLinkedListAfterNode(myList, node2, newNode);
        fmt::print("Element 999 nach Element {} eingefügt.\n", node2->data);
    }
    // Erwarteter Stand: 10 -> 20 -> 999 -> 30 -> 40 -> 50

    // 4. Test: Ein bestimmtes Element entfernen (wir wollen die 40 löschen)
    // Wir suchen die 40 in der Liste
    ListNode_t* search = GetNext(myList, NULL);
    while (search != NULL) {
        if (search->data == 40) {
            // Gefunden! Raus damit.
            RemoveFromList(myList, search);
            fmt::print("Element mit Wert 40 entfernt.\n");
            break; // WICHTIG: Wir müssen aufhören, weil 'search' jetzt gelöscht (free) ist!
        }
        search = GetNext(myList, search); // Weiter zum Nächsten
    }
    // Erwarteter Stand: 10 -> 20 -> 999 -> 30 -> 50

    // 5. Ergebnis ausgeben (Traversieren)
    fmt::print("Aktueller Listeninhalt: ");
    ListNode_t* current = GetNext(myList, NULL);
    
    while (current != NULL) {
        fmt::print("{} -> ", current->data);
        current = GetNext(myList, current);
    }
    fmt::print("NULL\n");

    // 6. Aufräumen
    FreeList(myList); // Löscht Liste UND alle Knoten
    fmt::print("Liste freigegeben.\n\n");


    // ==========================================
    // TEIL 2: TEST DES MINI-VECTORS
    // ==========================================
    fmt::print("--- Start: Test des Mini-Vectors ---\n");

    // 1. Vektor anlegen
    // Hier legen wir die Struktur 'Vector_t' direkt auf dem Stack an (ohne malloc für die Struktur selbst).
    // Aber die DATEN im Vektor landen trotzdem auf dem Heap (durch vector_init).
    Vector_t myVec; 
    vector_init(&myVec); 

    // 2. Werte einfügen
    // Wir fügen 5 Werte ein. Da Startkapazität 4 ist, MUSS beim 5. Element vergrößert werden!
    vector_push_back(&myVec, 100);
    vector_push_back(&myVec, 200);
    vector_push_back(&myVec, 300);
    vector_push_back(&myVec, 400);
    vector_push_back(&myVec, 500); // Hier passiert intern das 'realloc'
    fmt::print("5 Werte in Vector eingefügt.\n");

    // 3. Test: Zufälligen Zugriff (Random Access) prüfen
    // Wir wollen den Wert an Index 2 (das 3. Element -> 300)
    unsigned int val = 0;
    if (vector_get(&myVec, 2, &val) == 0) {
        fmt::print("Wert an Index 2 ist: {}\n", val); // Sollte 300 sein
    } else {
        fmt::print("Fehler: Index 2 konnte nicht gelesen werden.\n");
    }

    // 4. Alles ausgeben
    vector_print(&myVec);

    // 5. Aufräumen
    vector_clear(&myVec); // Gibt den internen Speicher (data) frei
    fmt::print("Vector freigegeben.\n");

    return 0;
}
