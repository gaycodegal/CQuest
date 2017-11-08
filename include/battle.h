#ifndef BATTLE_H
#define BATTLE_H
#include "util.h"
#include "graphics.h"
#include "hashmap.h"
#include "list.h"

typedef struct s_healthbar {
  char c;
  int health;
  int value;
  short length;
  flavor *display;
  flavor *bar;
} healthbar;

typedef struct s_statbar {
  flavor *fsym, *fscore, *fdelim, *fbase;
  flavor *ftotal;
  int score, base;
} statbar;

typedef struct s_stat {
  int value;
  int max;
} stat;

typedef struct s_monster {
  list *stats;
  healthbar *hpbar;
} monster;

stat *make_stat(int v, int m);
monster *make_monster(stat * health, stat * damage);
void draw_monster(int x, int y, monster *m);
statbar * make_statbar(char *sym, char *delim, int score, int base);
void draw_statbar(int x, int y, statbar *bar);
void *free_statbar(void *bar);
healthbar * make_healthbar(int health, int length);
void set_health(healthbar *bar, int value);
void free_healthbar(healthbar *bar);
void draw_healthbar(int x, int y, healthbar *bar);
int battle_main();

#endif
