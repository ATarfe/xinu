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
        else{
            return SYSERR;
        }
    }
    else
    if (f->flag==FUTURE_SHARED){
        if(f->state==FUTURE_WAITING || f->state==FUTURE_EMPTY){
            //disable interrupts-only thread running here.
            irqmask im=disable();
            f->state=FUTURE_VALID;
            *(f->value)=*value;
            //put thread into ready queue
            if(f->get_queue.thread!=0){
                tid_typ listener=peek(f->get_queue);
                ready(listener,RESCHED_YES);
                queue *nextinqueue=f->get_queue.next;
                free(&(f->get_queue));
                f->get_queue=*nextinqueue;
            }
            //restore interrupts.
            restore(im);
            return OK;
        }
        return SYSERR;
    }
    else
    if (f->flag==FUTURE_QUEUE){
        //check first if a consumer is waiting:
        if(f->state==FUTURE_EMPTY || f->state==FUTURE_WAITING){
            //put myself into queue:
            add_to_queue(&(f->set_queue),gettid());
            if((f->get_queue).thread==0){
                //I wait.
                irqmask im=disable();
                thrtab[gettid()].state=THRWAIT;
                resched();
                restore(im);
            }
            //woken up by consumer, or if consumers waiting, produce
            *(f->value)=*value;
            f->state=FUTURE_VALID;
            //signal consumer to consume
            irqmask im=disable();
            tid_typ listener=peek(f->get_queue);
            ready(listener,RESCHED_YES);
            queue *nextinqueue=f->get_queue.next;
            free(&(f->get_queue));
            f->get_queue=*nextinqueue;
            ready(listener,RESCHED_YES);
            restore(im);
            return OK;
        }
        return SYSERR;
    }
}
