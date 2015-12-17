/*
 *  Author: Dylan McKee (140357185)
 *  Date: 10/12/15
 *  Purpose: The implementation of the library functions for the system calls implemented in do_syscalls.c for CSC2025.
 */
 #include <lib.h>      // provides _syscall and message
 #include <unistd.h>   // provides library function prototypes

// Implementation of library function for 3.1 Printing child pids (printchildpids)
int printchildpids(pid_t pid) {
    message m;      // Minix message to pass parameters to a system call

    m.m1_i1 = pid;  // set message integer to the pid we've been passed

    return _syscall(PM_PROC_NR, PRINTCHILDPIDS, &m);  // invoke system call

}

// Implementation of library function for 3.2 Counting children (getnchildren)
int getnchildren(pid_t pid) {
    message m;      // Minix message to pass parameters to a system call

    m.m1_i1 = pid;  // set message integer to the pid we've been passed

    return _syscall(PM_PROC_NR, GETNCHILDREN, &m);  // invoke system call

}

// Implementation of library function for 3.3 Getting child pids (getchildpids)
int getchildpids(pid_t pid, int nchildren, pid_t *childpids) {
    message m;      // Minix message to pass parameters to a system call

    // Pass on the paramaters we've been passed
    m.m1_i1 = pid;
    m.m1_i2 = nchildren;

    // Pass the childpids array pointer...
    m.m1_p1 = childpids;

    return _syscall(PM_PROC_NR, GETCHILDPIDS, &m);  // invoke system call


}
