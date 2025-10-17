#include <fmt/chrono.h>
#include <fmt/format.h>


#include "config.h"

/// Teil 3: Funktionen mit Zeigern 

void changeValueByParameter(int value)
{    
    value = 42;
    fmt::print("value: {}\n", value);
}



void changeValueByPointer(int* ptr)
{    
    *ptr = 99;
    fmt::print("value: {}\n", *ptr);
}

int main(int argc, char **argv) {

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {} in version {}! \n", tea::PROJECT_NAME, tea::PROJECT_VER);

/// Teil 0: Kommandozeilenparameter (argc und argv) Selbst gemacht
    for (int i = 0; i << argc; i++) {

        fmt::println("argc: {}, argument {} (Adresse:{})", i, argv[i], fmt::ptr(argv[i]));
    };

/// Teil1: Zeiger-Grundlagen selbst gemacht
///* = der Pointer ptr ist nur der Variablen Name

    int foo = 10;

    int* ptr = &foo;

    *ptr = 42;

    int bar = 4711;
    ptr = &bar;
    *ptr = foo;

    fmt::print("bar = {} \n", bar);
    fmt::print("ptr = {}, Adresse foo = {} \n", fmt::ptr(ptr), fmt::ptr(&foo));
    fmt::print("bar = {}, Adresse bar = {}\n", fmt::ptr(ptr), fmt::ptr(&bar));
    fmt::print("foo = {} \n", foo);

/// Teil 2: Dynamische Speicherverwaltung

    double* dptr = new double(3.1415);

    fmt::print("Wert = {}, Adresse dptr = {}\n", *dptr, fmt::ptr(dptr));

    delete dptr;
    fmt::print("Wert_löschen = {}, Adresse dptr = {}\n", *dptr, fmt::ptr(dptr));
    ///dptr = nullptr;

    /// Aufruf Teil3:
    int y = 5;

    fmt::print("value: {}\n", y);

    changeValueByParameter(y);
    fmt::print("value1: {}\n", y);
    fmt::print(" value ptr_befor: {}\n", &y);

    changeValueByPointer(&y);
    fmt::print("value ptr_after: {}\n", &y);


    /* INSERT YOUR CODE HERE */

    return 0; /* exit gracefully*/
}


