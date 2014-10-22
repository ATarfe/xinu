#include <future.h>
#include <thread.h>
#include <stdlib.h>
void add_to_queue(queue *q,tid_typ thr){
    if(q==NULL){
        q=(queue*)(malloc(sizeof(queue)));
        q->thread=thr;
        q->next=NULL;
        return;
    }
    while(q->next!=NULL){
        q=q->next;
    }
    q->next=(queue*)malloc(sizeof(queue));
    ((queue*)(q->next))->thread=thr;
    ((queue*)(q->next))->next=NULL;
}

tid_typ peek(queue q){
    return q.thread;
}
