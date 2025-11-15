#include "timer.h"
#include "thread.h"
#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

extern thread_t *current_thread;

void timer_handler(int signum)
{
    (void)signum;
    if(!current_thread || current_thread->state != RUNNING)
    {
        return;
    }

    thread_t *next_thread = scheduler_pick_next_thread();
    if(!next_thread)
    {
        return;
    }

    if(current_thread->state != TERMINATED)
    {
        current_thread->state = READY;
        scheduler_add_thread(current_thread);
    }

    thread_t *prev_thread = current_thread;
    current_thread = next_thread;
    current_thread->state = RUNNING;

    if(swapcontext(&prev_thread->context, &current_thread->context) == -1)
    {
        perror("swapcontext");
        exit(1);
    }
}

void timer_init()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = timer_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    if(sigaction(SIGALRM, &sa, NULL) == -1)
    {
        perror("SIGACTION");
        exit(1);
    }

    struct itimerval tv;
    tv.it_interval.tv_sec = 0;
    tv.it_interval.tv_usec = TIME_SLICE_USEC;
    tv.it_value.tv_sec = 0;
    tv.it_value.tv_usec = TIME_SLICE_USEC;

    if (setitimer(ITIMER_REAL, &tv, NULL) == -1) 
    {
        perror("setitimer");
        exit(1);
    }
}