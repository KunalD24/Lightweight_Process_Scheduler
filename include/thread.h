#ifndef THREAD_H
#define THREAD_H

#include <ucontext.h>
#include <stdlib.h>

typedef enum {READY, RUNNING, WAITING_OR_BLOCKED, TERMINATED} thread_state;

typedef struct thread
{
    int thread_id;
    int priority;
    ucontext_t context;
    void *stack;
    thread_state state;
    struct thread *next;
} thread_t;

void thread_create();
void thread_yield();
void thread_join();
void thread_exit();

#endif