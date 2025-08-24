#ifndef LIBGETTASKINFO_H
#define LIBGETTASKINFO_H

struct task_info {
    long int state;
    unsigned long long int start_time;
    int normal_prio;
};

struct task_info* gettaskinfo();
void free_task_info(struct task_info* info);

#endif // LIBGETTASKINFO_H
