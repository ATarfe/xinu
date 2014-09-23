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
