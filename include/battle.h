#ifndef BATTLE_H
#define BATTLE_H

#include "graphics.h"

typedef struct s_healthbar {
  char c;
  int health;
  int value;
  short length;
  flavor * display;
  flavor * bar;
} healthbar;

void set_health(healthbar * bar, int value);
int battle_main();

#endif
