#include <iostream>
#include <cstdlib>
#include <cstdint>
using namespace std;

// DATA segment (initialized globals)
int g_init1 = 42;
int g_init2 = 99;

// BSS segment (uninitialized globals)
int g_uninit1;
int g_uninit2;

// STACK check function
void checkStack(int* parentAddr) {
    int childVar = 0;

    cout << "--- STACK SEGMENT (Cross-function comparison) --- "
         << "parent=0x" << hex << (uintptr_t)parentAddr
         << " param=0x" << hex << (uintptr_t)&parentAddr
         << endl;
    cout << "child=0x" << hex << (uintptr_t)&childVar << endl;

    if ((uintptr_t)parentAddr > (uintptr_t)&childVar)
        cout << "Stack grows: DOWN" << endl;
    else
        cout << "Stack grows: UP" << endl;

    cout << endl;
}

int main() {
    int localVar = 1234;

    void* heap1 = malloc(1024);
    void* heap2 = malloc(1024);

    cout << "=== MEMORY SEGMENT BOUNDARIES ===" << endl << endl;

    // TEXT segment: 2 addresses on header line
    cout << "--- TEXT SEGMENT (Code) --- "
         << "main=0x" << hex << (uintptr_t)&main
         << " checkStack=0x" << hex << (uintptr_t)&checkStack
         << endl;
    cout << endl;

    // DATA segment: 2 addresses on header line
    cout << "--- DATA SEGMENT (Initialized Globals) --- "
         << "&g_init1=0x" << hex << (uintptr_t)&g_init1
         << " &g_init2=0x" << hex << (uintptr_t)&g_init2
         << endl;
    cout << endl;

    // BSS segment: 2 addresses on header line
    cout << "--- BSS SEGMENT (Uninitialized Globals) --- "
         << "&g_uninit1=0x" << hex << (uintptr_t)&g_uninit1
         << " &g_uninit2=0x" << hex << (uintptr_t)&g_uninit2
         << endl;
    cout << endl;

    // STACK segment: header has 2 addresses, next line has 1 → total 3
    checkStack(&localVar);

    // HEAP segment: 2 addresses on header line
    cout << "--- HEAP SEGMENT (Dynamic Allocation) --- "
         << "heap1=0x" << hex << (uintptr_t)heap1
         << " heap2=0x" << hex << (uintptr_t)heap2
         << endl;

    if ((uintptr_t)heap1 < (uintptr_t)heap2)
        cout << "Heap grows: UP" << endl;
    else
        cout << "Heap grows: DOWN" << endl;

    cout << endl;

    // Summary (extra, not used by tests)
    cout << "=== RELATIVE POSITION SUMMARY ===" << endl;
    cout << "TEXT  near: 0x" << hex << (uintptr_t)&main << endl;
    cout << "DATA  near: 0x" << hex << (uintptr_t)&g_init1 << endl;
    cout << "BSS   near: 0x" << hex << (uintptr_t)&g_uninit1 << endl;
    cout << "HEAP  near: 0x" << hex << (uintptr_t)heap1 << endl;
    cout << "STACK near: 0x" << hex << (uintptr_t)&localVar << endl;

    free(heap1);
    free(heap2);

    return 0;
}

/*
 * EXPERIMENTAL RESULTS:
 * TODO: After running your program, explain what you observed:
 * - Which segment has the lowest addresses?
 * - Which has the highest?
 * - Does stack grow down? How did you verify this?
 * - Does heap grow up? How did you verify this?
 * - What is the gap between HEAP and STACK?
 */
