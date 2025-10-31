# Übungsaufgabe: 🎃 Der Fluch des Speichers – Halloween Special

**Veranstaltung:** Mikrocomputertechnik 3  
**Datum:** 31. Oktober  
**Themen:** Stack, Heap, Zeiger, Speicherfehler, Debugging  
**Ziel:** Spielerische Wiederholung der Speicherverwaltung und Zeigermechanismen in C/C++

---

## 🧙‍♂️ Story

Ein uralter Speicherfluch lastet auf eurem Programm:  
Der **Stackdämon** erwacht bei jedem rekursiven Aufruf,  
und im **Heap** spuken die Geister vergessener `free()`-Aufrufe.  

Doch dies ist nicht das Ende:  
In alten Modulen wurden längst vergessene Variablen erneut **zum Leben erweckt** –  
die **Untoten Variablen**.  
Sie tragen denselben Namen, doch wohnen in verschiedenen Speicherreichen.  

Später, beim **Lagerfeuer im Ferienlager der Speicherjäger**, kursiert eine 
Gruselgeschichte über eine **heiße Kartoffel** – einen Pointer, der von Hand zu Hand 
gereicht wird, bis niemand mehr weiß, woher er stammt... und was er noch berührt. 🔥🏕️

Nur wer die Gesetze von **Stack, Heap, Data-Segment und Zeigern** versteht,  
kann den Fluch brechen und den Speicher reinigen.

Heute tretet ihr als **Speicherjäger** an, um die Dämonen zu bannen.  
Euer Werkzeug: C, `fmt`, und scharfer Verstand. 💀

---

## 🧰 Vorbereitung

### Notwendige git Kommandos

```sh
git remote -v
origin  https://github.com/IhrBenutzerName/tea23 (fetch)
origin  https://github.com/IhrBenutzerName/tea23 (push)
upstream        https://github.com/graugans/tea23.git (fetch)
upstream        https://github.com/graugans/tea23.git (push)

git fetch --all
git switch -c solution-002 upstream/excercise-002 
git push -u origin solution-002 
```

---

## 🧟‍♂️ Programm kompilieren und ausführen

```sh
cmake --build build
./build/bin/halloween
```

> **Hinweis:**  
> Das `./` vor dem Programmnamen weist Linux an, das Programm im **aktuellen Verzeichnis** zu starten.  
> Ohne `./` sucht das System nur in `/usr/bin`, `/bin`, etc.

---

## 🧠 Ziel der Übung

- Stack und Heap unterscheiden  
- Typische Speicherfehler erkennen  
- Zeiger richtig verwenden  
- Verständnis für globale, lokale und statische Variablen  
- **Dangling Pointers** erkennen und vermeiden  
- Spaß an Halloween haben 🎃  

---

## ☠️ Aufgabe 1 – Pointer oder Poltergeist?

Beantworten Sie die folgenden Fragen, um Ihren Speicher zu „entfluchen“.  
Jede richtige Antwort bringt **1 Exorzismus-Punkt**.

| Nr. | Frage | Antwortmöglichkeiten |
|:--:|:-------|:---------------------|
| 1 | Was passiert, wenn ein Pointer auf eine lokale Variable nach Funktionsende zeigt? | a) Es entsteht ein Zombie-Pointer 🧟<br>b) Alles gut<br>c) Der Heap lacht |
| 2 | Warum darf `free()` nur auf dynamisch allozierten Speicher angewendet werden? | a) Sonst wird der Stack instabil<br>b) Undefined Behavior<br>c) Der Garbage Collector ruft „Buh!“ |
| 3 | Warum ist Rekursion gefährlich ohne Abbruchbedingung? | a) Stack Overflow<br>b) Heap Overflow<br>c) Heapdämon ruft `malloc()` unendlich oft |
| 4 | Wie nennt man Speicher, der nie wieder freigegeben wird? | a) Memory Leak 👻<br>b) Stack Frame<br>c) Lost Pointer |

> 💬 **Diskussion:**  
> Welche Fehler sind in echten Mikrocontrollersystemen besonders kritisch?

---

## 💀 Aufgabe 2 – Der Heap der verlorenen Seelen

Analysieren Sie die folgenden Programme.  
Erklären Sie jeweils:

1. Was passiert technisch?  
2. Welcher „Fluch“ (Fehler) entsteht?  
3. Wie kann man ihn bannen?

