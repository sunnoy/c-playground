//
// Created by lirui on 2021/2/24.
//

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_CONNECTION_NUM 50000

int buildConnect(const char *lIp, const char *sIp, int sPort)
{
    int skFd;
    // 初始化socket
    if((skFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket\n");
        return 0;
    }

    // 初始化 socket 数据结构
    struct sockaddr_in cliAddr;

    cliAddr.sin_family = AF_INET;
    cliAddr.sin_addr.s_addr = inet_addr(lIp);
    cliAddr.sin_port = 0;

    // 将socket和addr进行绑定
    if(bind(skFd,  (struct sockaddr *)&cliAddr, sizeof(cliAddr)) < 0)
    {
        printf("\n Error : Bind Failed \n");
    }

    // 初始化服务端addr
    struct sockaddr_in srvAddr;

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_addr.s_addr = inet_addr(sIp);
    srvAddr.sin_port = htons(sPort);

    // 连接服务端
    // int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

    if( connect(skFd, (struct sockaddr *)&srvAddr, sizeof(srvAddr)) < 0)
    {
        printf("\n connect error , \n");
        return 0;
    }

    return skFd;
}


int main(int argc, char *argv[])
{

    // 初始化相关变量
    int i = 0, sPort, fd;
    char lIp[16], sIp[16];

    if(argc != 4)
    {
        printf("\n Usage: %s <local ip> <server ip> <server port>\n", argv[0]);
        return 1;
    }


    //1. 从命令行获取并解析local ip、server ip以及端口
    strcpy(lIp, argv[1]);
    strcpy(sIp, argv[2]);
    sPort = atoi(argv[3]);

    //2. 开始建立连接
    // 分配内存
    int *sockets = (int *)malloc(sizeof(int) * MAX_CONNECTION_NUM);

    // 循环建立连接
    for(i = 1; i <= MAX_CONNECTION_NUM; i++)
    {
        // 每1000 停顿一下
        if(0 == i % 1500)
        // 越大握手越慢
        {//稍稍停顿一下，避免把服务端的握手队列打满
            printf("%s 连接 %s:%d成功了 %d 条！\n", lIp, sIp, sPort, i);
            sleep(1);
        }

        // 创建连接
        fd = buildConnect(lIp, sIp, sPort);
        if(fd > 0)
        {
            sockets[i-1] = fd;
        }else{
            return 1;
        }
    }


    sleep(300);



    //3. 释放所有的连接
    printf("关闭所有的连接...\n");
    for(i = 0; i < MAX_CONNECTION_NUM; i++)
    {
        close(sockets[i]);
    }

    return 0;
}
