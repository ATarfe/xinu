#include <future.h>
#include <thread.h>
#include <stdlib.h>
void add_to_queue(queue **q,tid_typ thr){
    if(q==NULL){
        printf("adding: queue head at %x\n\r",q);
        *q=(queue*)(malloc(sizeof(queue)));
        (*q)->thread=thr;
        (*q)->next=NULL;
        return;
    }
    queue * currentqueue=*q;
    while(currentqueue->next!=NULL){
        currentqueue=currentqueue->next;
    }
    currentqueue->next=(queue*)malloc(sizeof(queue));
    ((queue*)(currentqueue->next))->thread=thr;
    ((queue*)(currentqueue->next))->next=NULL;
}

tid_typ peek(queue *q){
    return q->thread;
}
