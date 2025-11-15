#include <stdio.h>
#include "thread.h"
#include "scheduler.h"
#include "timer.h"
#include <string.h>

void func(void *arg)
{
    int id = *(int *)arg;
    for(int i=0; i<5; ++i)
    {
        printf("Thread %d is running and i = %d\n",id,i);
        thread_yield();
    }
    thread_exit();
}
int main(int argc, char **argv) 
{ 
    int preemptive = 0;
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

    thread_create(func, &id1, 1);
    thread_create(func, &id2, 1);
    thread_create(func, &id3, 1);

    if(preemptive) 
    {
        timer_init();
    }
    thread_yield();
    return 0; 
}
