/*
 *  Author: Dylan McKee (140357185)
 *  Date: 10/12/15
 *  Purpose: A test of my system call functions for the CSC2025 assignment.
 */
#include <unistd.h>
#include <stdlib.h>
#include <lib.h>

// Define constant test PID
#define TEST_PID 140

// Test function prototypes
void testPrintChildPids();
void testGetNChildren();
void testGetChildPids();

int main(int argc, char **argv) {
    printf("System call tests:\n");
    // Run the test functions
    testPrintChildPids();
    testGetNChildren();
    testGetChildPids();

}

void testPrintChildPids() {
    message m;
    m.m1_i1 = TEST_PID;

    int result = _syscall(PM_PROC_NR, PRINTCHILDPIDS, &m);

    if (result == 0) {
        printf("PRINTCHILDPIDS system call success\n");
    } else {
        printf("PRINTCHILDPIDS system call failed\n");
    }

}

void testGetNChildren() {
    message m;
    m.m1_i1 = TEST_PID;

    int result = _syscall(PM_PROC_NR, GETNCHILDREN, &m);


    if (result == 0) {
        printf("GETNCHILDREN system call success\n");
    } else {
        printf("GETNCHILDREN system call failed\n");
    }

}

void testGetChildPids() {
    // Define a limit
    const int limit = 50;

    message m;
    m.m1_i1 = TEST_PID;
    m.m1_i2 = limit;

    // Pass the childpids array pointer...
    m.m1_p1 = childpids;

    int result = _syscall(PM_PROC_NR, GETCHILDPIDS, &m);

    if (result == 0) {
        printf("GETCHILDPIDS system call success\n");
    } else {
        printf("GETCHILDPIDS system call failed\n");
    }

}
