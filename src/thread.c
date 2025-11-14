#include<stdio.h>
#include "thread.h"
#include "scheduler.h"
#include "context.h"

static int next_id = 1;

int thread_create(void (*start_routine)(void *), void *arg, int priority)
{
    thread_t *thread = malloc(sizeof(thread_t));
    if(!thread)
    {
        perror("Malloc Failed");
        return -1;
    }
    thread->thread_id = next_id++;
    thread->priority = priority;
    thread->state = READY;
    thread->thread_data = arg;
    thread->next = NULL;

    context_create(thread, start_routine, arg);
    scheduler_add_thread(thread);

    return thread->thread_id;
}