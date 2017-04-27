/*
** syscalls.h for strace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
**
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Mon Apr 10 18:48:38 2017 MonsieurTom
** Last update Sun Apr 16 15:05:11 2017 Alexis Lavenu
*/

#ifndef SYSCALLS_H_
# define SYSCALLS_H_

# include "strace.h"

static t_syscall	g_syscalls[] =
  {
    {0, "read", 3, "ssize_t", "int", "void *", "size_t", NULL, NULL, NULL},
    {1, "write", 3, "ssize_t", "int", "const void *", "size_t", NULL, NULL,
     NULL},
    {2, "open", 2, "int", "const char *", "int", NULL, NULL, NULL, NULL},
    {3, "close", 1, "int", "int", NULL, NULL, NULL, NULL, NULL},
    {4, "stat", 2, "int", "const char *", "struct *", NULL, NULL, NULL, NULL},
    {5, "fstat", 2, "int", "int", "struct stat *" , NULL, NULL, NULL, NULL},
    {6, "lstat", 2, "int", "const char *", "struct stat *", NULL, NULL, NULL,
     NULL},
    {7, "poll", 3, "int", "pollfd *", "nsdf_t", "int", NULL, NULL, NULL},
    {8, "lseek", 3, "off_t", "int", "off_t", "int", NULL, NULL, NULL},
    {9, "mmap", 6, "void *", "void *", "size_t", "int", "int", "int", "off_t"},
    {10, "mprotect", 3, "int", "void *", "size_t", "int", NULL, NULL, NULL},
    {11, "munmap", 2, "int", "void *", "size_t", NULL, NULL, NULL, NULL},
    {12, "brk", 1, "int", "void *", NULL, NULL, NULL, NULL, NULL},
    {13, "rt_sigaction", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {14, "rt_sigprocmask", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {15, "rt_sigreturn", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {16, "ioctl", 3, "int", "int", "unsigned long", "...", NULL, NULL, NULL},
    {17, "pread64", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {18, "pwrite64", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {19, "readv", 3, "size_t", "int", "const struct iovec *", "int", NULL,
     NULL, NULL},
    {20, "writev", 3, "size_t", "int", "const struct iovec *", "int", NULL,
     NULL, NULL},
    {21, "access", 2, "int", "const char *", "int", NULL, NULL, NULL, NULL},
    {22, "pipe", 1, "int", "int", NULL, NULL, NULL, NULL, NULL },
    {23, "select", 5, "int", "int", "fd_set *", "fd_set *", "fd_set *",
     "struct timeval *", NULL },
    {24, "sched_yield", 0, "int", NULL, NULL, NULL, NULL, NULL, NULL},
    {25, "mremap", 0, "void *", NULL, NULL, NULL, NULL, NULL, NULL},
    {26, "msync", 3, "int", "void *", "size_t", "int", NULL, NULL, NULL},
    {27, "mincore", 3, "int", "void *", "size_t", "unsigned char *", NULL, NULL,
     NULL},
    {28, "madvise", 3, "int", "void *", "size_t", "int", NULL, NULL, NULL},
    {29, "shmget", 3, "int", "key_t", "size_t", "int", NULL, NULL, NULL},
    {30, "shmat", 3, "void *", "int", "const void *", "int", NULL, NULL, NULL},
    {31, "shmctl", 3, "int", "int", "int", "struct shmid_ds *", NULL, NULL,
     NULL},
    {32, "dup", 1, "int", "int", NULL, NULL, NULL, NULL, NULL},
    {33, "dup2", 2, "int", "int", "int", NULL, NULL, NULL, NULL},
    {34, "pause", 0, "int", NULL, NULL, NULL, NULL, NULL, NULL},
    {35, "nanosleep", 2, "int", "const struct timespec *", "struct timespec *",
     NULL, NULL, NULL, NULL},
    {36, "getitimer", 2, "int", "int", "struct itimerval *", NULL, NULL, NULL,
     NULL},
    {37, "alarm", 1, " unsigned int", " unsigned int", NULL, NULL, NULL, NULL,
     NULL},
    {38, "setitimer", 3, "int", "int", "const struct itimerval *",
     "struct itimerval *", NULL, NULL, NULL},
    {39, "getpid", 0, "pid_t", NULL, NULL, NULL, NULL, NULL, NULL},
    {40, "sendfile", 4, "ssize_t", "int", "int", "off_t *", "size_t", NULL,
     NULL},
    {41, "socket", 3, "int", "int", "int", "int", NULL, NULL, NULL},
    {42, "connect", 3, "int", "int", "const struct sockaddr *", "sicklen_t",
     NULL, NULL, NULL},
    {43, "accept", 3, "int", "int", "struct sockaddr *", "socklen_t *", NULL,
     NULL, NULL},
    {44, "sendto", 6, "ssize_t", "int", "const void *", "size_t", "int",
     "const struct sockaddr *", "socklen_y"},
    {45, "recvfrom", 6, "ssize_t", "int", "void *", "size_t", "int",
     "struct sockaddr *", "socketlen_t *"},
    {46, "sendmsg", 3, "ssize_t", "int", "const struct msghd *", "int", NULL,
     NULL, NULL},
    {47, "recvmsg", 3, "ssize_t", "int", "struct msghdr *", "int", NULL,
     NULL, NULL},
    {48, "shutdown", 2, "int", "int", "int", NULL, NULL, NULL, NULL},
    {49, "bind", 3, "int", "int", "const struct sockaddr *", "socklen_t",
     NULL, NULL, NULL},
    {50, "listen", 2, "int", "int", "int", NULL, NULL, NULL, NULL},
    {51, "getsockname", 3, "int", "int", "struct sockaddr *", "socklen_t *",
     NULL, NULL, NULL},
    {52, "getpeername", 3, "int", "int", "struct sockaddr *", "socklen_t *",
     NULL, NULL, NULL},
    {53, "socketpair", 4, "int", "int", "int", "int", "int", NULL, NULL},
    {54, "setsockopt", 5, "int", "int", "int", "int", "const void *",
     "socklen_t", NULL },
    {55, "getsockopt", 5, "int", "int", "int", "int", "void *",
     "socketlen_t *", NULL},
    {56, "clone", 0, "int", NULL, NULL, NULL, NULL, NULL, NULL},
    {57, "fork", 0, "pid_t", NULL, NULL, NULL, NULL, NULL, NULL},
    {58, "vfork", 1, "pid_t", NULL, NULL, NULL, NULL, NULL, NULL},
    {59, "execve", 3, "int", "const char *", "char **", "char **", NULL, NULL,
     NULL},
    {60, "exit", 1, "?", "int", NULL, NULL, NULL, NULL, NULL},
    {61, "wait4", 4, "pid_t", "pid_t", "int *", "int", "struct rusage *", NULL,
     NULL},
    {62, "kill", 2, "int", "pid_t", "int", NULL, NULL, NULL, NULL},
    {63, "uname", 1, "int", "struct utsname *", NULL, NULL, NULL, NULL, NULL},
    {64, "semget", 3, "int", "key_t", "int", "int", NULL, NULL, NULL},
    {65, "semop", 3, "int", "int", "struct sembuf *", "size_t", NULL, NULL,
     NULL},
    {66, "semctl", 4, "int", "int", "int", "int", "...", NULL, NULL},
    {67, "shmdt", 1, "int", "const void *", NULL, NULL, NULL, NULL, NULL},
    {68, "msgget", 2, "int", "key_t", "int", NULL, NULL, NULL, NULL},
    {69, "msgsnd", 4, "int", "int", "const void *", "size_t", "int", NULL,
     NULL},
    {70, "msgrcv", 5, "ssize_t", "int", "void *", "size_t", "long", "int",
     NULL},
    {71, "msgctl", 3, "int", "int", "int", "struct msqid_ds *", NULL, NULL,
     NULL},
    {72, "fcntl", 2, "int", "int", "int", NULL, NULL, NULL, NULL},
    {73, "flock", 2, "int", "int", "int", NULL, NULL, NULL, NULL},
    {74, "fsync", 1, "int", "int", NULL, NULL, NULL, NULL, NULL},
    {75, "fdatasync", 1, "int", "int", NULL, NULL, NULL, NULL, NULL},
    {76, "truncate", 2, "int", "const char *", "off_t", NULL, NULL, NULL, NULL},
    {77, "ftruncate", 2, "int", "int", "off_t", NULL, NULL, NULL, NULL},
    {78, "getdents", 3, "int", "unsigned int", "struct linux_dirent *",
     "unsigned int", NULL, NULL, NULL},
    {79, "getcwd", 2, "char *", "char *", "size_t", NULL, NULL, NULL, NULL},
    {80, "chdir", 1, "int", "const char *", NULL, NULL, NULL, NULL, NULL},
    {81, "fchdir", 1, "int", "int", NULL, NULL, NULL, NULL, NULL},
    {82, "rename", 2, "int", "const char *", "const char *", NULL, NULL, NULL,
     NULL},
    {83, "mkdir", 2, "int", "const char *", "mode_t", NULL, NULL, NULL, NULL},
    {84, "rmdir", 1, "int", "const char *", NULL, NULL, NULL, NULL, NULL},
    {85, "creat", 2, "int", "const char *", "mode_t", NULL, NULL, NULL, NULL},
    {86, "link", 2, "int", "const char *", "const char *", NULL, NULL, NULL,
     NULL},
    {87, "unlink", 1, "int", "const char *", NULL, NULL, NULL, NULL, NULL},
    {88, "symlink", 2, "int", "const char *", "const char *", NULL, NULL, NULL,
     NULL},
    {89, "readlink", 3, "ssize_t", "const char *", "char *", "size_t", NULL,
     NULL, NULL},
    {90, "chmod", 2, "int", "const char *", "mode_t", NULL, NULL, NULL, NULL},
    {91, "fchmod", 2, "int", "int", "mode_t", NULL, NULL, NULL, NULL},
    {92, "chown", 3, "int", "const char *", "uid_t", "gid_t", NULL, NULL, NULL},
    {93, "fchown", 3, "int", "int", "uid_t", "gid_t", NULL, NULL, NULL},
    {94, "lchown", 3, "int", "const char *", "uid_t", "gid_t", NULL, NULL,
     NULL},
    {95, "umask", 1, "mode_t", "mode_t", NULL, NULL, NULL, NULL, NULL},
    {96, "gettimeofday", 2, "int", "struct timeval *", "struct timezone *",
     NULL, NULL, NULL, NULL},
    {97, "getrlimit", 2, "int", "int", "struct rlimit *", NULL, NULL, NULL,
     NULL},
    {98, "getrusage", 2, "int", "int", "struct rusage *", NULL, NULL, NULL,
     NULL},
    {99, "sysinfo", 1, "int", "struct sysinfo *", NULL, NULL, NULL, NULL, NULL},
    {100, "times", 1, "clock_t", "struct tms *", NULL, NULL, NULL, NULL, NULL},
    {101, "ptrace", 4, "long", "enum __ptrace_request", "pid_t", "void *",
     "void *", NULL, NULL},
    {102, "getuid", 0, "uid_t", NULL, NULL, NULL, NULL, NULL, NULL},
    {103, "syslog", 3, "int", "int", "char *", "int", NULL, NULL, NULL},
    {104, "getgid", 0, "gid_t", NULL, NULL, NULL, NULL, NULL, NULL},
    {105, "setuid", 1, "int", "uid_t", NULL, NULL, NULL, NULL, NULL},
    {106, "setgid", 1, "int", "gid_t", NULL, NULL, NULL, NULL, NULL},
    {107, "geteuid", 0, "uid_t", NULL, NULL, NULL, NULL, NULL, NULL},
    {108, "getegid", 0, "gid_t", NULL, NULL, NULL, NULL, NULL, NULL},
    {109, "setpgid", 2, "int", "pid_t", "pid_t", NULL, NULL, NULL, NULL},
    {110, "getppid", 0, "pid_t", NULL, NULL, NULL, NULL, NULL, NULL},
    {111, "getpgrp", 1, "pid_t", NULL, NULL, NULL, NULL, NULL, NULL},
    {112, "setsid", 0, "pid_t", NULL, NULL, NULL, NULL, NULL, NULL},
    {113, "setreuid", 2, "int", "uid_t", "uid_t", NULL, NULL, NULL, NULL},
    {114, "setregid", 2, "int", "gid_t", "gid_t", NULL, NULL, NULL, NULL},
    {115, "getgroups", 2, "int", "int", "gid_t", NULL, NULL, NULL, NULL},
    {116, "setgroups", 2, "int", "size_t", "const gid_t *", NULL, NULL, NULL,
     NULL},
    {117, "setresuid", 3, "int", "uid_t", "uid_t", "uid_t", NULL, NULL, NULL},
    {118, "getresuid", 3, "int", "uid_t *", "uid_t *", "uid_t *", NULL, NULL,
     NULL},
    {119, "setresgid", 3, "int", "gid_t", "gid_t", "gid_t", NULL, NULL, NULL},
    {120, "getresgid", 3, "int", "gid_t *", "gid_t *", "gid_t *", NULL, NULL,
     NULL},
    {121, "getpgid", 1, "pid_t", "pid_t", NULL, NULL, NULL, NULL, NULL},
    {122, "setfsuid", 1, "int", "uid_t", NULL, NULL, NULL, NULL, NULL},
    {123, "setfsgid", 1, "int", "uid_t", NULL, NULL, NULL, NULL, NULL},
    {124, "getsid", 1, "pid_t", "pid_t", NULL, NULL, NULL, NULL, NULL},
    {125, "capget", 2, "int", "cap_user_header_t", "cap_user_data_t", NULL,
     NULL, NULL, NULL},
    {126, "capset", 2, "int", "cap_user_header_t", "const cap_user_data",
     NULL, NULL, NULL, NULL},
    {127, "rt_sigpending", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {128, "rt_sigtimedwait", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {129, "rt_sigqueueinfo", 3, "int", "pid_t", "int", "siginfo_t *", NULL,
     NULL, NULL},
    {130, "rt_sigsuspend", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    {131, "sigaltstack", 2, "int", "const stack_t *", "stack_t *", NULL, NULL,
     NULL, NULL},
    {132, "utime", 2, "int", "const char *", "const struct utimbuf_p", NULL,
     NULL, NULL, NULL},
    {133, "mknod", 3, "int", "const char *", "mode_t", "dev_t", NULL, NULL,
     NULL},
    {134, "uselib", 1, "int", "const char *", NULL, NULL, NULL, NULL, NULL},
    {135, "personality", 1, "int", "unsigned long", NULL, NULL, NULL, NULL,
     NULL},
    {136, "ustat", 2, "int", "dev_t" , "struct ustat *", NULL, NULL, NULL,
     NULL},
    {137, "statfs", 2, "int", "const char *", "struct statfs *", NULL, NULL,
     NULL, NULL},
    {138, "fstatfs", 2, "int", "int", "struct statfs *", NULL, NULL, NULL,
     NULL},
    {139, "sysfs", 2, "int", "int", "const char *", NULL, NULL, NULL, NULL},
    {140, "getpriority", 2, "int", "int", "id_t", NULL, NULL, NULL, NULL},
    {141, "setpriority", 3, "int", "int", "id_t", "int", NULL, NULL, NULL},
    {142, "sched_setparam", 2, "int", "pid_t", "const struct sched_param *",
     NULL, NULL, NULL, NULL},
    {143, "sched_getparam", 2, "int", "pid_t", "struct sched_param *", NULL,
     NULL, NULL, NULL},
    {144, "sched_setscheduler", 3, "int", "pid_t", "int",
     "const struct sched_param *", NULL, NULL, NULL},
    {145, "sched_getscheduler", 1, "int", "pid_t", NULL, NULL, NULL, NULL,
     NULL},
    {146, "sched_get_priority_max", 1, "int", "int", NULL, NULL, NULL, NULL,
     NULL},
    {147, "sched_get_priority_min", 1, "int", "int", NULL, NULL, NULL, NULL,
     NULL},
    {148, "sched_rr_get_interval", 2, "int", "pid_t", "struct timespec *",
     NULL, NULL, NULL, NULL},
    {149, "mlock", 2, "int", "const void *", "size_t", NULL, NULL, NULL, NULL},
    {150, "munlock", 2, "int", "const void *", "size_t", NULL, NULL, NULL,
     NULL},
    {151, "mlockall", 1, "int", "int", NULL, NULL, NULL, NULL, NULL},
    {152, "munlockall", 0, "int", NULL, NULL, NULL, NULL, NULL, NULL},
    {153, "vhangup", 0, "int", NULL, NULL, NULL, NULL, NULL, NULL},
    {154, "modify_ldt", 3, "int", "int", "void *", "unsigned long", NULL, NULL,
     NULL},
    {155, "pivot_root", 2, "int", "const char *", "const char *", NULL, NULL,
     NULL, NULL},
    {156, "_sysctl", 1, "int", "struct ___sysctl_args *", NULL, NULL, NULL,
     NULL, NULL },
    {157, "prctl", 5, "int", "int", "unsigned long", "unsigned long",
     "unsigned long", "unsigned long", NULL},
    {158, "arch_prctl", 2, "int", "int", "unsigned long", NULL, NULL, NULL,
     NULL},
    {159, "adjtimex", 1, "int", "struct timex_p", NULL, NULL, NULL, NULL, NULL},
    {160, "setrlimit", 2, "int", "int", "cont struct rlimit_p", NULL, NULL,
     NULL, NULL},
    {161, "chroot", 1, "int", "const char *", NULL, NULL, NULL, NULL, NULL},
    {162, "sync", 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {163, "acct", 1, "int", "const char *", NULL, NULL, NULL, NULL, NULL},
    {164, "settimeofday", 2, "int", "const struct timeval *",
     "const struct timezone_p", NULL, NULL, NULL, NULL},
    {165, "mount", 5, "int", "const char *", "const char *", "const char *",
     "unsigned long", "const void *", NULL },
    {166, "umount2", 2, "int", "const char *", "int", NULL, NULL, NULL, NULL},
    {167, "swapon", 2, "int", "const char *", "int", NULL, NULL, NULL, NULL},
    {168, "swapoff", 1, "int", "const char *", NULL, NULL, NULL, NULL, NULL},
    {169, "reboot", 4, "int", "int", "int", "int", "void *", NULL, NULL},
    {170, "sethostname", 2, "int", "const char *", "size_t", NULL, NULL, NULL,
     NULL},
    {171, "setdomainname", 2, "int", "const char *", "size_t", NULL, NULL,
     NULL, NULL},
    {172, "iopl", 1, "int", "int", NULL, NULL, NULL, NULL, NULL},
    {173, "ioperm", 3, "int", "unsigned long", "unsigned long", "int", NULL,
     NULL, NULL},
    {174, "create_module", 2, "caddr_t", "const char *", "size_t", NULL, NULL,
     NULL, NULL},
    {175, "init_module", 3, "int", "void *", "unsigned long", "const char *",
     NULL, NULL, NULL},
    {176, "delete_module", 2, "int", "const char *", "int", NULL, NULL, NULL,
     NULL},
    {177, "get_kernel_syms", 1, "int", "struct kernel_sym_p", NULL, NULL, NULL,
     NULL, NULL},
    {178, "query_module", 5, "int", "const char *", "int", "void *", "size_t",
     "size_t *", NULL },
    {179, "quotactl", 4, "int", "int", "const char *", "int", "caddr_t", NULL,
     NULL},
    {180, "nfsservctl", 3, "long", "int", "struct nfsctl_arg *",
     "union nfsctl_res *", NULL, NULL, NULL},
    {181, "getpmsg", 5, "int", NULL, NULL, NULL, NULL, NULL, NULL },
    {182, "putpmsg", 5, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    {183, "afs_syscall", 5, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    {184, "tuxcall", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    {185, "security", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    {186, "gettid", 0, "pid_t", NULL, NULL, NULL, NULL, NULL, NULL},
    {187, "readahead", 3, "ssize_t", "int", "off64_t", "size_t", NULL, NULL,
     NULL},
    {188, "setxattr", 5, "int", "const char *", "const char *", "const void *",
     "size_t", "int", NULL},
    {189, "lsetxattr", 5, "int", "const char *", "const char *", "const void *",
     "size_t", "int", NULL },
    {190, "fsetxattr", 5, "int", "int", "const char *", "const void *",
     "size_t", "int", NULL},
    {191, "getxattr", 4, "ssize_t", "const char *", "const char *", "void *",
     "size_t", NULL, NULL},
    {192, "lgetxattr", 4, "ssize_t", "const char *", "const char *", "void *",
     "size_t", NULL, NULL},
    {193, "fgetxattr", 4, "ssize_t", "int", "const char *", "void *", "size_t",
     NULL, NULL},
    {194, "listxattr", 3, "ssize_t", "const char *", "char *", "size_t", NULL,
     NULL, NULL},
    {195, "llistxattr", 3, "ssize_t", "const char *", "char *", "size_t", NULL,
     NULL, NULL},
    {196, "flistxattr", 3, "ssize_t", "int", "char *", "size_t", NULL, NULL,
     NULL},
    {197, "removexattr", 2, "int", "const char *", "const char *", NULL, NULL,
     NULL, NULL},
    {198, "lremovexattr", 2, "int", "const char *", "const char *", NULL, NULL,
     NULL, NULL},
    {199, "fremovexattr", 2, "int", "int", "const char *", NULL, NULL, NULL,
     NULL},
    {200, "tkill", 2, "int", "int", "int", NULL, NULL, NULL, NULL},
    {201, "time", 1, "time_t", "time_t *", NULL, NULL, NULL, NULL, NULL},
    {202, "futex", 6, "int", "int *", "int", "int", "const struct timespec *",
     "int *", "int"},
    {203, "sched_setaffinity", 3, "int", "pid_t", "size_t", "const cpy_set_t *",
     NULL, NULL, NULL},
    {204, "sched_getaffinity", 3, "int", "pid_t", "size_t", "cpy_set_t *", NULL,
     NULL, NULL},
    {205, "set_thread_area", 1, "int", "struct user_desc_p", NULL, NULL, NULL,
     NULL, NULL},
    {206, "io_setup", 2, "int", "unsigned", "aio_context_t *", NULL, NULL,
     NULL, NULL},
    {207, "io_destroy", 1, "int", "aio_context_t", NULL, NULL, NULL, NULL,
     NULL},
    {208, "io_getevents", 5, "int", "aio_context_t", "long", "long",
     "struct io_event *",
     "struct timespec *", NULL},
    {209, "io_submit", 3, "int", "aio_context_t", "long", "struct iocb *",
     NULL, NULL, NULL},
    {210, "io_cancel", 3, "int", "aio_context_t", "struct iocb *",
     "struct io_event *", NULL, NULL, NULL},
    {211, "get_thread_area", 1, "int", "struct user_desc *", NULL, NULL, NULL,
     NULL, NULL},
    {212, "lookup_dcookie", 3, "int", "u64", "char *", "size_t", NULL, NULL,
     NULL},
    {213, "epoll_create", 1, "int", "int", NULL, NULL, NULL, NULL, NULL},
    {214, "epoll_ctl_old", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    {215, "epoll_wait_old", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    {216, "remap_file_pages", 5, "int", "void *", "size_t", "int", "size_t",
     "int", NULL},
    {217, "getdents64", 3, "int", "unsigned int", "struct linux_dirent64 *",
     "unsigned int", NULL, NULL, NULL},
    {218, "set_tid_address", 1, "long", "int *", NULL, NULL, NULL, NULL, NULL},
    {219, "restart_syscall", 0, "int", NULL, NULL, NULL, NULL, NULL, NULL},
    {220, "semtimedop", 4, "int", "int", "struct sembuf *", "size_t",
     "const struct timespec *",
     NULL, NULL },
    {221, "fadvise64", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    {222, "timer_create", 3, "int", "clockid_t", "struct sigevent *",
     "timer_t *", NULL, NULL, NULL},
    {223, "timer_settime", 4, "int", "timer_t", "int",
     "const struct itimerspec *", "struct itimerspec *", NULL, NULL},
    {224, "timer_gettime", 2, "int", "timer_t", "struct itimerspec *", NULL,
     NULL, NULL, NULL},
    {225, "timer_getoverrun", 1, "int", "timer_t", NULL, NULL, NULL, NULL,
     NULL},
    {226, "timer_delete", 1, "int", "timer_t", NULL, NULL, NULL, NULL, NULL},
    {227, "clock_settime", 2, "int", "clockid_t", "const struct timespec *",
     NULL, NULL, NULL, NULL},
    {228, "clock_gettime", 2, "int", "cockid_t", "struct timespec *", NULL,
     NULL, NULL, NULL},
    {229, "clock_getres", 2, "int", "clockid_t", "struct timespec *", NULL,
     NULL, NULL, NULL},
    {230, "clock_nanosleep", 4, "int", "clockid_t", "int",
     "const struct timespec *", "struct timespec *", NULL, NULL},
    {231, "exit_group", 1, NULL, "int", NULL, NULL, NULL, NULL, NULL},
    {232, "epoll_wait", 4, "int", "int", "struct epoll_event *", "int", "int",
     NULL, NULL},
    {233, "epoll_ctl", 4, "int", "int", "int", "int", "struct epoll_event *",
     NULL, NULL},
    {234, "tgkill", 3, "int", "int", "int", "int", NULL, NULL, NULL},
    {235, "utimes", 2, "int", "const char *", "const struct timeval", NULL,
     NULL, NULL, NULL},
    {236, "vserver", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {237, "mbind", 6, "long", "void *", "unsigned long", "int",
     "const unsigned long *",
     "unsigned long", "unsigned"},
    {238, "set_mempolicy", 3, "long", "int", "const unsigned long *",
     "unsigned long", NULL,
     NULL, NULL},
    {239, "get_mempolicy", 5, "int", "int *", "unsigned long *",
     "unsigned long", "unsigned long",
     "unsigned long", NULL},
    {240, "mq_open", 2, "mqd_t", "const char *", "int", NULL, NULL, NULL, NULL},
    {241, "mq_unlink", 1, "int", "const char *", NULL, NULL, NULL, NULL, NULL},
    {242, "mq_timedsend", 5, "int", "mqd_t", "const char *", "size_t",
     "unsigned int",
     "const struct timespec *", NULL},
    {243, "mq_timedreceive", 5, "ssize_t", "mqd_t", "char *", "size_t",
     "unsigned int *",
     "const struct timespec *", NULL},
    {244, "mq_notify", 2, "int", "mqd_t", "const struct sigevent *", NULL,
     NULL, NULL, NULL},
    {245, "mq_getsetattr", 3, "int", "mqd_t", "struct mq_attr *",
     "struct mq_attr *", NULL, NULL, NULL},
    {246, "kexec_load", 4, "long", "unsigned long", "unsigned long",
     "struct kexec_segment *", "unsigned long", NULL, NULL},
    {247, "waitid", 4, "int", "idtype_t", "id_t", "siginfo_t *", "int",
     NULL, NULL},
    {248, "add_key", 5, "key_serial_t", "const char *", "const char *",
     "const void *",
     "size_t", "key_serial_t", NULL},
    {249, "request_key", 4, "key_serial_t", "const char *", "const char *",
     "const char *", "key_serial_t", NULL, NULL},
    {250, "keyctl", 2, "long", "int", "...", NULL, NULL, NULL, NULL},
    {251, "ioprio_set", 3, "int", "int", "int", "int", NULL, NULL, NULL},
    {252, "ioprio_get", 2, "int", "int", "int", NULL, NULL, NULL, NULL},
    {253, "inotify_init", 0, "int", NULL, NULL, NULL, NULL, NULL, NULL},
    {254, "inotify_add_watch", 3, "int", "int", "const char *", "uint32_t",
     NULL, NULL, NULL},
    {255, "inotify_rm_watch", 2, "int", "int", "int", NULL, NULL, NULL, NULL},
    {256, "migrate_pages", 4, "long", "int", "unsigned long",
     "const unsigned long *",
     "const unsigned long *", NULL, NULL},
    {257, "openat", 3, "int", "int", "const char *", "int", NULL, NULL, NULL},
    {258, "mkdirat", 3, "int", "int", "const char *", "mode_t", NULL, NULL,
     NULL},
    {259, "mknodat", 4, "int", "int", "const char *", "mode_t", "dev_t", NULL,
     NULL},
    {260, "fchownat", 5, "int", "int", "const char *", "uid_t", "gid_t", "int",
     NULL },
    {261, "futimesat", 3, "int", "int", "const char *", "const struct timeval",
     NULL, NULL, NULL},
    {262, "newfstatat", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {263, "unlinkat", 3, "int", "int", "const char *", "int", NULL, NULL, NULL},
    {264, "renameat", 4, "int", "int", "const char *", "int", "const char *",
     NULL, NULL},
    {265, "linkat", 5, "int", "int", "const char *", "int", "const char *",
     "int", NULL},
    {266, "symlinkat", 3, "int", "const char *", "int", "const char *", NULL,
     NULL, NULL},
    {267, "readlinkat", 4, "ssize_t", "int", "const char *", "char *", "size_t",
     NULL, NULL},
    {268, "fchmodat", 4, "int", "int", "const char *", "mode_t", "int", NULL,
     NULL},
    {269, "faccessat", 4, "int", "int", "const char *", "int", "int", NULL,
     NULL},
    {270, "pselect6", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {271, "ppoll", 4, "int", "struct pollfd *", "nfds_t",
     "const struct timespec *", "const sigset_t *", NULL, NULL},
    {272, "unshare", 1, "int", "int", NULL, NULL, NULL, NULL, NULL},
    {273, "set_robust_list", 2, "long", "struct robust_list_head *",
     "size_t", NULL, NULL, NULL, NULL},
    {274, "get_robust_list", 3, "long", "int", "struct robust_list_head *",
     "size_t *", NULL, NULL, NULL },
    {275, "splice", 6, "ssize_t", "int", "loff_t *", "int", "loff_t *",
     "size_t", "unsigned int"},
    {276, "tee", 4, "ssize_t", "int", "int", "size_t", "unsigned int", NULL,
     NULL},
    {277, "sync_file_range", 4, "int", "int", "off64_t", "off64_t",
     "unsigned int", NULL, NULL},
    {278, "vmsplice", 4, "ssize_t", "int", "const struct iovec *",
     "unsigned long", "unsigned int", NULL, NULL},
    {279, "move_pages", 6, "long", "int", "unsigned long",
     "void *", "const int *", "int *", "int" },
    {280, "utimensat", 4, "int", "int", "const char *", "const struct timespec",
     "int", NULL, NULL},
    {281, "epoll_pwait", 5, "int", "int", "struct epoll_event *", "int", "int",
     "const sigset_t *", NULL},
    {282, "signalfd", 3, "int", "int", "const sigset_t *", "int", NULL,
     NULL, NULL},
    {283, "timerfd_create", 2, "int", "int", "int", NULL, NULL, NULL, NULL},
    {284, "eventfd", 2, "int", "unsigned int", "int", NULL, NULL, NULL, NULL},
    {285, "fallocate", 4, "int", "int", "int", "off_t", "off_t", NULL, NULL},
    {286, "timerfd_settime", 4, "int", "int", "int",
     "const struct itimerspec *", "struct itimerspec *", NULL, NULL},
    {287, "timerfd_gettime", 2, "int", "int", "struct itimerspec *",
     NULL, NULL, NULL, NULL},
    {288, "accept4", 4, "int", "int", "struct sockaddr *", "socketlen_t *",
     "int", NULL, NULL},
    {289, "signalfd4", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {290, "eventfd2", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {291, "epoll_create1", 1, "int", "int", NULL, NULL, NULL, NULL, NULL},
    {292, "dup3", 3, "int", "int", "int", "int", NULL, NULL, NULL},
    {293, "pipe2", 2, "int", "int", "int", NULL, NULL, NULL, NULL},
    {294, "inotify_init1", 1, "int", "int", NULL, NULL, NULL, NULL, NULL},
    {295, "preadv", 4, "ssize_t", "int", "const struct iovec *",
     "int", "off_t", NULL, NULL},
    {296, "pwritev", 4, "ssize_t", "int", "const struct iovec *", "int",
     "off_t", NULL, NULL},
    {297, "rt_tgsigqueueinfo", 4, "int", "pid_t", "pid_t", "int", "siginfo_t *",
     NULL, NULL},
    {298, "perf_event_open", 5, "int", "struct perf_event_attre *",
     "pid_t", "int", "int", "unsigned long", NULL},
    {299, "recvmmsg", 5, "int", "int", "struct mmsghdr *", "unsigned int",
     "unsigned int", "struct timespec *", NULL},
    {300, "fanotify_init", 2, "int", "unsigned int", "unsigned int", NULL,
     NULL, NULL, NULL},
    {301, "fanotify_mark", 5, "int", "int", "unsigned int", "uint64_t", "int",
     "const char *", NULL},
    {302, "prlimit64", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    {303, "name_to_handle_at", 5, "int", "int", "const char *",
     "struct file_handle *", "int *", "int", NULL},
    {304, "open_by_handle_at", 3, "int", "int", "struct file_handle *",
     "int", NULL, NULL, NULL},
    {305, "clock_adjtime", 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {306, "syncfs", 1, "int", "int", NULL, NULL, NULL, NULL, NULL},
    {307, "sendmmsg", 4, "int", "int", "struct mmsghdr *", "unsigned int",
     "unsigned int", NULL, NULL},
    {308, "setns", 2, "int", "int", "int", NULL, NULL, NULL, NULL},
    {309, "getcpu", 3, "int", "unsigned *", "unsigned *",
     "struct __cache *", NULL, NULL, NULL},
    {310, "process_vm_readv", 6, "ssize_t", "pid_t", "const struct iovec *",
     "unsigned long", "const struct iovec *", "unsigned long", "unsigned long"},
    {311, "process_vm_writev", 6, "ssize_t", "pid_t", "const struct iovec *",
     "unsigned long", "const struct iovec *", "unsigned long", "unsigned long"},
    {312, "kcmp", 5, "int", "pid_t", "pid_t", "int", "unsigned long",
     "unsigned long", NULL },
    {313, "finit_module", 3, "int", "int", "const char *", "int", NULL,
     NULL, NULL }
  };

#endif /* !SYSCALLS_H_ */