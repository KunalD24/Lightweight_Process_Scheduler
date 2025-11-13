#ifndef CONTEXT_H
#define CONTEXT_H

#include<ucontext.h>
#include"thread.h"

void context_create();
void context_save();
void context_restore();
void context_switch();

#endif