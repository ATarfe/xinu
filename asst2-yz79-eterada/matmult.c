/*
 * Assignment 2
 *
 * Author: Peter Zhang (yz79), Eriya Terada (eterada)
 * CSCI P536 FA14 ASST0
 * Sept 23 2014
 * matmult.c file
 * contains methods to initialize and multiply matrices
 */
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

#include "matmult.h"
/**
 * rand_int function
 * designed for multithreaded program
 * @param tid thread id
 * reseeds random number generator based on current time and current thread id.
 */
int rand_int(int tid){
  struct timeval tv;
  gettimeofday(&tv,NULL);
  unsigned int seed=tv.tv_usec+tid*time(NULL);
  //generate numbers in the rage -1000~1000
  return (rand_r(&seed) % 50 -25);
}

/**
 * populates matrix with random integers
 * @param matrix
 * @param size size of matrix
 */
void populate_matrix(int *matrix, int size){
  //use openmp to speed up population:
  int i,tid;
  omp_set_num_threads(16);
  #pragma omp parallel shared(matrix,size) private(i,tid)
  {
    tid = omp_get_thread_num();
    #pragma omp for
    for(i=0;i<size;i++)
      matrix[i]=rand_int(tid); 
  }
}

/**
 * write to file function
 * writes the input to file: output.txt
 * @param input
 */
void write_to_file(char* filename,int *input, int size){
  FILE *fd=fopen(filename,"w");
  int i;
  for(i=0;i<size;i++){
    fprintf(fd,"%d ",input[i]);
  }
  fclose(fd);
}

/**
 * the matrix multiplication method
 * NOTE: we are assuming that matrix2 is already transposed. i.e., the function
 * will use the rows of matrix2 in global memory as if they were the columns of
 * the second matrix being multiplied.
 * @param output
 */
void * matrix_mult(matrix_mult_struct * input){
  //get the matrices from the global mem:
  int * output=input->output;
  uint8_t *print_current_indices=input->print_current_indices;
  uint8_t *stop=input->stop;
  uint8_t *alive=input->alive;
  int i,j,k;
  while(*alive){
    for(i=0;i<DIM;i++){
      for(j=0;j<DIM;j++){
        int sum=0;
        for(k=0;k<DIM;k++){
          while(*stop && (*(input->tofile)==0) && *alive){
            usleep(500);
          }
          sum+=(matrix1[i*DIM+k]*matrix2[j*DIM+k]);
          /*
           * if another thread has set print_current_indices to non-zero,
           * print current indices
           * and then change that variable to 0
           */
          if(*print_current_indices){
            printf("%d, %d, %d\n", i,j,k);
            *print_current_indices=0;
            *stop=1;
          }
          if(*alive==0){
            return;
          }
        }
        output[i*DIM+j]=sum;
      }
    }
    if(*(input->tofile)){
      printw("outputing file\n");
      //call write to file and exit:
      write_to_file("output.txt",output,DIM*DIM);
      *(input->alive)=0;
      return;
    }
  }
}
