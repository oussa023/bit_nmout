#include "incld/mini.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// Signal handler for the parent process
void parent_handler(int signum) {
    printf("Parent received signal %d\n", signum);
}

// Signal handler for the child process
void child_handler(int signum) {
    printf("Child received signal %d\n", signum);
}

int main() {
    pid_t child_pid;

    // Set the signal handler for the parent process
    signal(SIGUSR1, parent_handler);

    // Fork a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        // This code runs in the child process

        // Set the signal handler for the child process
        signal(SIGUSR1, child_handler);

        // Child-specific code here
        printf("Child process is running.\n");

        // Simulate some work in the child process
        sleep(5);

        printf("Child process is exiting.\n");
        exit(EXIT_SUCCESS);
    } else {
        // This code runs in the parent process

        // Parent-specific code here
        printf("Parent process is running.\n");

        // Send a signal to the child process
        sleep(2);
        printf("Sending SIGUSR1 to the child process...\n");
        kill(child_pid, SIGUSR1);

        // Wait for the child process to exit
        int status;
        waitpid(child_pid, &status, 0);

        printf("Parent process is exiting.\n");
    }

    return 0;
}