#include "context.h"
#include <stdio.h>


void context_create(thread_t *thread, void (*func)(void *), void *arg)
{
    if(getcontext(&thread->context) == -1)
    {
        perror("Getcontext failed");
        exit(1);
    }
    thread->stack = malloc(STACK_SIZE);
    if(!thread->stack)
    {
        perror("Malloc Failed");
        exit(1);
    }
    thread->context.uc_stack.ss_sp = thread->stack;
    thread->context.uc_stack.ss_size = STACK_SIZE;
    thread->context.uc_link = NULL;
    makecontext(&thread->context, (void (*)(void))func, 1, arg);
}

void context_switch(thread_t *from, thread_t *to)
{
    if(!from)
    {
        if(setcontext(&to->context) == -1)
        {
            perror("setcontext");
            exit(1);
        }
    }
    else
    {
        if(swapcontext(&from->context, &to->context) == -1)
        {
            perror("Swapcontext failed");
            exit(1);
        }
    }
}