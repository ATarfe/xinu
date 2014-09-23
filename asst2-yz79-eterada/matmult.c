#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

#define DIM 2 
int matrix1[DIM*DIM];
int matrix2[DIM*DIM];

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
  return (rand_r(&seed) % 2000 -1000);
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
 * the matrix multiplication method
 * NOTE: we are assuming that matrix2 is already transposed. i.e., the function
 * will use the rows of matrix2 in global memory as if they were the columns of
 * the second matrix being multiplied.
 * @param output
 */
void matrix_mult(int * output){
  //get the matrices from the global mem:
  int i,j,k;
  for(i=0;i<DIM;i++){
    for(j=0;j<DIM;j++){
      int sum=0;
      for(k=0;k<DIM;k++){
        sum+=(matrix1[i*DIM+k]*matrix2[j*DIM+k]);
      }
      output[i*DIM+j]=sum;
    }
  }
}

int main(){
  populate_matrix(matrix1,DIM*DIM);
  populate_matrix(matrix2,DIM*DIM);
  int i,j;
  for(i=0;i<DIM*DIM;i++)
    printf("%d ",matrix1[i]);
  for(i=0;i<DIM*DIM;i++)
    printf("%d ",matrix2[i]);
  printf("\n");
  int *da=malloc(16);
  matrix_mult(da);
  for(i=0;i<DIM*DIM;i++)
    printf("%d ",da[i]);
  free(da);
  return 0;
}
