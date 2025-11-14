#include <stdio.h>
#include "thread.h"
#include "scheduler.h"

void func(void *arg)
{
    int id = *(int *)arg;
    for(int i=0; i<5; i++)
    {
        printf("Thread %d is running and i = %d\n",id,i);
        thread_yield();
    }
    thread_exit();
}
int main() 
{ 
    int id1 = 1;
    int id2 = 2;
    int id3 = 3;

    thread_create(func, &id1, 1);
    thread_create(func, &id2, 1);
    thread_create(func, &id3, 1);

    thread_yield();
    return 0; 
}
