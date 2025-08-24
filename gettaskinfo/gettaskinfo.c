#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/uaccess.h>
#include <linux/gettaskinfo.h>

#define BUFFER_SIZE 256

SYSCALL_DEFINE2(gettaskinfo, pid_t, pid, char __user *, buffer)
{
    struct task_struct *task;
    char kernel_buffer[BUFFER_SIZE];
    int len;

    printk(KERN_INFO "I am in gettaskinfo.\n");

    rcu_read_lock();
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (!task)
    {
        rcu_read_unlock();
        return -ESRCH;
    }

    len = snprintf(kernel_buffer, sizeof(kernel_buffer),
                   "%ld-%llu-%d",
                   task->state, task->start_time, task->normal_prio);

    rcu_read_unlock();

    if (len >= BUFFER_SIZE)
    {
        printk(KERN_WARNING "gettaskinfo: Buffer overflow prevented.\n");
        return -EOVERFLOW;
    }

    if (copy_to_user(buffer, kernel_buffer, len + 1))
        return -EFAULT;

   printk(KERN_INFO "I am out of gettaskinfo.\n");

    return len;
}