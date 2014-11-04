/* courtesy : [System V] */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <kernel.h>
#include <shm.h>

#define SEGSIZE 100
#define KEY     1

void writeshm(int shmid, char *segptr, char *text)
{
        strcpy(segptr, text);
        printf("Wrote to shared memory segment #%d\n", shmid);
}

void readshm(int shmid, char *segptr)
{
        printf("Contents of shared memory segment #%d: %s\n", shmid, segptr);
}

void removeshm(int shmid)
{
        shmdt(shmid);
        printf("Detached shared memory segment #%d\n", shmid);
}

void usage()
{
        fprintf(stderr, "shmipc - A utility for tinkering with shared memory\n");
        fprintf(stderr, "\nUSAGE:  shmipc (w)rite <text>\n");
        fprintf(stderr, "                (r)ead\n");
        fprintf(stderr, "                (d)elete\n");
}

shellcmd xsh_shmipc(int argc, char *argv[])
{
        key_t key = KEY;            /* NOTE: all invocations use the same key */
        int   shmid, cntr;
        char  *segptr;
        int createflags = IPC_CREAT;
        int accessflags = IPC_ACCES;    /* NOTE : access != create */

        if(argc == 1)
            usage();

        /* Open the shared memory segment - create if necessary */
        if((shmid = shmget(key, SEGSIZE, createflags)) == -1) 
        {
            /* Segment probably already exists - try as a client */
            if((shmid = shmget(key, SEGSIZE, accessflags)) == -1) 
            {
                fprintf(stderr,"shmget : create, access\n");
                return;
            }
            printf("Opened shared memory segment #%d\n", shmid);
        }
        else
        {
            printf("Created new shared memory segment #%d\n", shmid);
        }

        /* Attach (map) the shared memory segment into the current process */
        if((segptr = (char *) shmat( shmid )) == (char *) -1)
        {
            fprintf(stderr,"shmat\n");
            return;
        }

        switch((argv[1][0]))
        {
                case 'w': writeshm(shmid, segptr, argv[2]);
                          break;
                case 'r': readshm(shmid, segptr);
                          break;
                case 'd': removeshm(shmid);
                          break;
                /*
                case 'm': changemode(shmid, argv[2]);
                          break;
                */
                 default: usage();
        }
}

