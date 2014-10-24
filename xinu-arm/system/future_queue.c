#include <future.h>
#include <thread.h>
#include <stdlib.h>


void put_thread_to_sleep(tid_typ tid){
    //interrupts must be disabled already!
    //put thread state to wait
    thrtab[tid].state=THRWAIT;
    //reschedule
    resched();
}

//add to queue
//queue must be valid.
void add_to_queue(queue *q,tid_typ thr){
    while(q->next!=NULL){
        q=q->next;
    }
    q->next=(queue*)malloc(sizeof(queue));
    ((queue*)(q->next))->thread=thr;
    ((queue*)(q->next))->next=NULL;
}

tid_typ peek(queue *q){
    return q->thread;
}

//pop first element of queue
void pop(queue *q){
    queue * next=q->next;
    if(next==NULL){
        q->thread=-1;
        return;
    }
    q->next=next->next;
    q->thread=next->thread;
    free(next);
}
