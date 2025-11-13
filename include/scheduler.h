#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "thread.h"

extern thread_t *ready_queue;

void scheduler_add_thread();
thread_t scheduler_pick_next_thread();
void scheduler_remove_thread();
#endif