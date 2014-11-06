/**
 * Peter Zhang(yz79)
 * Eriya Terada(eterada)
 * P536 HW7 IPC
 * shm.h
 * 11/6/14
 */
#pragma once
#include <stdint.h>

#define IPC_CREAT 1
#define IPC_ACCES 2

#define IPC_MAX_SEG 1024 


typedef int32_t key_t;

struct shmid_ds 
{
    char*           shm_seg;         /* pointer to shared memory segment */
    int             shm_segsz;       /* size of segment (bytes) */
    unsigned short  shm_cpid;        /* pid of creator */
    unsigned short  shm_lpid;        /* pid of last operator */
    short           shm_nattch;      /* no. of current attaches */
};


int shmget ( key_t key, int size, int shmflg );

/*
    DESCRIPTION ...

    key - unique key for identifying a shared memory segment
    size - size of the shared memory segment
    shmflg - IPC_CREAT to create a shared memory segment
             IPC_ACCES to access an existing shared memory segment             
    returns shmid - id of shared memory segment mapped to key
*/

char* shmat ( int shmid );

/*
    DESCRIPTION ...

    returns a pointer to the shared memory segment
*/

int shmdt ( int shmid );

/*
    DESCRIPTION ...

    each call to shmdt() reduces the value of shm_nattach by 1;
    a shared memory segment is detached when shm_nattach reaches 0
*/
