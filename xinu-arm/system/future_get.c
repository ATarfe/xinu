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
        if(f->state==FUTURE_EMPTY && f->tid==NULL){
            //set tid:
            f->tid=gettid();
            //set state:
            f->state=FUTURE_WAITING;
            //block thread:
            //disable interrupts
            irqmask im=disable();
            //put thread state to wait
            thrtab[f->tid].state=THRWAIT;
            //reschedule
            resched();
            //restore interrupts
            restore(im);
            if(f->state==FUTURE_VALID){
                f->state=FUTURE_EMPTY;
                *value=*(f->value);
                //reset tid:
                f->tid=NULL;
                return OK;
            }
        }
    }
    else 
    if (f->flag==FUTURE_SHARED && (f->state==FUTURE_WAITING || f->state==FUTURE_EMPTY)){
        irqmask im=disable();
        if(f->state!=FUTURE_WAITING){
            f->state=FUTURE_WAITING;
        }
        add_to_queue(&(f->get_queue),gettid());
        //put current thread to wait
        thrtab[gettid()].state=THRWAIT;
        //reschedule
        resched();
        //restore interrupts
        restore(im);
        if(f->state==FUTURE_VALID){
            *value=*(f->value);
            //wake up next consumer in queue, if valid:
            im=disable();
            if(f->get_queue!=NULL){
                tid_typ listener=peek(f->get_queue);
                ready(listener,RESCHED_YES);
                queue *nextinqueue=f->get_queue->next;
                free(f->get_queue);
                f->get_queue=nextinqueue;
            }
            restore(im);
            return OK;
        }
    }
    else 
    if (f->flag==FUTURE_QUEUE && (f->state==FUTURE_WAITING || f->state==FUTURE_EMPTY)){
        irqmask im=disable();
        if(f->state!=FUTURE_WAITING){
            f->state=FUTURE_WAITING;
        }
        add_to_queue(&(f->get_queue),gettid());
        //test if producer exists:
        if(f->set_queue!=NULL){
            tid_typ prod=peek(f->set_queue);
            ready(prod,RESCHED_YES);
            //replace next consumer:
            queue * nextCons=f->get_queue->next;
            free(f->get_queue);
            f->get_queue=nextCons;
        }
        //put current thread to wait
        thrtab[gettid()].state=THRWAIT;
        //reschedule
        resched();
        //restore interrupts
        restore(im);
        if(f->state==FUTURE_VALID){
            *value=*(f->value);
            im=disable();
            //set state to empty:
            f->state=FUTURE_EMPTY;
            restore(im);
            return OK;
        }

    }
    return SYSERR;
}
