#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "thread.h"

extern thread_t *ready_queue;
extern thread_t *all_thread;

void scheduler_add_thread(thread_t *thread);
thread_t* scheduler_pick_next_thread(void);
void scheduler_remove_thread(thread_t *thread);
#endif