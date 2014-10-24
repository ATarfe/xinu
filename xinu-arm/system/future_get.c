/*
 * @file future_get.c
 * @provides future_get
 * For Xinu OS for Assignment 5 of P536
  * Peter Zhang (yz79)
  * Eriya Terada (eterada)
  *
  * Oct 9 2014
  */
  
#include <stdio.h>
#include <string.h>
#include <future.h>
//necessary??
#include <kernel.h>

void print_queue(queue*q){
    while(q!=NULL){
        printf("element:%d\n\r",q->thread);
        q=q->next;
    }
}

int get_exclusive(future *f, int * value){
    if(f->state==FUTURE_EMPTY){
        //set tid:
        f->tid=gettid();
        //set state:
        f->state=FUTURE_WAITING;
        //disable interrupts
        irqmask im=disable();
        //sleep:
        put_thread_to_sleep(gettid());
        restore(im);
        if(f->state==FUTURE_VALID){
            f->state=FUTURE_EMPTY;
            *value=*(f->value);
            //reset tid:
            f->tid=NULL;
            return OK;
        }
    }
    else if (f->state==FUTURE_VALID){
        //just get value:
        irqmask im=disable();
        f->state=FUTURE_EMPTY;
        *value=*(f->value);
        //reset tid:
        f->tid=NULL;
        restore(im);
        return OK;

    }
}

int get_shared(future *f, int * value){
    while(1){
        //printf("getter tid=%d\n\r",gettid());
        if(f->state==FUTURE_VALID){
            //get value:
            *value=*(f->value);
            //last in queue?
            if(f->get_queue!=NULL && f->get_queue->thread!=-1){
                //wake up next consumer:
                irqmask im=disable();
                //printf("valid, check getqueue\n\r");
                //print_queue(f->get_queue);
                //printf("end getqueue, first in line:%d\n\r",f->get_queue->thread);
                //pop first in queue:
                int first=peek(f->get_queue);
                //pop:
                pop(f->get_queue);
                ready(first,RESCHED_YES);
                restore(im);
                return OK;
            }
            else{
                //last one: 
                //get value:
                *value=*(f->value);
                *(f->value)=0xdeadbeef;
                f->state=FUTURE_EMPTY;
                return OK;
            }
        }
        else if(f->state==FUTURE_WAITING){
            //printf("waiting at tid %d\n\r",gettid());
            //add yourself to queue:
            irqmask im=disable();
            add_to_queue(f->get_queue,gettid());
            //print_queue(f->get_queue);
            put_thread_to_sleep(gettid());
            restore(im);
        }
        else if(f->state==FUTURE_EMPTY){
            //printf("empty at tid %d\n\r",gettid());
            irqmask im=disable();
            //make queue:
            //build head node:
            f->get_queue=(queue*)malloc(sizeof(queue));
            f->get_queue->thread=gettid();
            f->get_queue->next=NULL;
            f->state=FUTURE_WAITING;
            put_thread_to_sleep(gettid());
            restore(im);
        }
    }
}

int get_queue(future *f, int * value){
    while(1){
        //printf("get tid=%d, state=%d\n\r",gettid(),f->state);
        if(f->state==FUTURE_VALID){
            //get value:
            irqmask im=disable(); 
            *value=*(f->value);
            //a producer waiting?
            if(f->set_queue!=NULL && f->set_queue->thread!=-1){
                //wake up next producer:
                int first=peek(f->set_queue);
                pop(f->set_queue);
                f->state=FUTURE_EMPTY;
                ready(first,RESCHED_YES);
                restore(im);
                return OK;
            }
            else if (f->get_queue!=NULL && f->get_queue->thread!=-1){
                //get value:
                *value=*(f->value);
                *(f->value)=0xdeadbeef;
                f->state=FUTURE_WAITING;
                restore(im);
                return OK;
            }
            return OK;
        }
        else if(f->state==FUTURE_WAITING){
            //add yourself to queue:
            irqmask im=disable();
            add_to_queue(f->get_queue,gettid());
            put_thread_to_sleep(gettid());
            restore(im);
        }
        else if(f->state==FUTURE_EMPTY){
            irqmask im=disable();
            //make queue:
            //build head node:
            f->get_queue=(queue*)malloc(sizeof(queue));
            f->get_queue->thread=gettid();
            f->get_queue->next=NULL;
            f->state=FUTURE_WAITING;
            put_thread_to_sleep(gettid());
            restore(im);
        }
         
    }
}
/**
 * Get the value of a future set by an operation and change the state of future  
 * fromFUTURE_VALID to FUTURE_EMPTY
 * params: future *f: future on which to wait for and obtain value int *value:
 * variable in which to obtain the value from a future
 *
 * return: syscall: SYSERR or OK 
 */
syscall future_get(future *f, int *value){
    //if tid id not set and state is empty
    if(f->flag==FUTURE_EXCLUSIVE){
        return get_exclusive(f,value);
    }
    else 
    if (f->flag==FUTURE_SHARED ){
        return get_shared(f,value);
    }
    else 
    if (f->flag==FUTURE_QUEUE){
        return get_queue(f,value);
    }
    return SYSERR;
}
