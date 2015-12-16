/*
*  Author: Dylan McKee (140357185)
*  Date: 10/12/15
*  Purpose: The implementation of various Minix system calls for CSC2025
*/

#include <stdio.h>  // standard library
#include "pm.h"     // access to global variables
#include "mproc.h"  // mproc struct access

// Implementation of 3.1 Printing child pids (printchildpids)
int do_printchildpids() {
    // Get the input of process id from the message (m_in is a global message struct variable, get first param. from it)
    int pidToList = m_in.m1_i1;

    int processCount = NR_PROCS;
    // Process ID must be between 1 and the maximum, perform some bounds checking...
    if (pidToList < 1 || pidToList >= processCount) {
        // pid is not valid! Return with error code -1....
        return -1;
    }

    // Print pid and info message to console
    printf("Searching for children of process: %d\n", pidToList);

    // Iterate the mproc array...
    for (int i = 0; i < processCount; i++) {
        // Get current process
        struct mproc *currentProcess = &mproc[i];
        // Ensure there's an actual struct there...
        if (currentProcess != NULL) {
            // Go ahead and read process ID
            pid_t processId = currentProcess->mp_pid;

            // Check process isn't just blank (i.e. the ID must be greater than 0)...
            if (processId > 0) {
                // It's an actual process... get parent
                int parentProcessIndex = currentProcess->mp_parent;

                // Get parent from mproc array, at index specified in current process
                struct mproc *parentProcess = &mproc[parentProcessIndex];

                // Get parent process ID...
                pid_t parentProcessId = parentProcess->mp_pid;

                // Check if parent process ID matches the one we're looking for...
                if (parentProcessId == pidToList) {
                    // It's a child of the process we want to list the children of!
                    // List the process ID!
                    printf("%d\n", processId);
                }
            }
        }
    }


    return 0;
}

// Implementation of 3.2 Counting children (getnchildren)
int do_getnchildren() {
    return 0;
}

// Implementation of 3.3 Getting child pids (getchildpids)
int do_getchildpids() {
    return 0;
}
