#ifndef _LIST_H_
#define _LIST_H_
#include <stdlib.h>
#include <ncurses.h>
#include "util.h"

typedef struct s_list {
  int length;
  struct s_node *head;
  struct s_node *tail;
} list;

typedef struct s_node {
  void *data;
  struct s_node *prev;
  struct s_node *next;
} node;

/*
  allocates a pointer to an empty list
 */
list *make_list();

list *make_list_from(int n, ...);
  
/*
  Allocates and returns a node with the given element. You may
  create nodes with NULL element.
*/
node *new_node(void*);

void add_node(node*, list*);

void add_elem(void*, list*);

void append_node(node*, list*);

void append_elem(void*, list*);

void *remove_node(node*, list*);

void *remove_last(list*);

void *remove_first(list*);

void empty_list(list*);

void free_list(list*);

void static_map_list(list*, void *(*)(void *));

void *freeAny(void *item);

#endif