---

### Beispiel 1: Der vergessene Geist

```cpp
#include <fmt/format.h>
#include <cstdlib>
#include <cstring>

#define SOULS 100

void cursed() {
    char *soul = (char*)malloc(8);
    strcpy(soul, "boo!");
    fmt::println("{}", soul);
}

int main() {
    for(int i=0; i < SOULS; i++) {
        cursed();
    }
}
```

- Führen Sie eine Exorzismus durch: Wo müsste `free()` aufgerufen werden?

---

### Beispiel 2: Der Zombie-Pointer

```cpp
#include <fmt/format.h>
#include <cstdlib>
#include <cstring>

int main() {
    char *ghost = (char*)malloc(8);
    strcpy(ghost, "evil");
    free(ghost);
    fmt::println("{}", ghost);
}
```

- Was passiert, wenn Sie anschließend **erneut Speicher allokieren**?  
  - Prüfen und vergleichen Sie die Adressen und überlegen Sie mögliche Fehlerquellen.

---

### Beispiel 3: Der Dämon des unendlichen Wachstums

```cpp
#include <cstdlib>

int main() {
    while (1) {
        malloc(1024);
    }
}
```

> 🧩 **Aufgabe:**  
> Erklären Sie, was hier langfristig passiert – und was das für ein Embedded-System bedeuten würde.

---

## ⚔️ Aufgabe 3 – Stack vs. Heap: Das Duell der Untoten

### Schritt 1: Gruppenbildung

- **Team Stack** – organisiert, schnell, aber begrenzt.  
- **Team Heap** – flexibel, aber chaotisch und langsam.

### Schritt 2: Vorbereitung (10 min)

Jedes Team erstellt **3 Argumente**, warum es „überleben“ sollte.  
Beispiel:
> „Ich bin der Stack – diszipliniert, ordentlich, und sterbe nur bei Overflow!“

### Schritt 3: Duell (15 min)

- Abwechselnde 1-minütige Redebeiträge  
- Jury (die anderen Studierenden) vergeben Punkte für:
  - technische Richtigkeit ✅  
  - Kreativität 🎭  
  - Gruselfaktor 💀  

> 🏆 Das Siegerteam wird zum **Meister des Speichers** gekrönt.

---

## 🧛 Aufgabe 4 – Der Exorzismus

Kurze gemeinsame Reflexion:

- Wann tritt ein Stack Overflow auf?  
- Warum entstehen Memory Leaks?  
- Was ist gefährlicher: Ein Zombie-Pointer oder ein Leak?  
- Wie kann man solche Fehler frühzeitig erkennen?  

Optional:  
> Zeichnen Sie ein einfaches Diagramm, das Stack, Heap, Code und Daten-Segment im Speicher zeigt.  
> Markieren Sie typische Speicherorte der Beispiele aus Aufgabe 2.

---

## 🧟 Aufgabe 5 – Die Rückkehr der Untoten Variablen

> In einem alten C-Modul erwachen längst vergessene Variablen erneut zum Leben.  
> Sie tragen denselben Namen, doch bewohnen verschiedene Speicherreiche:  
> **globale, lokale und statische** Variablen kämpfen um die Vorherrschaft im RAM.

Erstellen Sie ein separates Modul `graveyard.cpp` (mit Header `graveyard.h`).  
Analysieren Sie das Verhalten gleichnamiger Variablen in unterschiedlichen Kontexten.

---

### Beispielcode (in `graveyard.cpp`)

```c
#include <fmt/format.h>

// Globale Variable – lebt im Datensegment
int undead = 13;

void awaken() {
    // Lokale Variable mit gleichem Namen
    int undead = 666;
    fmt::println("👁️  Die lokale Variable ruft: {}", undead);
}

void persistent() {
    static int undead = 42;
    undead++;
    fmt::println("💀 Der statische Geist zählt weiter: {}", undead);
}
```

---

### Beispielcode (in `main.cpp`)

```c
#include <fmt/format.h>
#include "graveyard.h"

int undead = 7;

int main() {
    fmt::println("🪦 Globale Variable sagt: {}", undead);
    awaken();
    persistent();
    persistent();
    fmt::println("🪦 Globale Variable nach Aufruf: {}", undead);
}
```

---

### Fragen dazu

