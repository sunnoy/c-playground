//
// Created by lirui on 2021/2/26.
//
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void thread (void )
{
    sleep(100);
    return;
}

int main() {
    pthread_t id;
    int ret;
    int num = 0 ;
    for (int a = 0; a < 500; a = a + 1) {

        // man 文档
        // https://man7.org/linux/man-pages/man3/pthread_create.3.html
        ret = pthread_create(&id,NULL,(void *)thread,NULL);
        ++num;
        if (ret != 0)
            break;


    }
    printf("pthread_create fail with ret=%d, total num=%d\n", ret, num);
    sleep(100);
    return 0;
}