#include <fs.h>
#include <stdlib.h>
#include <stdio.h>


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

/*
    Block Store functions
    bread, bwrite,
    bput, bget write entire blocks (macro with offset=0, len=blocksize)
*/
int mkbsdev(int dev, int blocksize, int numblocks)
{
}
int bread(int bsdev, int block, int offset, void *buf, int len)
{
}
int bwrite(int bsdev, int block, int offset, void * buf, int len)
{
}

/* debugging functions */
void printfreemask(void)
{
}
void print_fsd(void)
{
}
