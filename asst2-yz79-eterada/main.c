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


int worker(char input){
  
  printw("Calculating matrices...\n");
  
  if (input == 'z'){
    printw("Calculate curent multiplication, save, and quit\n");
    /* TO-DO: write to file */
    endwin();
    return 0;
  }
  
  if (input == 's'){
    printw("\nCalculation stopped.\n");
    input = getch();
  }
  
  if (input == 't'){
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
