#include "scheduler.h"
#include<stdlib.h>

thread_t *ready_queue = NULL;
thread_t *all_thread = NULL;

void scheduler_add_thread(thread_t *thread)
{
    if(!thread)
    {
        return;
    }
    thread->next = NULL;
    if(!ready_queue)
    {
        ready_queue = thread;
    }
    else
    {
        thread_t *temp = ready_queue;
        while(temp->next)
        {
            temp = temp->next;
        }
        temp->next = thread;
    }
    thread->next_all = all_thread;
    all_thread = thread;
}

thread_t* scheduler_pick_next_thread()
{
    if(!ready_queue)
    {
        return NULL;
    }
    thread_t *thread = ready_queue;
    ready_queue = ready_queue->next;
    thread->next = NULL;
    return thread;
}
