#include <fs.h>
#include <stdlib.h>
#include <stdio.h>
#include <kernel.h>
#include <stddef.h>
#include <string.h>
#include <bufpool.h>


int fopen(char *filename, int flags){

}
int fclose(int fd)
{
}
int fcreate(char *filename, int mode)
{
}
int fseek(int fd, int offset)
{
}
int fread(int fd, void *buf, int nbytes)
{
}
int fwrite(int fd, void *buf, int nbytes)
{
}

/* filesystem functions */
int mkfs(int dev, int num_inodes)
{
    //make bs dev:blocksize for default values:
    if(OK==mkbsdev(
                dev,
                MDEV_BLOCK_SIZE,
                num_inodes*ceil(((float)sizeof(inode)/(float)MDEV_BLOCK_SIZE)))
            )
    {
        //init fsystem to block 0:
        struct fsystem fs;
        fs.nblocks=num_inodes*ceil(((float)sizeof(inode)/(float)MDEV_BLOCK_SIZE));
        fs.blocksz=MDEV_BLOCK_SIZE;
        fs.ninodes=num_inodes;
        fs.inodes_used=0;
        bwrite(dev,0,0,,sizeof(fsystem));
    }
    else return SYSERR;
}
int mount(int dev)
{
}

/* filesystem internal functions */
int get_inode_by_num(int dev, int inode_number, struct inode *in)
{
}
int put_inode_by_num(int dev, int inode_number, struct inode *in)
{
}
int setmaskbit(int b)
{
}
int clearmaskbit(int b)
{
}
int getmaskbit(int b)
{
}

/* debugging functions */
void printfreemask(void)
{
}
void print_fsd(void)
{
}
