/*
 *  Author: Dylan McKee (140357185)
 *  Date: 10/12/15
 *  Purpose: A test of my library functions for the CSC2025 assignment.
 */
#include <unistd.h>
#include <stdlib.h>

// Define constant test PID
#define TEST_PID 140

// Define out of bounds test PID
#define OUT_OF_BOUNDS_PID -1

// Test function prototypes
void testPrintChildPids();
void testGetNChildren();
void testGetChildPids();

int main(int argc, char **argv) {
    printf("Library function tests:\n");
    // Run the test functions
    testPrintChildPids();
    testGetNChildren();
    testGetChildPids();

}

void testPrintChildPids() {
    int status = printchildpids(TEST_PID);

    if (status == 0) {
        printf("printchildpids success\n");
    } else {
        printf("printchildpids failed\n");
        // Print error number/description
         perror("printchildpids error");
    }

    // now test process number bounds checking...
    status = printchildpids(OUT_OF_BOUNDS_PID);

    if (status == -1) {
        printf("printchildpids bounds test passed\n");
    } else {
        printf("printchildpids bounds test failed\n");
    }

}

void testGetNChildren() {
    int childrenForProcess = getnchildren(TEST_PID);

    if (childrenForProcess >= 0) {
        printf("getnchildren success\n");
    } else {
        printf("getnchildren failed\n");
        // Print error number/description
        perror("getnchildren error");

    }

    // now test process number bounds checking...
    int status = getnchildren(OUT_OF_BOUNDS_PID);

    if (status == -1) {
        printf("getnchildren bounds test passed\n");
    } else {
        printf("getnchildren bounds test failed\n");
    }


}

void testGetChildPids() {
    // Define a limit
    const int limit = 50;

    // Create an array of PIDs to fill
    pid_t pidArray[limit] = { 0 };

    // Test...
    int numberOfChildren = getchildpids(TEST_PID, limit, pidArray);

    if (numberOfChildren >= 0) {
        printf("getchildpids success\n");
    } else {
        printf("getchildpids failed\n");
        // Print error number/description
        perror("getchildpids error");

    }

    // now test process number bounds checking...
    int status = getnchildren(OUT_OF_BOUNDS_PID);

    if (status == -1) {
        printf("getchildpids bounds test passed\n");
    } else {
        printf("getchildpids bounds test failed\n");
    }


}
