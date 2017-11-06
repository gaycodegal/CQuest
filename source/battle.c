#include "battle.h"

healthbar * make_healthbar(int health, int length){
  healthbar * hbar = (healthbar *)malloc(sizeof(healthbar));
  char * bar;
  char c = ':';
  int i;
  --length;
  bar = (char *)malloc(sizeof(char) * length);
  --length;
  hbar->c = c;
  hbar->length = length;
  bar[length] = 0;
  for(i = 0; i < length; ++i){
    bar[i] = c;
  }
  hbar->bar = make_flavor(COLOR_GOOD_M, bar, make_flavor(0, strdup("]"), NULL));
  hbar->display = make_flavor(0, strdup("["), hbar->bar);
  hbar->health = health;
  hbar->value = health;
  return hbar;
}

void set_health(healthbar * bar, int value){
  int i, s, e = bar->length;
  char c = bar->c;
  char * text = bar->bar->text;
  float v = (float)value/(float)(bar->health);
  if(v > 0.5 && v <= 0.75){
    bar->bar->cpair = COLOR_MID_M;
  }else if(v <= 0.5){
    bar->bar->cpair = COLOR_LOW_M;
  }else{
    bar->bar->cpair = COLOR_GOOD_M;
  }
  s = bar->value*e/bar->health;
  for(i = s; i < e; ++i){
    text[i] = c;
  }
  s = value*e/bar->health;
  for(i = s; i < e; ++i){
    text[i] = ' ';
  }
  bar->value = value;
}

void free_healthbar(healthbar * bar){
  free_flavor(bar->display);
  free(bar);
}

void draw_healthbar(int x, int y, healthbar * bar){
  move(x, y);
  printcs(bar->display);
}

int battle_main(){
  if(start_graphics())
    return 1;
  
  erase();
  move(0,0);
  flavor *test = make_flavor(colors[0], strdup("hello "), make_flavor(colors[1], strdup("nice (very) (ultra) (super) "), make_flavor(colors[2], strdup("day!"), NULL)));
  healthbar * bar = make_healthbar(100, 10);
  printncs(test, 20);
  draw_healthbar(1, 10, bar);
  set_health(bar, 25);
  draw_healthbar(2, 10, bar);
  set_health(bar, 70);
  draw_healthbar(3, 10, bar);
  set_health(bar, 100);
  draw_healthbar(4, 10, bar);
  free_healthbar(bar);
  free_flavor(test);
  while(!input_loop());
  refresh();

  end_graphics();

  return 0;
}
