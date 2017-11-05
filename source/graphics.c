#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "graphics.h"

int start_graphics(){
  initscr();
  if(has_colors() == FALSE){
    endwin();
    printf("Your terminal does not support color\n");
    return 1;
  }
  start_color();
  noecho();
  raw();
  curs_set(0);
  return 0;
}

int end_graphics(){
  echo();
  noraw();
  curs_set(1);
  endwin();
  return 0;
}

void prints(char * s){
  char c;
  while((c=*(s++))){
    addch(c);
  }
}

int graphics_main(){
  if(start_graphics())
    return 1;
  /*init_color(COLOR_RED, 184, 142, 12);
    init_color(COLOR_GREEN, 78, 154, 6);*/
  
  /*init_color(COLOR_BLUE, 78, 154, 6);*/
  /*init_pair(colors_display, COLOR_BLACK, COLOR_GREEN);
  init_pair(colors_input, COLOR_BLACK, COLOR_YELLOW);
  init_pair(colors_prompt, COLOR_BLACK, COLOR_WHITE);*/
  /*scrollok(stdscr, TRUE);*/
  /*win = newwin(0,0,LINES,COLS);*/
  
  //keypad(stdscr, TRUE);
  //
  erase();
  move(0,0);
  prints("hello!");
  refresh();
  sleep(1);
  
  //nodelay(stdscr, TRUE);
  //resize(0);
  end_graphics();
  printf("hi\n");

  return 0;
}
