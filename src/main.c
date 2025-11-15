#include <stdio.h>
#include "thread.h"
#include "scheduler.h"
#include "timer.h"
#include <string.h>

int preemptive = 0;

void func(void *arg)
{
    int id = *(int *)arg;
    for(int i = 0; i < 5; ++i)
    {
        printf("Thread %d is running and i = %d\n", id, i);

        for (volatile long j = 0; j < 50000000; j++);

        if (!preemptive)
        {
            thread_yield();
        }
    }
    thread_exit();
}

int main(int argc, char **argv) 
{ 
    preemptive = 0;
    if(argc > 1)
    {
        if(strcmp(argv[1],"--mode=preemptive") == 0)
        {
            preemptive = 1;
        }
    }

    if (preemptive) 
    {
        printf("Starting in PREEMPTIVE mode\n");
    } 
    else 
    {
        printf("Starting in COOPERATIVE mode\n");
    }

    int id1 = 1;
    int id2 = 2;
    int id3 = 3;

    int tid1 = thread_create(func, &id1, 3);
    int tid2 = thread_create(func, &id2, 1);
    int tid3 = thread_create(func, &id3, 2);

    if(preemptive) 
    {
        timer_init();
    }
    thread_yield();

    thread_join(tid1);
    thread_join(tid2);
    thread_join(tid3);
    return 0; 
}