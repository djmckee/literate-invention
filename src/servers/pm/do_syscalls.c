/*
 *  Author: Dylan McKee (140357185)
 *  Date: 10/12/15
 *  Purpose: The implementation of various Minix system calls for CSC2025
 */

#include <stdio.h>  // standard library
#include "pm.h"     // access to global variables

// Implementation of 3.1 Printing child pids (printchildpids)
int do_printchildpids() {
    // Get the input of process id from the message (m_in is a global message struct variable, get first param. from it)
    int pidToList = m_in.m1_i1;

    // Print pid and info message to console
    printf("Searching for children of process: %d\n", pidToList);


    return 0;
}

int do_getnchildren(void) {
    return 0;
}

int do_getchildpids(void) {
    return 0;
}
