/**
 * Peter Zhang(yz79)
 * Eriya Terada(eterada)
 * P536 HW7 IPC
 * shm.c
 * 11/6/14
 */

#include <shm.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <kernel.h>
#include <string.h>

typedef struct shmseg shmseg;

struct shmseg{
    key_t key;
    struct shmid_ds seg;     //segment
    shmseg * prev;
    shmseg * next;
};

shmseg *shmqueue; //last node in queue

//construct a 2-pointer non-cyclic linked list
uint32_t add_shmseg(struct shmid_ds segment, key_t key){
    if(shmqueue==NULL){
        shmqueue=(shmseg*)malloc(sizeof(shmseg));
        shmqueue->prev=NULL;
        shmqueue->next=NULL;
        shmqueue->key=key;
        memcpy(&(shmqueue->seg), &segment, sizeof(struct shmid_ds));
    }
    else{
        shmseg *newseg=(shmseg*)malloc(sizeof(shmseg));
        newseg->prev=shmqueue;
        shmqueue->next=newseg;
        newseg->next=NULL;
        newseg->key=key;
        memcpy(&(newseg->seg), &segment, sizeof(struct shmid_ds));
        shmqueue=newseg;
    }
    return (uint32_t)shmqueue;
}

uint32_t get_key_seg(key_t key){
    shmseg * current=shmqueue;
    while(current!=NULL){
        if(current->key==key){
            return current;
        }
        current=shmqueue->prev;
    }
    return -1;
}

void destroy_shmseg(int shmseg_id){
    shmseg* seg=(shmseg*)shmseg_id;
    seg->prev->next=seg->next;
    seg->next->prev=seg->prev;
    free(seg);
}

int shmget ( key_t key, int size, int shmflg ){
    //first check if key already exists:
    int ipc_segment_id=-1;
    ipc_segment_id=get_key_seg(key);

    if(shmflg==IPC_ACCES){
        if(ipc_segment_id!=-1){
            //if access, return segid
            return ipc_segment_id;
        }
        else{
            fprintf(stderr,"shm access error: key doesn't exist\n\r");
            return -1;
        }
    }

    /****ALLOCATE******/

    else if(shmflg==IPC_CREAT){
        if(ipc_segment_id!=-1){
            fprintf(stderr,"shm access error: key already exists\n\r");
            return -1;
            
        }
        //disable interrupts for mutex access
        irqmask im=disable();
        struct shmid_ds current_segment;
        current_segment.shm_seg=memget(size);
        current_segment.shm_segsz=size;
        current_segment.shm_cpid=gettid();
        current_segment.shm_lpid=gettid();
        current_segment.shm_nattch=1;
        ipc_segment_id=add_shmseg(current_segment,key);
        restore(im);
        return ipc_segment_id;
    }
    return -1;
}

char* shmat ( int shmid ){
    shmseg* seg=(shmseg*)shmid;
    struct shmid_ds current_segment=seg->seg;
    //attach:
    current_segment.shm_nattch+=1;
    //change operator??
    current_segment.shm_lpid=gettid();
    return current_segment.shm_seg;
}

int shmdt ( int shmid ){
    shmseg* seg=(shmseg*)shmid;
    struct shmid_ds current_segment=seg->seg;
    //dettach:
    current_segment.shm_nattch-=1;
    if (current_segment.shm_nattch==0){
        //free shm segment:
        memfree(current_segment.shm_seg, current_segment.shm_segsz);
        //destroy container:
        destroy_shmseg(shmid);
    }
    return 0;
}
