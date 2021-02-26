# 执行

```bash
# 编译
gcc server.c -o server

# 运行
./server 0.0.0.0 80
```

# clidnt

```bash

gcc client.c -o client

# 运行
./client 10.0.4.9 10.0.4.2 80

```


# 错误

总是两万八个连接

本地端口数量限制了 60999-32768 = 
net.ipv4.ip_local_port_range = 32768	60999

连接队列
netstat -s | egrep "listen|LISTEN"

# 半链接
sysctl -w net.ipv4.tcp_max_syn_backlog=2048
半连接队列最大值不是单单由 max_syn_backlog 决定，还跟 somaxconn 和 backlog 有关系。

查看状态
netstat -natp | grep SYN_RECV | wc -l

# 全连接
somaxconn和监听backlog的最小值
sysctl -w net.core.somaxconn=2048

# 
