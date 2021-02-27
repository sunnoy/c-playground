//
// Created by lirui on 2021/2/26.
//

#include <stdio.h>  //标准的输入输出函数
#include <stdlib.h> //standard library标准库函数头文件
#include <unistd.h> //对于类 Unix 系统，unistd.h 中所定义的接口通常都是大量针对系统调用的封装 fork、
#include <sys/types.h>

int main()
{

    printf("input create process num: \n");
    int process_num;

    scanf("%d",&process_num);

    pid_t pid;
    int i;
    for (i = 0; i < process_num; ++i)
    {
        pid=fork();
        // 这是异常情况
        if (pid==-1)
        {
            perror("fork失败!");
            exit(1);
        }

        //循环中，fork函数调用五次，子进程返回0,父进程返回子进程的pid，
        //为了避免子进程也fork，需要判断并break
        if (pid==0)
        {
            break;
        }
    }

    //返回大于0的进程就是父进程
    if(pid>0)  //父进程
    {
        printf("父进程: pid= %d , 父进程所在的ppid=%d,子进程: %d \n", getpid(),getppid(),pid);
        sleep(100); //这里延迟父进程程序，等子进程先执行完。
    }
    else if(pid==0)  //子进程
    {
        printf("i的变量是: %d 子进程: pid= %d , ppid=%d \n", i,getpid(),getppid());
    }

    return 0; //养成好习惯，返回程序执行状态码
}