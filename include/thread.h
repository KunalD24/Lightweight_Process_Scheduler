#ifndef THREAD_H
#define THREAD_H

#include <ucontext.h>
#include<stdlib.h>

#define STACK_SIZE (1024 * 64)
#define TIME_SLICE_USEC 50000

typedef enum {READY, RUNNING, WAITING_OR_BLOCKED, TERMINATED} thread_state;

typedef struct thread
{
    int thread_id;
    int priority;
    ucontext_t context;
    void *stack;
    thread_state state;
    void *thread_data;
    struct thread *next;
} thread_t;

int thread_create(void (*start_routine)(void *), void *arg, int priority);
void thread_yield(void);
int thread_join(int thread_id);
void thread_exit(void);

#endif