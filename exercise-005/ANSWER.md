# Antworten zu Aufgabe 5 – Vergleich Liste vs. Vector

### 1. Vorteile der verketteten Liste
*   **Effizientes Einfügen/Löschen:** Wenn man die Position (Zeiger) hat, geht das Einfügen oder Löschen sehr schnell (O(1)), da keine Elemente verschoben werden müssen.
*   **Dynamische Speicherverwaltung:** Es wird immer nur genau so viel Speicher belegt, wie für die Elemente nötig ist (kein ungenutzter "Reserve"-Speicher).
*   **Keine Fragmentierungsprobleme beim Vergrößern:** Die Liste muss keinen großen zusammenhängenden Block im Speicher finden, die Knoten können verstreut liegen.

### 2. Nachteile der verketteten Liste
*   **Langsamer Zugriff:** Kein direkter Zugriff auf Index `i`. Man muss immer von vorne durchlaufen (O(n)).
*   **Speicher-Overhead:** Jedes Element braucht zusätzlichen Speicher für den `pNext`-Zeiger (meist 4 oder 8 Byte extra).
*   **Schlechte Cache-Performance:** Da die Knoten verstreut im Speicher liegen, kann der CPU-Cache nicht effizient genutzt werden (viele Cache Misses).

### 3. Vorteile des Mini-Vectors (Dynamisches Array)
*   **Schneller Zugriff (Random Access):** Man kann auf jedes Element sofort zugreifen (`vec[i]`), Zeitkomplexität O(1).
*   **Sehr gute Cache-Performance:** Alle Daten liegen direkt hintereinander im Speicher.
*   **Geringer Overhead:** Es werden keine Zeiger pro Element gespeichert, nur die Nutzdaten.

### 4. Nachteile des Mini-Vectors
*   **Teures Vergrößern:** Wenn die Kapazität voll ist, muss neuer Speicher gesucht und *alles* umkopiert werden.
*   **Langsames Einfügen in der Mitte:** Wenn man vorne oder in der Mitte einfügt, müssen alle nachfolgenden Elemente verschoben werden (O(n)).
*   **Speicherverschnitt:** Es wird oft mehr Speicher reserviert (`capacity`), als gerade genutzt wird (`size`).

### 5. Wann benutzt man welche Struktur?
*   **Vector:** Ist fast immer die bessere Standardwahl (in 90-95% der Fälle), besonders wenn man oft lesend zugreift oder Daten meistens nur hinten anhängt.
*   **Liste:** Nur dann sinnvoll, wenn man sehr häufig Elemente *mitten in der Sequenz* einfügen oder löschen muss und man keinen schnellen Index-Zugriff braucht.

### 6. Was passiert, wenn man die Elemente sortiert?
*   **Beim Mini-Vector:** Das geht sehr schnell und effizient. Man kann Standard-Algorithmen wie *Quicksort* verwenden, da der Zugriff über Indizes möglich ist.
*   **Bei der Liste:** Das ist langsamer und komplizierter. Algorithmen wie Quicksort funktionieren schlecht (kein Random Access). Man verwendet hier meist *Mergesort*, da man dabei nur Zeiger umbiegen muss, statt Daten zu kopieren.

### 7. Wie würden Sie einen Binären Baum strukturieren?
Ein Binärer Baum ist im Grunde wie eine Liste, nur dass ein Knoten zwei Nachfolger hat statt einem.
Die Struktur würde so aussehen:

### Allg. 
cpp ist das ausführende Programm (Bauarbeiter) und hpp definiert die Variablen und den Speicher (Bauplan)
list.cpp und vector.cpp definieren die logik im main.cpp wird die logik dann umgesetzt oder verwendet
list.hpp definiert die benötigten Variablen und gibt sie für cpp frei