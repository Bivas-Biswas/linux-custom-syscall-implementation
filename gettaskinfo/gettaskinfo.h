// File: linux/gettaskinfo_syscall/gettaskinfo_syscall.h

#ifndef _LINUX_GETTASKINFO_SYSCALL_H
#define _LINUX_GETTASKINFO_SYSCALL_H

#include <linux/types.h>

asmlinkage long sys_gettaskinfo(pid_t pid, char __user *buffer);

#endif /* _LINUX_GETTASKINFO_SYSCALL_H */