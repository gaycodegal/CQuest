#ifndef ATTACKS_H
#define ATTACKS_H
#include "util.h"
#include "graphics.h"
#include "list.h"
#include "hashmap.h"
#include "prompt.h"

#include "attacks.h"

typedef struct s_choices {
  list *opts;
  map_t combos;
  prompt *p;
} choices;

choices * make_choices(list *opts);

void *free_choices(void *data);
void draw_choices(int x, int y, void *data);
void printline(int y, char c);
void print_attacks(list * opts, map_t combos);  
int attacks_receiver(const char *buffer);
int attacks_main();

#endif
