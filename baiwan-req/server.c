//
// Created by lirui on 2021/2/24.
//

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONNECTION_NUM 2

// 通过在main函数上添加参数来使程序可以接受命令行参数
int main(int argc, char *argv[])
{
    // 声明一个数组 ip 16个字节 char的储值大小为一个字节
    char ip[16];
    // 声明三个 int 类型的变量
    int lisFd, conFd, port;
    // 声明一个 sockaddr_in 类型 Socket address, internet style 的结构体
    struct sockaddr_in servAddr;

    if(argc != 3)
    {
        printf("\n Usage: %s <server ip> <server port>\n", argv[0]);
        return 1;
    }

    //1. 从命令行获取并解析server ip以及端口
    // 第一个参数为监听的IP
    strcpy(ip, argv[1]);
    // 第二个参数为监听的端口
    port = atoi(argv[2]);

    //2. 创建server

    // 创建一个socket插口端点
    // int socket(int domain, int type, int protocol);
    // AF_INET      IPv4 Internet protocols
    // SOCK_STREAM 支持tcp
    if((lisFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket\n");
        return 0;
    }


    // 初始化 sockaddr_in 类型的数据结构
    // 协议类型
    servAddr.sin_family = AF_INET;
    // IP
    servAddr.sin_addr.s_addr = inet_addr(ip);
    // 端口
    servAddr.sin_port = htons(port);

    // assigns the address specified by addr to the socket referred to
    //   by the file descriptor sockfd
    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    // sock 为 socket 文件描述符，addr 为 sockaddr 结构体变量的指针，addrlen 为 addr 变量的大小，可由 sizeof() 计算得出
    //  sizeof是C/C++中的一个操作符（operator），简单的说其作用就是返回一个对象或者类型所占的内存字节数

    // sockaddr 是一种通用的结构体，可以用来保存多种类型的IP地址和端口号，而 sockaddr_in 是专门用来保存 IPv4 地址的结构体
    // (struct sockaddr*)&servAddr 用于类型转换
    // (float) a;  将变量 a 转换为 float 类型 括号内的类型
    if(bind(lisFd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
    {
        printf("\n Error : Bind Failed \n");
    }

    // socket可以进行接受请求
    if((listen(lisFd, 1024)) < 0)
    {
        printf("\n Error : Listen Failed \n");
    }

    //3. 接收连接
    int i = 0;
    // malloc() 分配虚拟内存
    // The malloc() function allocates size bytes and returns a pointer to the allocated memory
    int *sockets = (int *)malloc(sizeof(int) * MAX_CONNECTION_NUM);

    while(1)
    {
        // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
        // 返回链接描述符
        // accept() 返回一个新的套接字描述符来和客户端通信，addr 保存了客户端的IP地址和端口号，而 sock 是服务器端的套接字
        // accept() 会阻塞程序执行（后面代码不能被执行），直到有新的请求到来
        conFd = accept(lisFd, (struct sockaddr*)NULL, NULL);

        if(conFd > 0)
        {
            sockets[i++] = conFd;
            printf("%s %d accept success:%d\n", ip, port, i);
        }
    }
}