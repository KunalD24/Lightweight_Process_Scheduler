#include <stdio.h>
#include "thread.h"
#include "scheduler.h"

void func(void *arg)
{
    int id = *(int *)arg;
    printf("Thread %d is running\n",id);
}
int main() 
{ 
    int id1 = 1;
    int id2 = 2;

    thread_create(func, &id1, 1);
    thread_create(func, &id2, 1);

    thread_t *thread;
    while((thread = scheduler_pick_next_thread()) != NULL)
    {
        thread->state = RUNNING;
        setcontext(&thread->context);
    }
    printf("All thread finish\n"); 
    return 0; 
}
