// This is a simple implementation of a double linked list for a baremetal
// application.
#include <stdlib.h>

#define ADEPT

#ifndef ADEPT
#include <stdio.h>
#endif

// Structs
typedef struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct {
  unsigned int length;
  Node *head;
  Node *tail;
} List;

// Pointers to List and Nodes
#ifdef ADEPT
unsigned int *LIST_PTR = (unsigned int *)0xdeadbeef;
unsigned int N_LISTS;
unsigned int *NODE_PTR = (unsigned int *)0xbabebabe;
unsigned int N_NODES;
#endif

////////////////////////////////////////////////////////////////////////////////
// List implementation
////////////////////////////////////////////////////////////////////////////////

// Create a new list instance
List *new_list(void) {
#ifdef ADEPT
  List *my_list = (List *)LIST_PTR;
#else
  List *my_list = (List *)malloc(sizeof(List));

  if (my_list == NULL) {
    printf("Failed to allocate memory for list\n");
    exit(1);
  }
#endif

  my_list->length = 0;
  my_list->head = NULL;
  my_list->tail = NULL;

  return my_list;
}

// Append a Node to the end of the list with the specified data.
//
// # Arguments
// * data => data to be stored in the node
void append_node(List *self, int data) {
  Node *prev_tail = self->tail;

#ifdef ADEPT
  self->tail = (Node *)NODE_PTR;
  // Update Node pointer
  N_NODES++;
  NODE_PTR += sizeof(Node);
#else
  self->tail = (Node *)malloc(sizeof(Node));

  if (self->tail == NULL) {
    printf("Failed to allocate memory for node\n");
    exit(1);
  }
#endif

  if (self->length == 0) {
    self->head = self->tail;
    prev_tail = self->tail;
  }

  prev_tail->next = self->tail;
  self->head->prev = self->tail;

  // Initialize Node
  self->tail->prev = prev_tail;
  self->tail->next = self->head;
  self->tail->data = data;

  // Update list length
  self->length++;
}

// Add a Node to the beginning of the list with the specified data.
//
// # Arguments
// * data => data to be stored in the node
void insert_node(List *self, int data) {
  Node *prev_head = self->head;

#ifdef ADEPT
  self->head = (Node *)NODE_PTR;
  // Update Node pointer
  N_NODES++;
  NODE_PTR += sizeof(Node);
#else
  self->head = (Node *)malloc(sizeof(Node));

  if (self->head == NULL) {
    printf("Failed to allocate memory for node\n");
    exit(1);
  }
#endif

  if (self->length == 0) {
    self->tail = self->head;
    prev_head = self->head;
  }

  prev_head->prev = self->head;
  self->tail->next = self->head;

  // Initialize Node
  self->head->prev = self->tail;
  self->head->next = prev_head;
  self->head->data = data;

  // Update list length
  self->length++;
}

// Add every even node and subtract every odd node, travelling through the list
// forward.
//
// # Return Value
// The result of the summation
int op(List *self) {
  Node *tmp = self->head;
  int accumulation = 0;

  for (size_t i = 0; i < self->length; i++) {
    if (i % 2 == 0) {
      accumulation += tmp->data;
    } else {
      accumulation -= tmp->data;
    }

    // Change node
    tmp = tmp->next;
  }

  return accumulation;
}

////////////////////////////////////////////////////////////////////////////////
// Main Function
////////////////////////////////////////////////////////////////////////////////
int main(void) {
  List *my_list = new_list();

  // Add Nodes to the list
  append_node(my_list, 100);
  insert_node(my_list, 150);
  append_node(my_list, 200);
  insert_node(my_list, 69);
  append_node(my_list, 31);
  insert_node(my_list, 12);
  append_node(my_list, 24);

  // List order here is:
  // -> 12 <-> 69 <-> 150 <-> 100 <-> 200 <-> 31 <-> 24 <-
  // \___________________________________________________/
  //
  // Final result is 186.

#ifndef ADEPT
  Node *tmp = my_list->head;

  printf("Print forwards\n");
  for (size_t i = 0; i < my_list->length; i++) {
    printf("Node %zu data is %d\n", i, tmp->data);
    // Change node
    tmp = tmp->next;
  }

  tmp = my_list->tail;

  printf("Print backwards\n");
  for (size_t i = 0; i < my_list->length; i++) {
    printf("Node %zu data is %d\n", i, tmp->data);
    // Change node
    tmp = tmp->prev;
  }

  printf("Accumulation result is %d\n", op(my_list));
#endif

  return op(my_list);
}
