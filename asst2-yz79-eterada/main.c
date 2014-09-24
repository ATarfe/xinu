/*
 * Assignment 2
 *
 * Author: Peter Zhang (yz79), Eriya Terada (eterada)
 * CSCI P536 FA14 ASST0
 * Sept 23 2014
 * main.c file
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include "matmult.h"

//
// A struct shared between main and worker thread so that
// worker thread can get orders from main thread.
//
matrix_mult_struct m_struct;
/**
 * reads input from the file "sharedfile.txt"
 * and sends the input stream to the "worker" function
 */
void *read_from_file(matrix_mult_struct * mstruct){
  //open sharedfile.txt
  uint8_t running=1;
  while(running && *mstruct->alive){
      sleep(1);
      printw("file\n");
      refresh();
      FILE *fd=fopen("sharedfile.txt","a+");
      char buf[2048];
      fscanf(fd, "%s",buf);
      int i;
      fclose(fd);
      for(i=0;i<strlen(buf);i++){
        int input=buf[i];
        if (input == 'z' || input == 'Z'){
          printw("Calculate curent multiplication, save, and quit\n");
          *mstruct->tofile = 1; // Set tofile flag in m_struct to 1
          running=0;
        }
        else if(input == 'q' || input == 'Q'){
          *mstruct->alive = 0;
          running=0;
        }
        else{
          if (input == 's' || input == 'S'){
            //*m_struct.print_current_indices = 1; // set stop flag in m_struct to 1
            *mstruct->stop = 1; // set stop flag in m_struct to 1
            printw("\n%d, %d, %d\n", idx1,idx2,idx3);
          }
          
          // If input is 't' or 'T', the program will continue multiplying matrices
          if (input == 't' || input == 'T'){
            *mstruct->stop = 0; // set stop flag in m_struct to 0, i.e. continue calculation
          }
        }
      }
  }
}

/*
 * main() -> int
 *
 * The main function. Initializes curses for character input, and then
 * calls worker repeatedly until the user enters 'q' or 'Q'
 *
 */
int main(){
  // Allocate memory for stuff in m_struct
  m_struct.output = malloc(DIM*DIM*4);
  m_struct.print_current_indices = malloc(sizeof(uint8_t));
  m_struct.stop = malloc(sizeof(uint8_t));
  m_struct.alive = malloc(sizeof(uint8_t));
  m_struct.tofile = malloc(sizeof(uint8_t));
  
  // Initialize values in m_struct
  *m_struct.print_current_indices = 0;
  *m_struct.stop = 0;
  *m_struct.alive = 1;
  *m_struct.tofile = 0;
  
  // Fill 2 matrices with numbers
  populate_matrix(matrix1, DIM*DIM);
  populate_matrix(matrix2, DIM*DIM);
  
  // Create thread
  pthread_t thread;
  pthread_create(&thread, NULL, (void*)matrix_mult, (void*)(&m_struct));

  pthread_t fileio;
  pthread_create(&fileio, NULL, (void*)&read_from_file,(void*)(&m_struct));
  
  //first, initialize curses
  WINDOW * default_win=initscr();
  scrollok(default_win,TRUE);
  
  // Initially input is just 0
  int input = 0;
  uint8_t running=1;
  
  // Do worker while input is not 'q' or 'Q'
  while(running){
    input=getch();
    // If input is 'z' or 'Z', complete current matrix-multiply,
    // save its results to FILE and terminate.
    if (input == 'z' || input == 'Z'){
      printw("Calculate curent multiplication, save, and quit\n");
      *m_struct.tofile = 1; // Set tofile flag in m_struct to 1
      running=0;
    }
    else if(input == 'q' || input == 'Q'){
      *m_struct.alive = 0;
      running=0;
    }
    else{
      if (input == 's' || input == 'S'){
        //*m_struct.print_current_indices = 1; // set stop flag in m_struct to 1
        *m_struct.stop = 1; // set stop flag in m_struct to 1
        printw("\n%d, %d, %d\n", idx1,idx2,idx3);
      }
      
      // If input is 't' or 'T', the program will continue multiplying matrices
      if (input == 't' || input == 'T'){
        *m_struct.stop = 0; // set stop flag in m_struct to 0, i.e. continue calculation
      }
    }
  }
  
  printw("broken\n");

  // Join threads
  pthread_join(thread, NULL);
  pthread_join(fileio, NULL);
  
  // end curses window
  endwin();
  
  // Free stuff!!!
  free(m_struct.output);
  free(m_struct.print_current_indices);
  free(m_struct.stop);
  free(m_struct.alive);
  free(m_struct.tofile);
  
  return 0;
}
