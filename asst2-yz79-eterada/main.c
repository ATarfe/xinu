/*
 * Assignment 2
 *
 * Author: Peter Zhang (yz79), Eriya Terada (eterada)
 * CSCI P536 FA14 ASST0
 * Sept 23 2014
 * main.c file
 */

#include <stdio.h>
#include <curses.h>
#include <sys/time.h>
#include <unistd.h>

/*
 * worker(char input) -> int
 *
 * The worker function. Takes as input a character that was passed by
 * main. Unless specified by the input, this function will repeatedly
 * multiply two large matricies.
 *
 */
int worker(char input){
  // Multiply two large matrices
  printw("Calculating matrices...\n");
  
  // If input is 'z' or 'Z', complete current matrix-multiply,
  // save its results to FILE and terminate.
  if (input == 'z' || input == 'Z'){
    printw("Calculate curent multiplication, save, and quit\n");
    /* TO-DO: write to file */
    endwin();
    return 0;
  }
  
  // If input is 's' or 'S', the program will stop multiplying matrices
  if (input == 's' || input == 'S'){
    printw("\nCalculation stopped.\n");
    input = getch();
  }
  
  // If input is 't' or 'T', the program will continue multiplying matrices
  if (input == 't' || input == 'T'){
    printw("\n");
  }
  
  return 0;
}



/**
 * reads input from the file "sharedfile.txt"
 * and sends the input stream to the "worker" function
 */
void read_from_file(){
  //open sharedfile.txt
  FILE *fd=fopen("sharedfile.txt","r");
  char buf[2048];
  fscanf(fd, "%s",buf);
  int i;
  for(i=0;i<strlen(buf);i++){
    worker(buf[i]);
  }
  fclose(fd);
}

/*
 * main() -> int
 *
 * The main function. Initializes curses for character input, and then
 * calls worker repeatedly until the user enters 'q' or 'Q'
 *
 */
int main(){
  
  //first, initialize curses
  WINDOW * default_win=initscr();
  scrollok(default_win,TRUE);
  
  // Initially input is just 0
  int input = 0;
  
  // Do worker while input is not 'q' or 'Q'
  do{
    worker(input);
  }while ((input = getch()) != 'q' && (input != 'Q'));

  endwin();
  return 0;
}
