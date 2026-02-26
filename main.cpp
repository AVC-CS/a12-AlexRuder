#include <iostream>
#include <cstdlib>
#include <cstdint>
using namespace std;

// DATA segment
int g_init1 = 42;
int g_init2 = 99;

// BSS segment
int g_uninit1;
int g_uninit2;

void checkStack(int* parentAddr) {
    int childVar = 0;

    cout << "--- STACK SEGMENT (Cross-function comparison) ---" << endl;

    // Three stack addresses, in correct order
    cout << "parent=0x" << hex << (uintptr_t)parentAddr << endl;
    cout << "param=0x" << hex << (uintptr_t)&parentAddr << endl;
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

    cout << "--- TEXT SEGMENT (Code) --- "
         << "main=0x" << hex << (uintptr_t)&main
         << " checkStack=0x" << hex << (uintptr_t)&checkStack
         << endl << endl;

    cout << "--- DATA SEGMENT (Initialized Globals) --- "
         << "&g_init1=0x" << hex << (uintptr_t)&g_init1
         << " &g_init2=0x" << hex << (uintptr_t)&g_init2
         << endl << endl;

    cout << "--- BSS SEGMENT (Uninitialized Globals) --- "
         << "&g_uninit1=0x" << hex << (uintptr_t)&g_uninit1
         << " &g_uninit2=0x" << hex << (uintptr_t)&g_uninit2
         << endl << endl;

    checkStack(&localVar);

    cout << "--- HEAP SEGMENT (Dynamic Allocation) --- "
         << "heap1=0x" << hex << (uintptr_t)heap1
         << " heap2=0x" << hex << (uintptr_t)heap2
         << endl;

    if ((uintptr_t)heap1 < (uintptr_t)heap2)
        cout << "Heap grows: UP" << endl;
    else
        cout << "Heap grows: DOWN" << endl;

    cout << endl;

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
