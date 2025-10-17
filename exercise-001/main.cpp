#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

// Globale Variablen Teil 1 
int globalVar1 = 0;
int globalVar2 = 1;
int globalVar_; // keine Werte
int static globalVars = 2;
int const globalVarc = 3;

void foo(){

    fmt::print("Hallo from foo!\\n"); }


int main(int argc, char **argv) {

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tea::PROJECT_NAME);

    /* INSERT YOUR CODE HERE */

        /// Teil 1: Globale Variable
    
    fmt::print("Globale Variable1: {}\n", fmt::ptr(&globalVar1));
    fmt::print("Globale Variable2: {}\n", fmt::ptr(&globalVar2));
    fmt::print("Globale Variable_: {}\n", fmt::ptr(&globalVar_));
    fmt::print("Globale Variables: {}\n", fmt::ptr(&globalVars));
    fmt::print("Globale Variablec: {}\n", fmt::ptr(&globalVarc));

    /* Ausgabe: Addressen ändern sich bei neuem Ausführen
    Globale Variable0: 0x5bc380836028
    Globale Variable1: 0x5bc380836020
    Globale Variable_: 0x5bc38083602c
    */

    /*
    Globale Variable1: 0x64fad7baa02c
    Globale Variable2: 0x64fad7baa020
    Globale Variable_: 0x64fad7baa030
    Globale Variables: 0x64fad7baa024
    Globale Variablec: 0x64fad7ba8090 

    // Globale Variablen liegen im Data Segment und nicht im Stack

    // Static braucht viel mehr (8kb) speicher als ein const-Variable

    */

    /// Teil 2

    int localVar1 = 0;
    int localVar2 = 1;
    int localVar_;
    int localVars = 2;
    int localVarc = 3;

    fmt::print("Locale localVar1: {}\n", fmt::ptr(&localVar1));
    fmt::print("Locale localVar2: {}\n", fmt::ptr(&localVar2));
    fmt::print("Locale localVar_: {}\n", fmt::ptr(&localVar_));
    fmt::print("Locale localVars: {}\n", fmt::ptr(&localVars));
    fmt::print("Locale localVarc: {}\n", fmt::ptr(&localVarc));

    /*
    
    Locale localVar1: 0x7ffc0be3d594
    Locale localVar2: 0x7ffc0be3d590
    Locale localVar_: 0x7ffc0be3d58c
    Locale localVars: 0x7ffc0be3d588
    Locale localVarc: 0x7ffc0be3d584

    Erkenntnis:
    Neue lokale Variablen werden auf niedrigeren Adressen
    als vorherige Variable gelegt.
    */

    /// Teil 3

    int* heapVar = new int(3); 
    fmt::print("Addresse HeapVar: {}\n", fmt::ptr(&heapVar));
    fmt::print("Wert HeapVar: {}\n", *heapVar);

    // new int reserviert speicher auf dem Heap für eine einzelne int-Variable
    // heap speichert den Wert bis dieser speicher manuell freigegeben wird

    delete heapVar;
    fmt::print("Addresse HeapVar: {}\n", fmt::ptr(&heapVar));
    fmt::print("Wert HeapVar: {}\n", *heapVar);


    // Teil 4

    fmt::print("Address von foo: {} \n", fmt::ptr(&foo)); // kaufmanns und für die Addresse

    return 0; /* exit gracefully*/
}

/* FAZIT:
für weitere oder Zusammengefasste Erklärungen 
siehe Chati
*/ 

