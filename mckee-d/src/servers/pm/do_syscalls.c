/*
 *  Author: Dylan McKee (140357185)
 *  Date: 10/12/15
 *  Purpose: The implementation of various Minix system calls for CSC2025
 */

#include <stdio.h>  // standard library
#include "pm.h"     // access to global variables
#include "mproc.h"  // mproc array access
#include "errno.h"  // error number acccess

// Implementation of 3.1 Printing child pids (printchildpids)
int do_printchildpids() {
    // Get the input of process id from the message (m_in is a global message struct variable, get first param. from it)
    int pidToList = m_in.m1_i1;

    int processCount = NR_PROCS;
    // Process ID must be between 1 and the maximum, perform some bounds checking...
    if (pidToList < 1 || pidToList >= processCount) {
        // pid is not valid! Return with error code -1....

        // Set error number to 'No such process'
        errno = ESRCH;

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
    // Get the input of process id from the message (m_in is a global message struct variable, get first param. from it)
    int pidToList = m_in.m1_i1;

    int processCount = NR_PROCS;
    // Process ID must be between 1 and the maximum, perform some bounds checking...
    if (pidToList < 1 || pidToList >= processCount) {
        // pid is not valid! Return with error code -1....

        // Set error number to 'No such process'
        errno = ESRCH;

        return -1;
    }

    // Create counter var
    int count = 0;

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
                    // It's a child of the process we want to count the children of!
                    // Increment count...
                    count++;

                }
            }
        }
    }

    // Print count to the console (just for debugging!)...
    //printf("Process with id %d has %d children.", pidToList, count);

    if (count == 0) {
        // No child processes found; set error number to 'No child processes'
        errno = ECHILD;

    }

    // Return the count...
    return count;

}

// Implementation of 3.3 Getting child pids (getchildpids)
int do_getchildpids() {
    // Get the input of process id from the message (m_in is a global message struct variable, get first param. from it)
    int pidToList = m_in.m1_i1;

    // Get the limit of child processes to find from the message
    int maximumProcessLimit = m_in.m1_i2;

    // Get the childpid's array pointer
    pid_t *childPids = m.m1_p1;

    int processCount = NR_PROCS;
    // Process ID must be between 1 and the maximum, perform some bounds checking...
    if (pidToList < 1 || pidToList >= processCount) {
        // pid is not valid! Return with error code -1....

        // Set error number to 'No such process'
        errno = ESRCH;

        return -1;
    }

    // Create a local array of process IDs; as large as the max. number of possible processes (just to be safe).
    pid_t matchingChildren[processCount];

    // Create counter var (which will also = array size)
    int count = 0;

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
                    // It's a child of the process we want to count the children of!

                    // Add PID to the array
                    matchingChildren[count] = processId;

                    // Increment count...
                    count++;

                    // If we've hit the limit of child processes that we're meant to find then give up...
                    if (count == maximumProcessLimit) {
                        // Break out of the loop - we've already found the desired maximum number of processes
                        break;
                    }

                }
            }
        }
    }

    // Print count to the console (just for debugging!)...
    //printf("Process with id %d has %d children.", pidToList, count);

    // Copy process ID array into the pointer we've been passed
    // Compute size of array to copy first...
    size_t childArraySize = (sizeof(pid_t) * count);

    // And run the copy between processes, as per the assignment instructions
    sys_vircopy(SELF, &matchingChildren, who_e, &childPids, childArraySize);
    
    if (count == 0) {
        // No child processes found; set error number to 'No child processes'
        errno = ECHILD;

    }

    // Return the count of child processes found...
    return count;

}
