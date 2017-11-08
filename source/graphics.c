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
  keypad(stdscr, TRUE);
  colors = init_colors(COLOR_MAX);
  init_pair(colors[0], COLOR_YELLOW, COLOR_BLACK);
  init_pair(colors[1], COLOR_RED, COLOR_BLACK);
  init_pair(colors[2], COLOR_BLUE, COLOR_BLACK);
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

int printns(char * s, int n){
  char c;
  while(n && (c=*(s++))){
    addch(c);
    --n;
  }
  return n;
}

flavor * make_flavor(short cpair, char * text, flavor * next){
  flavor * f = (flavor *)malloc(sizeof(flavor));
  f->cpair = cpair;
  f->text = text;
  f->next = next;
  return f;
}

flavor * last_flavor(flavor * f){
  flavor * next = f->next;
  while(next != NULL){
    f = next;
    next = f->next;
  }
  return f;
}

void free_flavor(flavor * f){
  flavor * next;
  while(f != NULL){
    next = f->next;
    free(f->text);
    free(f);
    f = next;
  }
}

//avoiding posix
char * strdup (const char *s) {
  int len;
  char *d;
  if (s == NULL) return NULL;
  len = strlen (s) + 1;
  d = malloc(len);
  strcpy(d, s);
  d[len - 1] = 0;
  return d;
}

void printcs(flavor * f){
  while(f != NULL){
    attron(COLOR_PAIR(f->cpair));
    prints(f->text);
    attroff(COLOR_PAIR(f->cpair));
    f = f->next;
  }
}

int printncs(flavor * f, int n){
  if(n < 0)
    n = 0;
  while(n && f != NULL){
    attron(COLOR_PAIR(f->cpair));
    n = printns(f->text, n);
    attroff(COLOR_PAIR(f->cpair));
    f = f->next;
  }
  return n;
}

short * init_colors(short len){
  short * colors = (short *)malloc(sizeof(short) * len);
  for(short i = 0; i < len; ++i){
    colors[i] = i + 1;
  }
  return colors;
}

void redraw(){

}

int input_loop(){
  int c;
  key_fn f;
  c = getch();
  if(c < 0 || c > KEY_MAP_SIZE)
    c = 0;
  f = key_map[c]; 
  if(f(c))
    return 1;
  return 0;
}

int graphics_main(){
  if(start_graphics())
    return 1;
  bind_keys();
  key_resize(410);
  
  erase();
  move(0,0);
  flavor *test = make_flavor(colors[0], strdup("hello "), make_flavor(colors[1], strdup("nice (very) (ultra) (super) "), make_flavor(colors[2], strdup("day!"), NULL)));
  printncs(test, 20);
  free_flavor(test);
  while(!input_loop());
  refresh();

  end_graphics();

  return 0;
}
