/**
 * vector.cpp
 * 
 * Implementierung des Mini-Vectors (dynamisches Array).
 * Ein Vektor ist im Grunde ein Array, das automatisch mitwächst, wenn es voll ist.
 */

#include "vector.hpp"   // Wir brauchen die Struktur-Definition (Vector_t)
#include <stdlib.h>     // Für malloc, free und realloc (Speicherverwaltung)
#include <fmt/format.h> // Für fmt::print (Ausgabe auf die Konsole)

// =========================================================
// INITIALISIERUNG
// =========================================================

/**
 * Initialisiert einen neuen Vektor.
 * Reserviert Speicher für die Startkapazität von 4 Elementen.
 */
void vector_init(Vector_t* vec) {
    // Sicherheitscheck: Wurde überhaupt ein gültiger Vektor übergeben?
    if (vec == NULL) return;

    vec->size = 0;      // Am Anfang sind 0 Elemente drin (Logische Größe)
    vec->capacity = 4;  // Aber wir haben Platz für 4 Elemente (Physische Größe)
    
    // Wir reservieren Speicherplatz auf dem Heap.
    // Kapazität * Größe eines unsigned int (meist 4 Byte) = Gesamtbytes.
    vec->data = (unsigned int*)malloc(vec->capacity * sizeof(unsigned int));
    
    // Hinweis: Hier könnte man noch prüfen, ob malloc NULL zurückgegeben hat (Speicher voll),
    // aber für diese Übung gehen wir davon aus, dass es klappt.
}

/**
 * Gibt den reservierten Speicher wieder frei und setzt alles auf 0.
 */
void vector_clear(Vector_t* vec) {
    if (vec == NULL) return;

    // Nur freigeben, wenn auch wirklich Speicher da ist.
    if (vec->data != NULL) {
        free(vec->data); // Den Speicherblock zurück ans System geben.
        vec->data = NULL; // Zeiger auf NULL setzen, damit niemand mehr darauf zugreift (Dangling Pointer vermeiden).
    }
    
    // Reset der Metadaten
    vec->size = 0;
    vec->capacity = 0;
}


// =========================================================
// EINFÜGEN
// =========================================================

/**
 * Fügt ein neues Element hinten an den Vektor an.
 * Wenn der Platz nicht reicht, wird der Speicher automatisch vergrößert (verdoppelt).
 */
int vector_push_back(Vector_t* vec, unsigned int value) {
    if (vec == NULL) return -1;

    // Prüfen: Ist der Vektor voll? (Anzahl Elemente == Maximale Kapazität)
    if (vec->size >= vec->capacity) {
        
        // 1. Neue Kapazität berechnen: Einfach verdoppeln (* 2).
        // Das ist effizient ("amortisierte Laufzeit"), weil wir nicht ständig neu reservieren müssen.
        size_t newCapacity = vec->capacity * 2; 
        
        // 2. Speicher vergrößern mit 'realloc'.
        // realloc versucht, den bestehenden Speicherblock zu vergrößern.
        // Wenn das nicht geht, sucht es einen neuen, größeren Platz, KOPIERT die alten Daten rüber
        // und gibt den alten Platz frei. Das alles macht realloc automatisch für uns!
        unsigned int* newData = (unsigned int*)realloc(vec->data, newCapacity * sizeof(unsigned int));
        
        // Check: Hat das Vergrößern geklappt?
        if (newData == NULL) {
            return -1; // Fehler: Kein Speicher mehr da!
        }
        
        // 3. Die neuen Daten übernehmen
        vec->data = newData;       // Der Zeiger auf die Daten (könnte eine neue Adresse sein)
        vec->capacity = newCapacity; // Die neue, größere Kapazität merken
    }

    // Jetzt ist garantiert genug Platz da.
    // Wir schreiben den Wert an die Stelle 'size' (das ist der erste freie Platz).
    vec->data[vec->size] = value;
    
    // Zähler für die Elemente um eins erhöhen.
    vec->size++;

    return 0; // Erfolg
}


// =========================================================
// ZUGRIFF & AUSGABE
// =========================================================

/**
 * Holt ein Element an einem bestimmten Index heraus.
 * Mit Bounds-Check (Prüfung, ob der Index gültig ist).
 */
int vector_get(const Vector_t* vec, size_t index, unsigned int* outValue) {
    // Sicherheitscheck für Zeiger
    if (vec == NULL || outValue == NULL) return -1;

    // Bounds Check: Wollen wir auf einen Index zugreifen, den es gar nicht gibt?
    // Beispiel: Size ist 3 (Indizes 0, 1, 2), aber wir wollen Index 5.
    if (index >= vec->size) {
        return -1; // Fehler: Index Out of Bounds
    }

    // Wert an die Zielvariable schreiben (über den Pointer outValue)
    *outValue = vec->data[index];
    
    return 0; // Erfolg
}

/**
 * Gibt den gesamten Inhalt des Vektors auf der Konsole aus.
 * Nutzt fmt::print für schöne Formatierung.
 */
void vector_print(const Vector_t* vec) {
    if (vec == NULL) return;

    // Kopfzeile mit Infos zu Größe und Kapazität
    fmt::print("Vector (Size: {}, Cap: {}): [ ", vec->size, vec->capacity);
    
    // Alle Elemente durchlaufen und ausgeben
    for (size_t i = 0; i < vec->size; i++) {
        fmt::print("{} ", vec->data[i]);
    }
    
    fmt::print("]\n");
}
