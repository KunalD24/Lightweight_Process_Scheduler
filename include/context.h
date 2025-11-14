#ifndef CONTEXT_H
#define CONTEXT_H

#include<ucontext.h>
#include"thread.h"

void context_create(thread_t *thread, void (*func)(void *), void *arg);
void context_switch(thread_t *from, thread_t *to);

#endif