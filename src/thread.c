#include "thread.h"
#include "scheduler.h"
#include "context.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int next_id = 1;
thread_t *current_thread = NULL;

int thread_create(void (*start_routine)(void *), void *arg, int priority)
{
    thread_t *thread = malloc(sizeof(thread_t));
    if(!thread)
    {
        perror("Malloc Failed");
        return -1;
    }
    memset(thread, 0, sizeof(*thread));
    thread->thread_id = next_id++;
    thread->priority = priority;
    thread->state = READY;
    thread->thread_data = arg;

    context_create(thread, start_routine, arg);
    scheduler_add_thread(thread);

    return thread->thread_id;
}

void thread_yield()
{
    thread_t *next_thread = scheduler_pick_next_thread();
    if(!next_thread)
    {
        return;
    }
    if(current_thread && current_thread->state != TERMINATED)
    {
        current_thread->state = READY;
        scheduler_add_thread(current_thread);
    }
    thread_t *prev_thread = current_thread;
    current_thread = next_thread;
    current_thread->state = RUNNING;

    if(prev_thread)
    {
        if(swapcontext(&prev_thread->context, &current_thread->context) == -1)
        {
            perror("swapcontext");
            exit(1);
        }
    }
    else
    {
        if(setcontext(&current_thread->context) == -1)
        {
            perror("setcontext");
            exit(1);
        }
    }
}

void thread_exit()
{
    if(!current_thread)
    {
        exit(0);
    }
    current_thread->state = TERMINATED;
    if(current_thread->stack)
    {
        free(current_thread->stack);
        current_thread->stack = NULL;
    }

    thread_t *next_thread = scheduler_pick_next_thread();
    if(next_thread)
    {
        current_thread = next_thread;
        current_thread->state = RUNNING;
        setcontext(&current_thread->context);
    }
    else
    {
        printf("All Thread Finish\n");
        exit(0);
    }
}

int thread_join(int thread_id)
{
    (void)thread_id;
    return -1;
}