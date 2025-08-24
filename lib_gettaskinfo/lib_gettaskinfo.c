
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib_gettaskinfo.h"

#define SYS_gettaskinfo 449
#define BUFFER_SIZE 256

struct task_info* gettaskinfo(pid_t pid) {
    char buffer[BUFFER_SIZE];
    struct task_info* info = malloc(sizeof(struct task_info));

    if (!info) {
        errno = ENOMEM;
        return NULL;
    }

    long result = syscall(SYS_gettaskinfo, pid, buffer);
    if (result < 0) {
        free(info);
        errno = -result;
        return NULL;
    }

    // printf("%s\n", buffer);

    if (sscanf(buffer, "%ld-%llu-%d", &info->state, &info->start_time, &info->normal_prio) != 3) {
        free(info);
        errno = EINVAL;
        return NULL;
    }

    return info;
}

void free_task_info(struct task_info* info) {
    free(info);
}
