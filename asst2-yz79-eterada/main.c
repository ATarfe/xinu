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


int main(){
  
  //first, initialize curses
  WINDOW * default_win=initscr();
  scrollok(default_win,TRUE);
  
  char buffer[10];
  
  printw("=>");
  int input=getch();

  // While program is not told to quit
  while (input != 'q' && input != 'Q'){
    printw("Calculate matrices...\n");
    refresh();
  }
  
  endwin();
  return 0;
}