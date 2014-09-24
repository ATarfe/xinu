/*
 * Assignment 2
 *
 * Author: Peter Zhang (yz79), Eriya Terada (eterada)
 * CSCI P536 FA14 ASST0
 * Sept 23 2014
 * matmult.h file
 * header of methods to initialize and multiply matrices
 */

#include <stdint.h>
#define DIM 32 

typedef struct{
  int * output;
  uint8_t *print_current_indices;
  uint8_t *stop; //boolean: stop (pause)
  uint8_t *alive;//boolean: process is currently alive
  uint8_t *tofile; //boolean: write result to file
}matrix_mult_struct;

int matrix1[DIM*DIM];
int matrix2[DIM*DIM];
int idx1,idx2,idx3;
void populate_matrix(int *matrix, int size);
void * matrix_mult (matrix_mult_struct * input);
