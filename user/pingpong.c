#include "kernel/types.h"
#include "user/user.h"

int main()
{
    int p1[2], p2[2];
    char buffer[] = {'X'};

    long length = sizeof(buffer);

    // pipe1(p1)：写端父进程，读端子进程
    // pipe2(p2)；写端子进程，读端父进程
    pipe(p1);
    pipe(p2);

    // 当进程调用fork()，会创建一个完全相同的子进程，拷贝父进程的代码段、数据段、堆、栈等
    // 但子进程还是独立进程，有自己的进程ID(PID)
    // 在父进程中，fork()返回子进程的进程ID；子进程中，fork()返回0；调用失败会返回-1

    // 如果是子进程，执行以下代码
    if (fork() == 0)
    {
        close(p1[1]);
        close(p2[0]);

        if (read(p1[0], buffer, length) != length)
        {
            printf("a--->b read error!");
            exit(1);
        }

        printf("%d: received ping\n", getpid());

        if (write(p2[1], buffer, length) != length)
        {
            printf("a<---b write error!");
            exit(1);
        }
        exit(0);
    }

    // 如果是父进程，执行以下代码
    close(p1[0]);
    close(p2[1]);

    if (write(p1[1], buffer, length) != length)
    {
        printf("a--->b write error!");
        exit(1);
    }

    if (read(p2[0], buffer, length) != length)
    {
        printf("a<---b read error!");
        exit(1);
    }
    printf("%d: received pong\n", getpid());

    wait(0);
    exit(0);
}