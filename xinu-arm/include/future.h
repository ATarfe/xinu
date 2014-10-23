#pragma once

#ifndef _FUTURE_H_
#define _FUTURE_H_
#include <semaphore.h>
#include <thread.h>
#include <stdlib.h>
/* define states */
#define FUTURE_EMPTY         0
#define FUTURE_WAITING       1                                    
#define FUTURE_VALID         2                                    
/* modes of operation for future*/
#define FUTURE_EXCLUSIVE        1
#define FUTURE_SHARED        2
#define FUTURE_QUEUE        3

typedef struct{
    tid_typ thread;
    struct queue* next;
}queue;


typedef struct futent
{
    int *value;
    int flag;
    int state;                                    
    tid_typ tid;
    queue *set_queue;
    queue *get_queue;
}future;
/* Interface for system call */
future* future_alloc(int future_flags);
syscall future_free(future*);
syscall future_get(future*, int*);
syscall future_set(future*, int*);
tid_typ peek(queue* q);
void add_to_queue(queue **q,tid_typ thr);
#endif /* _FUTURE_H_ */
