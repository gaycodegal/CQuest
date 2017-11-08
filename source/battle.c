#include "battle.h"

statbar * make_statbar(char * sym, char * delim, int score, int base){
  statbar * bar = (statbar *)malloc(sizeof(statbar));
  flavor * fsym = make_flavor(0, sym, NULL);
  char *cscore = (char *)malloc(11*sizeof(char)), *cbase = (char *)malloc(11*sizeof(char));
  flavor * fbase = make_flavor(0, cbase, NULL);
  flavor * fscore = make_flavor(0, cscore, NULL);
  flavor * fdelim = make_flavor(0, delim, NULL);
  bar->ftotal = fsym;
  bar->fsym = fsym;
  bar->fscore = fscore;
  bar->fdelim = fdelim;
  bar->fbase = fbase;
  last_flavor(bar->fsym)->next = fscore;
  last_flavor(bar->fscore)->next = fdelim;
  last_flavor(bar->fdelim)->next = fbase;
  bar->score = score;
  bar->base = base;
  statbar_set(bar, score, base);
  return bar;
}

void statbar_set(statbar *b, int score, int base){
  snprintf(b->fscore->text, 10, "%i", score);
  snprintf(b->fbase->text, 10, "%i", base);
}

void draw_statbar(int x, int y, statbar * bar){
  move(y, x);
  printncs(bar->ftotal, MAX_X - x);
}

void *free_statbar(void *bar){
  free_flavor(((statbar *)bar)->ftotal);
  free(bar);
  return NULL;
}

healthbar * make_healthbar(int health, int length){
  healthbar * hbar = (healthbar *)malloc(sizeof(healthbar));
  char * bar;
  char c = '/';
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
  hbar->bar = make_flavor(0, bar, make_flavor(0, strdup("]"), NULL));
  hbar->display = make_flavor(0, strdup("["), hbar->bar);
  hbar->health = health;
  hbar->value = health;
  return hbar;
}

short health_color(float value, float max){
  float v = value/max;
  if(v > 0.5 && v <= 0.75){
    return COLOR_MID_M;
  }else if(v <= 0.5){
    return COLOR_LOW_M;
  }else{
    return COLOR_GOOD_M;
  }
}

void set_health(healthbar * bar, int value){
  int i, s, e = bar->length;
  char c = bar->c;
  char * text = bar->bar->text;
  s = bar->value*e/bar->health;
  if(s == 0 && bar->value != 0) s = 1;
  for(i = s; i < e; ++i){
    text[i] = c;
  }
  s = value*e/bar->health;
  if(s == 0 && value != 0) s = 1;
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
  move(y, x);
  printncs(bar->display, MAX_X - x);
}

void draw_monster(int x, int y, monster *m){
  int n;
  move(y, x);
  n = MAX_X - x;
  node * t = m->stats->head;
  while(n && t != NULL){
    n = printncs(((statbar *)t->data)->ftotal, n);
    n = printns("   ", n);
    t = t->next;
  }
  draw_healthbar(x + 2, y + 1, m->bar);
}

stat *make_stat(int v, int m){
  stat *s = NEW(stat);
  s->value = v;
  s->max = m;
  return s;
}

monster *make_monster(stat *health, stat *attack){
  monster *m = NEW(monster);
  statbar *hp = make_statbar(strdup("HP: "), strdup(" / "), health->value, health->max);
  statbar *atk = make_statbar(strdup("ATK: "), strdup(" - "), attack->value, attack->max);
  m->stats = make_list();
  append_elem(hp, m->stats);
  append_elem(atk, m->stats);
  m->health = health;
  m->attack = attack;
  m->hp = hp;
  m->atk = atk;
  m->bar = make_healthbar(health->max, 30);
  set_monster_health(m, health->value);
  return m;
}

void statbar_color(statbar *s, short cval, short cbase){
  s->fscore->cpair = cval;
  s->fbase->cpair = cbase;
}

void set_monster_health(monster *m, int value){
  short c = health_color(value, m->health->max);
  m->bar->bar->cpair = c;
  statbar_color(m->hp, c, c);
  m->health->value = value;
  set_health(m->bar, value);
  statbar_set(m->hp, value, m->health->max);
}

void *free_monster(void *mons){
  monster *m = (monster *)mons;
  static_map_list(m->stats, &free_statbar);
  free_list(m->stats);
  free(m->health);
  free(m->attack);
  free_healthbar(m->bar);
  free(m);
  return NULL;
}

float frand(){
  return (float)rand()/((float)RAND_MAX);
}

int attack1(int c){
  int v = fighting->health->value;
  float f = (frand() * (float)(player->attack->max - player->attack->value) + player->attack->value);
  v -= (int)f;
  
  if (v < 0) v = 0;
  set_monster_health(fighting, v);
  draw_monster(0, 0, fighting);
  return 0; 
}

void battle_keys(){
  key_map[49] = &attack1;
}

int battle_main(){
  srand((unsigned int)time(NULL));
  if(start_graphics())
    return 1;
  bind_keys();
  battle_keys();
  key_resize(410);

  monster *m = make_monster(make_stat(100, 100), make_stat(1, 5));
  fighting = m;
  player = m;
  
  erase();
  move(0,0);
  draw_monster(0, 0, m);  

  while(!input_loop());
  refresh();

  end_graphics();
  free_monster(m);

  return 0;
}