1. Wie unterscheiden sich die Adressen der drei `undead`-Variablen?  
2. Warum bleibt der Wert in `persistent()` zwischen Aufrufen erhalten?  
3. Was passiert, wenn man `extern int undead;` in `graveyard.c` verwendet?  
4. In welchem Speicherbereich liegen:
   - die globale Variable `undead`?
   - die lokale Variable in `awaken()`?
   - die statische Variable in `persistent()`?

> 💬 **Diskussion:**  
> Welche „Untoten“ überleben das Ende der Funktion – und warum?

---

### 🕸️ Bonus: Der doppelte Fluch

Erstellen Sie ein weiteres Modul `curse.cpp`:

```c
int undead = 999;
void curse() { fmt::println("🧿 Der Fluch ruft: {}", undead); }
```

Binden Sie beide Header (`graveyard.h`, `curse.h`) in `main.cpp` ein.  
Untersuchen Sie, welche Variable wirklich „spricht“.  
> 💀 Tipp: Der Linker entscheidet, welcher Geist am Ende Besitz ergreift...

---

## 🔥 Aufgabe 6 – Die heiße Kartoffel am Lagerfeuer (Dangling-Pointer-Staffel)

> **Lagerfeuer-Szene:** „Reicht die Kartoffel weiter, aber verbrennt euch nicht!“  
> In unserer Geschichte ist die Kartoffel ein **Pointer auf eine lokale Variable** – heiß, flüchtig und gefährlich, sobald er das sichere Nest (den Stackframe) verlässt.

### Teil A: Der gruselige Ursprung

```c
// hot_potato.cpp
#include <fmt/format.h>

int* hot_potato() {
    int secret = 42;            // lokale Stack-Variable
    return &secret;             // ⚠️ Dangling Pointer
}

void tell(const char* who, int* p) {
    fmt::println("{} hält Kartoffel {} -> Wert: {}", who, fmt::ptr(p), *p);
}

int main() {
    int* p = hot_potato();      // zeigt auf toten Stackframe
    tell("🏕️ Alice", p);
    int filler = 123456;        // Stack wird verändert
    (void)filler;
    tell("🏕️ Bob", p);
    return 0;
}
```

**Aufgabe:** Kompilieren und mehrmals ausführen, auch mit unterschiedlichen Optimierungsstufen (`-O0` und `-O2`). Beobachten Sie: stabiler Wert, Zufallswerte, ggf. Absturz – **Undefined Behavior**.

### Teil B: Die Staffel – weiterreichen

```c
void stage1(int* p) { tell("🔥 Stage 1", p); }
void stage2(int* p) { tell("🔥 Stage 2", p); }
void stage3(int* p) { tell("🔥 Stage 3", p); }

int main() {
    int* p = hot_potato();
    stage1(p);
    stage2(p);
    stage3(p);
}
```

**Fragen:**  

1. Warum ist `p` nach Rückkehr aus `hot_potato()` prinzipiell ungültig?  
2. Welche Rolle spielen zusätzliche lokale Variablen/Funktionsaufrufe für die beobachteten Werte?  
3. Wie ändert sich das Verhalten unter `-O2`?

### Teil C: Exorzismen (sichere Varianten)

Implementieren Sie **eine** der folgenden Korrekturen und begründen Sie die Wahl:

**Variante 1 – Heap-Exorzismus**  

```c
int* hot_potato_heap() {
    int* p = (int*)malloc(sizeof(int));
    if (p) *p = 42;
    return p;                   // gültig bis free()
}
// Caller: free(p);
```

**Variante 2 – Der ewige Geist (static)**  

```c
int* hot_potato_static() {
    static int secret = 42;
    return &secret;             // eine einzige persistente Instanz
}
```

**Variante 3 – Kartoffel servieren, nicht reichen (By-Value/Out-Param)**  

```c
int hot_potato_value() { return 42; }

void hot_potato_into(int* out) { *out = 42; } // Caller stellt Speicher bereit
```

**Diskussion:**  

- Embedded: Welche Variante bevorzugen Sie und warum (Determinismus, RAM-Verbrauch, Ownership)?  
- Wer trägt Verantwortung für `free()` bei Variante 1?  
- Warum ist `static` nicht reentrant/thread-safe?

### Teil D: Tooling-Bonus (Desktop)

