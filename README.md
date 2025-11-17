# Lightweight Process Scheduler

A lightweight user-space threading library implementing cooperative and preemptive scheduling using `ucontext.h`.

This project demonstrates how operating systems manage **context switching, scheduling, and preemption without kernel threads** — ideal for learning and experimentation in concurrency and scheduling.

---

## Features

### **Custom thread library**
- `thread_create()` — create a new user thread  
- `thread_yield()` — voluntarily give up CPU (cooperative mode)  
- `thread_exit()` — terminate current thread  
- `thread_join()` — wait for a thread to finish  

### **Scheduling**
- Priority-based ready queue  
- Round-robin behavior among threads with the same priority  
- Switchable Cooperative / Preemptive modes  

### **Preemption**
Uses `setitimer()` + `SIGALRM` to trigger preemption every **50 ms**

### **Context switching**
Built using:
getcontext()
makecontext()
swapcontext()
setcontext()

---

### Modes
| Mode            | Behavior                                             |
| --------------- | ---------------------------------------------------- |
| **Cooperative** | Threads must call `thread_yield()`                   |
| **Preemptive**  | Timer (`SIGALRM`) forces a context switch every 50ms |

## Build Instructions

### **Compile**
```sh
make clean
```
```sh
make
```
```sh
./lightweight_scheduler
```
```sh
./lightweight_scheduler --mode=preemptive
```

### **Output**
```sh
./lightweight_scheduler
Starting in COOPERATIVE mode 
Thread 1 is running and i = 0
Thread 3 is running and i = 0
Thread 1 is running and i = 1
Thread 3 is running and i = 1
Thread 1 is running and i = 2
Thread 3 is running and i = 2
Thread 1 is running and i = 3
Thread 3 is running and i = 3
Thread 1 is running and i = 4
Thread 3 is running and i = 4
Thread 2 is running and i = 0
Thread 2 is running and i = 1
Thread 2 is running and i = 2
Thread 2 is running and i = 3
Thread 2 is running and i = 4
All Thread Finish
```
```sh
./lightweight_scheduler --mode=preemptive
Starting in PREEMPTIVE mode  
Thread 1 is running and i = 0
Thread 3 is running and i = 0
Thread 1 is running and i = 1
Thread 3 is running and i = 1
Thread 1 is running and i = 2
Thread 3 is running and i = 2
Thread 1 is running and i = 3
Thread 3 is running and i = 3
Thread 1 is running and i = 4
Thread 3 is running and i = 4
Thread 2 is running and i = 0
Thread 2 is running and i = 1
Thread 2 is running and i = 2
Thread 2 is running and i = 3
Thread 2 is running and i = 4
All Thread Finish
```

## Learning Outcomes

1. Understand **kernel vs user threads**
2. Implement manual **context switching**
3. Learn basics of **scheduling & preemption**
4. Build a functioning **priority + round-robin scheduler**
