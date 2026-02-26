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

    cout << "Parent frame local var address: " << hex << (uintptr_t)parentAddr << endl;
    cout << "Address of parameter parentAddr: " << hex << (uintptr_t)&parentAddr << endl;
    cout << "Address of childVar: " << hex << (uintptr_t)&childVar << endl;

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

    cout << "--- TEXT SEGMENT (Code) ---" << endl;
    cout << "Address of main():       " << hex << (uintptr_t)&main << endl;
    cout << "Address of checkStack(): " << hex << (uintptr_t)&checkStack << endl;
    cout << endl;

    cout << "--- DATA SEGMENT (Initialized Globals) ---" << endl;
    cout << "&g_init1 = " << hex << (uintptr_t)&g_init1 << endl;
    cout << "&g_init2 = " << hex << (uintptr_t)&g_init2 << endl;
    cout << endl;

    cout << "--- BSS SEGMENT (Uninitialized Globals) ---" << endl;
    cout << "&g_uninit1 = " << hex << (uintptr_t)&g_uninit1 << endl;
    cout << "&g_uninit2 = " << hex << (uintptr_t)&g_uninit2 << endl;
    cout << endl;

    checkStack(&localVar);

    cout << "--- HEAP SEGMENT (Dynamic Allocation) ---" << endl;
    cout << "heap1 = " << hex << (uintptr_t)heap1 << endl;
    cout << "heap2 = " << hex << (uintptr_t)heap2 << endl;

    if ((uintptr_t)heap1 < (uintptr_t)heap2)
        cout << "Heap grows: UP" << endl;
    else
        cout << "Heap grows: DOWN" << endl;

    cout << endl;

    cout << "=== RELATIVE POSITION SUMMARY ===" << endl;
    cout << "TEXT  near: " << hex << (uintptr_t)&main << endl;
    cout << "DATA  near: " << hex << (uintptr_t)&g_init1 << endl;
    cout << "BSS   near: " << hex << (uintptr_t)&g_uninit1 << endl;
    cout << "HEAP  near: " << hex << (uintptr_t)heap1 << endl;
    cout << "STACK near: " << hex << (uintptr_t)&localVar << endl;

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
