/*
 *  Author: Dylan McKee (140357185)
 *  Date: 10/12/15
 *  Purpose: A test of my library functions for the CSC2025 assignment.
 */
#include <unistd.h>
#include <stdlib.h>

// Define constant test PID
#define TEST_PID 140

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
        printf("testPrintChildPids success\n");
    } else {
        printf("testPrintChildPids failed\n");
        // Print error number/description
         perror("testPrintChildPids error");
    }

}

void testGetNChildren() {
    int childrenForProcess = getnchildren(TEST_PID);

    if (childrenForProcess >= 0) {
        printf("testGetNChildren success\n");
    } else {
        printf("testGetNChildren failed\n");
        // Print error number/description
        perror("testGetNChildren error");

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
        printf("testGetChildPids success\n");
    } else {
        printf("testGetChildPids failed\n");
        // Print error number/description
        perror("testGetChildPids error");

    }

}
