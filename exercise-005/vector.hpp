/**
 * vector.hpp
 * 
 * Header-Datei für den Mini-Vector.
 * Definiert die Struktur und die Funktionen (Schnittstelle),
 * die wir nutzen können.
 */

// Include Guards verhindern doppeltes Einbinden
#ifndef VECTOR_HPP
#define VECTOR_HPP

// stddef.h (oder cstddef) definiert den Typ 'size_t'.
// size_t ist ein unsigned int, der groß genug ist, um Speichergrößen zu speichern.
#include <stddef.h> 

// Die Struktur für unseren Vektor
typedef struct Vector {
    unsigned int* data;  // Zeiger auf das dynamische Array im Speicher (Startadresse)
    size_t size;         // Wie viele Elemente sind TATSÄCHLICH gerade drin?
    size_t capacity;     // Wie viel Platz haben wir RESERVIERT? (immer >= size)
} Vector_t;

// --- Funktionsprototypen (API) ---

// Initialisiert den Vektor (Reserviert ersten Speicher)
void vector_init(Vector_t* vec);

// Räumt auf: Gibt den gesamten Speicher wieder frei
void vector_clear(Vector_t* vec);

// Fügt ein Element am Ende hinzu (Vergrößert Speicher bei Bedarf automatisch)
int vector_push_back(Vector_t* vec, unsigned int value);

// Liest ein Element an einem Index sicher aus (mit Bounds Check)
// Der Wert wird in 'outValue' geschrieben. Rückgabe ist 0 (ok) oder -1 (Fehler).
int vector_get(const Vector_t* vec, size_t index, unsigned int* outValue);

// Gibt den Vektor zur Kontrolle auf der Konsole aus
void vector_print(const Vector_t* vec);

#endif // Ende Include Guard