- Testen Sie mit **AddressSanitizer**: `-fsanitize=address -fno-omit-frame-pointer`  
- Oder mit **valgrind** (falls verfügbar): Meldungen interpretieren.

---

## 🧩 Fazit

Nach dieser Übung sollten Sie:

- Stack, Heap und Datensegmente sicher unterscheiden können  
- Typische Speicherfehler (Leak, Dangling Pointer, Stack Overflow) erkennen  
- Das Verhalten von Zeigern und statischen Variablen verstehen  
- Dangling Pointer thematisch greifbar machen (🔥 „heiße Kartoffel“)  
- Wissen, wie man mit `fmt` Adressen und Werte ausgibt  
- Und: Spaß am Debuggen haben 🕷️  

---

**Erstellt von:**  
_Institut für Mikrocomputertechnik_  
_"We scare undefined behavior away."_ 👾

---

## 🛠️ CMake & VS Code – praktische Tipps (Clang, Flags, Sanitizer)

> Empfohlen in VS Code: **CMake Tools** Erweiterung + **Clang** als Compiler auswählen (`CMake: Select Kit` → „Clang“).

### 1) Compiler auswählen (Clang)

- **VS Code:** `Strg+Shift+P` → **CMake: Select Kit** → *Clang* wählen.  
- **Shell (einmalig beim Konfigurieren):**
  
  ```sh
  cmake -S . -B build -G Ninja \
        -D CMAKE_C_COMPILER=clang \
        -D CMAKE_CXX_COMPILER=clang++
  ```

  > Tipp: Verwenden Sie **Ninja** als Generator für schnelle Builds.

### 2) Build-Typ setzen

- Single‑Config Generator (z. B. Ninja):

  ```sh
  cmake -S . -B build -D CMAKE_BUILD_TYPE=Debug      # oder Release, RelWithDebInfo
  cmake --build build
  ```

- Multi‑Config Generator (z. B. „Ninja Multi‑Config“, MSVC):

  ```sh
  cmake -S . -B build -G "Ninja Multi-Config"
  cmake --build build --config Debug                  # oder Release
  ```

### 3) Projektweite Compiler-Optionen (empfohlen)

In Ihrer `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.20)
project(halloween LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # für clangd / IntelliSense

add_executable(halloween
  src/main.cpp
  src/graveyard.cpp
  src/hot_potato.cpp
)

# Allgemeine Warnungen & Debug-Infos
target_compile_options(halloween PRIVATE
  $<$<C_COMPILER_ID:Clang,GNU>:-Wall -Wextra -Wpedantic -Wconversion -g>
  $<$<CXX_COMPILER_ID:Clang,GNU>:-Wall -Wextra -Wpedantic -Wconversion -g>
)

# Optimierungen & Sanitizer je nach Build-Typ
target_compile_options(halloween PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>>:-O0 -fsanitize=address,undefined -fno-omit-frame-pointer>
  $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>>:-O0 -fsanitize=address,undefined -fno-omit-frame-pointer>
  $<$<AND:$<CONFIG:Release>,$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>>:-O3>
  $<$<AND:$<CONFIG:Release>,$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>>:-O3>
)

target_link_options(halloween PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>>:-fsanitize=address,undefined>
  $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>>:-fsanitize=address,undefined>
)
```

### 4) Ziel-spezifisch statt global

Bevorzugen Sie `target_compile_options()`/`target_link_options()` gegenüber globalen Variablen wie `CMAKE_C_FLAGS`. So bleiben Flags **lokal pro Target** und reproduzierbar.

### 5) Standard setzen & Features deklarieren

```cmake
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
target_compile_features(halloween PRIVATE c_std_11 cxx_std_17)
```

### 6) Schnell schalten zwischen Debug/Release in VS Code

- Statusleiste → **[CMake: Debug]** anklicken → *Release* wählen.
- Bauen mit **CMake: Build** (oder `cmake --build build --config Release` bei Multi‑Config).

### 7) AddressSanitizer / UndefinedBehaviorSanitizer testen

- **Debug-Konfiguration** bauen (mit oben gesetzten Flags).  
- Ausführen wie gewohnt:
  
  ```sh
  ./build/bin/halloween
  ```

- Typische Fehlermeldungen zeigen **dangling pointers**, **use‑after‑free**, **out‑of‑bounds** etc.

---
