/*
 * @file future_set.c
 * @provides future_set  
 * */
 /* For Xinu OS for Assignment 5 of P536
  * Peter Zhang (yz79)
  * Eriya Terada (eterada)
  *
  * Oct 9 2014
  */
  
#include <stdio.h>
#include <string.h>
#include <future.h>
#include <kernel.h>

void print_queuee(queue*q){
    while(q!=NULL){
        printf("element:%d\n\r",q->thread);
        q=q->next;
    }
}

int set_exclusive(future *f, int * value){
    if(f->state==FUTURE_WAITING || f->state==FUTURE_EMPTY){
        *(f->value)=*value;
        f->state=FUTURE_VALID;
        //disable interrupts
        irqmask im=disable();
        //put thread into ready queue
        ready(f->tid,RESCHED_YES);
        //restore interrupts.
        restore(im);
        return OK;
    }
    return SYSERR;
}

int set_shared(future *f, int * value){
    if(f->state!=FUTURE_VALID){
        //print_queuee(f->get_queue);
        irqmask im=disable();
        //set val
        *(f->value)=*value;
        //set state
        int oldstate=f->state;
        //printf("oldstate=%d\n\r",oldstate);
        f->state=FUTURE_VALID;
        //if no consumer waiting
        if(oldstate!=FUTURE_WAITING){
            restore(im);
            return OK;
        }
        //wake up first consumer:
        //printf("prod state:%d\n\r",oldstate);
        //pop first in queue:
        int first=peek(f->get_queue);
        pop(f->get_queue);
        ready(first,RESCHED_YES);
        restore(im);
        return OK;
    }
    return SYSERR;
}
/*
 * consumer has to check if both queues are empty before setting the state. 
 * AND set the states accordingly.
 */
int set_queue(future *f, int * value){
    if(f->state!=FUTURE_VALID){
        irqmask im=disable();
        //if i am the first one waiting:
        if(f->state==FUTURE_EMPTY){
            //build head node:
            f->set_queue=(queue*)malloc(sizeof(queue));
            f->set_queue->thread=-1;
            f->set_queue->next=NULL;
            //set state and value:
            f->state=FUTURE_VALID;
            *(f->value)=*value;
            //put_thread_to_sleep(gettid());
            restore(im);
            return OK;
        }
        //here state must be waiting: consumers
        else if(f->state==FUTURE_WAITING){
            //printf("waiting in set\n\r");
            //print_queuee(f->get_queue);
            *(f->value)=*value;
            //*(f->value)=gettid();
            //wake up consumer: 
            int first=peek(f->get_queue);
            pop(f->get_queue);
            f->state=FUTURE_VALID;
            ready(first,RESCHED_YES);
            restore(im);
            return OK;
        }
    }
    //valid:
    else{
        irqmask im=disable();
        //add myself to queue and wait.
        if(f->set_queue->thread==-1){
            f->set_queue->thread=gettid();
            f->set_queue->next=NULL;
        }
        else{
            add_to_queue(f->set_queue,gettid());
        }
        //sleep:
        put_thread_to_sleep(gettid());
        restore(im);

        //woken up:
        im=disable();
        if(f->state==FUTURE_WAITING){
            *(f->value)=*value;
            //wake up consumer: 
            int first=peek(f->get_queue);
            pop(f->get_queue);
            ready(first,RESCHED_YES);
            restore(im);
            return OK;
            
        }
        else if(f->state==FUTURE_EMPTY){
            //set state and value:
            f->state=FUTURE_VALID;
            *(f->value)=*value;
            restore(im);
            return OK;
        }
         
    }
    return SYSERR;
}

/**
 * Set a value in a future and changes state from FUTURE_EMPTY or FUTURE_WAITING
 * to FUTURE_VALID.  
 * params: future *f: future in which to set the value int
 *          *value: result of an operation to be set as value in a future 
 * return:
 * syscall: SYSERR or OK
 */
syscall future_set(future *f, int *value){
    if(f->flag==FUTURE_EXCLUSIVE){
        return set_exclusive(f,value);
    }
    else
    if (f->flag==FUTURE_SHARED){
        return set_shared(f,value);
    }
    else
    if (f->flag==FUTURE_QUEUE){
        return set_queue(f,value);
    }
    return SYSERR;
}
