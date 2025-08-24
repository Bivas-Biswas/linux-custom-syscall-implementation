#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For pid_t
#include "lib_gettaskinfo.h"

void print_process_info(pid_t pid) {
    struct task_info* info = gettaskinfo(pid);
    if (info == NULL) {
        perror("gettaskinfo failed");
        return;
    }

    printf("Process info for PID %d:\n", pid);
    printf("State: %ld\n", info->state);
    printf("Start time: %llu\n", info->start_time);
    printf("Normal priority: %d\n", info->normal_prio);

    free_task_info(info);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t target_pid = (pid_t)atoi(argv[1]);

    if (target_pid <= 0) {
        fprintf(stderr, "Invalid PID: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    print_process_info(target_pid);

    return 0;
}
