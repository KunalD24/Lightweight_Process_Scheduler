#ifndef TIMER_H
#define TIMER_H

#include<signal.h>
#include<sys/time.h>

void timer_init();
void timer_handler(int signum);

#endif