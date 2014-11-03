#include <shm.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <kernel.h>

int shmget ( key_t key, int size, int shmflg ){
    //first check if key already exists:
    int i, ipc_segment_id=-1;
    for(i=0;i<IPC_MAX_SEG;i++){
        if(ipc_keymap[i]==key){
            ipc_segment_id=i; 
            //if access, return segid
            if(shmflg==IPC_ACCES){
                return ipc_segment_id;
            }
            else{
                fprintf(stderr,"shm allocate error: key already exists\n\r");
                return -1;
            }
        }
    }
    //allocate 
    if(ipc_segment_id==-1 && shmflg==IPC_ACCES){
        fprintf(stderr,"shm access error: key does not exist\n\r");
        return -1;
        
    }
    if(ipc_segment_id==-1 && shmflg==IPC_CREAT){
        //disable interrupts for mutex access
        irqmask im=disable();
        ipc_keymap[ipc_seq]=key;
        struct shmid_ds current_segment=ipc_seg[ipc_seq];
        current_segment.shm_seg=memget(size);
        current_segment.shm_segsz=size;
        current_segment.shm_cpid=gettid();
        current_segment.shm_lpid=gettid();
        current_segment.shm_nattch=1;
        ipc_segment_id=++ipc_seq;
        restore(im);
        return ipc_segment_id;
    }
    return -1;
}

char* shmat ( int shmid ){
    struct shmid_ds current_segment=ipc_seg[shmid];
    //attach:
    current_segment.shm_nattch+=1;
    //change operator??
    //TODO:verify
    return current_segment.shm_seg;
}

int shmdt ( int shmid ){
    struct shmid_ds current_segment=ipc_seg[shmid];
    //dettach:
    current_segment.shm_nattch-=1;
    if (current_segment.shm_nattch==0){
        //free shm segment:
        memfree(current_segment.shm_seg, current_segment.shm_segsz);
    }
    //TODO:cleanup
    return 0;
}
