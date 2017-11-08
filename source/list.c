#include "list.h"

list *make_list(){
  list *l = MALLOC(list, 1);
  l->length = 0;
  l->head = NULL;
  l->tail = NULL;
  return l;
}

node *new_node(void *data){
  node *n = MALLOC(node, 1);
  n->data = data;
  n->next = NULL;
  n->prev = NULL;
  return n;
}

void add_node(node *n, list *l){
  node *h;
  if(n == NULL || l == NULL) return;
  ++(l->length);
  h = l->head;
  if(h == NULL){
    l->head = n;
    l->tail = n;
    return;
  }
  h->prev = n;
  n->next = h;
  n->prev = NULL;
  l->head = n;
}

void add_elem(void *e, list *l){
  node *n;
  if(l == NULL) return;
  ++(l->length);
  n = new_node(e);
  add_node(n, l);
}

void append_node(node *n, list *l){
  node *t;
  if(n == NULL || l == NULL) return;
  ++(l->length);
  t = l->tail;
  if(t == NULL){
    l->head = n;
    l->tail = n;
    return;
  }
  t->next = n;
  n->prev = t;
  n->next = NULL;
  l->tail = n;  
}

void append_elem(void *e, list *l){
  node *n;
  if(l == NULL) return;
  ++(l->length);
  n = new_node(e);
  append_node(n, l);
}

void *remove_node(node *n, list *l){
  void *data;
  if(n == NULL)
    return NULL;
  if(l != NULL){
    --(l->length);
    if(n == l->head) return remove_first(l);
    if(n == l->tail) return remove_last(l);
  }  
  if(n->next != NULL)
    n->next->prev = n->prev;
  if(n->prev != NULL)
    n->prev->next = n->next;
  data = n->data;
  free(n);
  return data;
}

void *remove_last(list *l){
  node *n, *t;
  if(l == NULL || l->tail == NULL) return NULL;
  t = l->tail;
  n = t->prev;
  if(n != NULL) n->next = NULL;
  if(l->head == t){
    l->head = NULL;
    l->tail = NULL;
    l->length = 0;
    return remove_node(t, NULL);
  }
  l->tail = n;
  --(l->length);
  return remove_node(t, NULL);
}

void *remove_first(list *l){
  node *n, *h;
  if(l == NULL || l->head == NULL) return NULL;
  h = l->head;
  n = h->next;
  if(n != NULL) n->prev = NULL;
  if(l->tail == h){
    l->head = NULL;
    l->tail = NULL;
    l->length = 0;
    return remove_node(h, NULL);
  }
  l->head = n;
  --(l->length);
  return remove_node(h, NULL);
}

void empty_list(list *l){
  while(l->length)
    remove_first(l);
}

void free_list(list *l){
  while(l->length)
    remove_first(l);
  free(l);
}

void static_map_list(list *l, void *(* map_fn)(void *)){
  node *n = l->head;
  while(n != NULL){
    n->data = map_fn(n->data);
    n = n->next;
  }
}
