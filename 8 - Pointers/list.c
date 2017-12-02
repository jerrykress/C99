/*Last modified: 12:24, 22 Nov*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#define RED "\x1B[31m"
#define NRM "\x1B[0m"
#define GRN "\x1B[32m"
#define BLU "\x1B[34m"

//Define node structure;
struct node{
  struct node* previous;
  int value;
  struct node* next;
};

//Define list structure;
struct list{
  struct node* start;
  struct node* current;
  struct node* end;
  struct node n1, n2, n3;
};

//Allocate memory for new list;
struct list* newList() {
  struct list *newList = malloc(sizeof(struct list));
  newList -> start = NULL;
  newList -> current = newList -> start;
  newList -> end = NULL;
  return newList;
}

//Allocate memory for new node;
struct node* newNode() {
  struct node *newNode = malloc(sizeof(struct node));
  newNode -> previous = NULL;
  newNode -> next = NULL;
  return newNode;
}

void start(struct list *l){
  l -> current = l -> start;
}

void end(struct list *l){
  l -> current = l -> end;
}

bool atStart(struct list *l){
  if(l -> current -> previous == NULL) return true;
    else return false;
}

bool atEnd(struct list *l){
  if(l -> current -> next  == NULL) return true;
    else return false;
}

void forward(struct list *l) {
  if(atEnd(l) == true){
    printf("Already at the end of the list\n");
  }
  else{
    l -> current = l -> current -> next;
  }
}


void backward(struct list *l) {
  if(atStart(l) == true){
    printf("Already at the beginning of the list\n");
  }
  else{
    l -> current = l -> current -> next;
  }
}

void insertNew(struct list *l, int x){
  struct node* first = newNode();
  first -> value = x;
  l -> start = first;
  l -> current = first;
  l -> end = first;
  first -> previous = NULL;
  first -> next = NULL;
}

void insertBefore(struct list *l, int x){
  struct node* new = newNode();
  new -> value = x;
  new -> next = l -> current;
  l -> current -> previous = new;
}

void insertAfter(struct list *l, int x){
  struct node* new = newNode();
  new -> value = x;
  new -> previous = l -> current;
  l -> current -> next = new;
}

int getBefore(struct list* l){
  int before = 0;
  if(atStart(l) == true){
    printf("No element before current position\n");
  }
  else{before = l -> current -> previous -> value;}
  return before;
}

int getAfter(struct list* l){
  int after = 0;
  if(atEnd(l) == true){
    printf("No element after current position\n");
  }
  else{after = l -> current -> next -> value;}
  return after;
}

void setBefore(struct list* l, int x){
  if(atStart(l) == true){
    printf("No element before current position\n");
  }
  else{l -> current -> previous -> value = x;}
}

void setAfter(struct list* l, int x){
  if(atEnd(l) == true){
    printf("No element after current position\n");
  }
  else{l -> current -> next -> value = x;}
}

void deleteBefore(struct list* l){
  if(atStart(l) == true){
    printf("No element before,deleting current position.\n");
    l -> current = l -> current -> next;
    l -> current -> previous = NULL;
  }
  else{
    l -> current -> previous = l -> current -> previous -> previous;
    l -> current -> previous -> next = l -> current;
  }
}

void deleteAfter(struct list* l){
  if(atEnd(l) == true){
    printf("No element after,deleting current position.\n");
    l -> current = l -> current -> previous;
    l -> current -> next = NULL;
  }
  else{
    l -> current -> next = l -> current -> next -> next;
    l -> current -> next -> previous = l -> current;
  }
}


//=============tests=============================================================================================
void test_StartEnd(){
  printf("\nStarting test_StartEnd\n-----------------\n");
  struct list* t = newList();
  struct node* x = newNode();
  x -> value = 1;
  t -> current = x;
  t -> start = x;
  t -> end = x;
  printf("test_StartEnd: 1st node setup OK\n");
  struct node* x2 = newNode();
  x2 -> value = 2;
  x2 -> previous = x;
  x -> next = x2;
  printf("test_StartEnd: 2nd node setup OK\n");
  assert(atStart(t));
  t -> current = t -> current -> next;
  assert(atEnd(t));
  free(t);
  free(x);
}

void test_insertNew(){
  printf("\nStarting test_insertNew\n-----------------\n");
  struct list* t = newList();
  struct node* x = newNode();
  assert(x -> previous == NULL);
  assert(x -> next == NULL);
  free(t);
  free(x);
}

void test_insertBefore(){
  printf("\nStarting test_insertBefore\n-----------------\n");
  struct list* t = newList();
  struct node* x = newNode();
    x->value = 1;
    t->start = x;
    t->current = x;
    t->end = x;
    printf("test_insertBefore: List pointers setup OK\n");

    for (int i = 1; i < 10; i++) {
      insertBefore(t,i);
      assert(t->current->previous->value==i);
      printf("test_insertBefore: Test loop when insert value = %d OK\n", i);
    }
    free(t);
    free(x);
}

void test_insertAfter(){
  printf("\nStarting test_insertAfter\n-----------------\n");
  struct list* t = newList();
  struct node* x = newNode();
    x->value = 1;
    t->start = x;
    t->current = x;
    t->end = x;
    printf("test_insertAfter: List pointers setup OK\n");

    for (int i = 1; i < 10; i++) {
      insertAfter(t,i);
      assert(t->current->next->value==i);
      printf("test_insertAfter: Test loop when insert value = %d OK\n", i);
    }
    free(t);
    free(x);
}

void test_get(){
  printf("\nStarting test_get\n-----------------\n");
  struct list* t = newList();
  struct node* x1 = newNode();
  struct node* x2 = newNode();
  struct node* x3 = newNode();
    x1 -> next = x2; //Setup linked lists;
    x2 -> next = x3;
    x2 -> previous = x1;
    x3 -> previous = x2;
    x1 -> value = 1;
    x2 -> value = 2;
    x3 -> value = 3;
    t -> current = x2;
    printf("test_get: Linked list setup OK\n");
    for(int i = 0; i < 10; i++){ //testing 1 - 9;
      x1 -> value = i;
      x2 -> value = i + 1;
      x3 -> value = i + 2;
      printf("test_get: Test loop at current value = %d OK\n", i);
      assert(getBefore(t) == i);
      assert(getAfter(t) == i + 2);
    }
    free(t);
    free(x1);
    free(x2);
    free(x3);
}


void test_delete(){
  struct list* t = newList();
  struct node* x1 = newNode();
  struct node* x2 = newNode();
  struct node* x3 = newNode();

  x1 -> next = x2; //Setup linked lists;
  x2 -> next = x3;
  x2 -> previous = x1;
  x3 -> previous = x2;
  x1 -> value = 1;
  x2 -> value = 2;
  x3 -> value = 3;
  printf("test_delete: Linked list setup OK\n");
  t -> current = x3;
  deleteBefore(t);
  assert(t -> current -> previous -> value == 1);
  printf("test_delete: Testing deleteBefore when current position == end OK\n");

  x1 -> next = x2; //Setup linked lists;
  x2 -> next = x3;
  x2 -> previous = x1;
  x3 -> previous = x2;
  printf("Linked list restored\n");
  t -> current = x1;
  printf("Current pointer reset to start\n");
  deleteBefore(t);
  assert(t -> current -> value == 2);
  printf("test_delete: Testing deleteBefore when current position == start OK\n");

  x1 -> next = x2; //Setup linked lists;
  x2 -> next = x3;
  x2 -> previous = x1;
  x3 -> previous = x2;
  printf("Linked list restored\n");
  t -> current = x1;
  printf("Current pointer reset to start\n");
  deleteAfter(t);
  assert(t -> current -> next -> value == 3);
  printf("test_delete: Testing deleteAfter when current position == start OK\n");

  x1 -> next = x2; //Setup linked lists;
  x2 -> next = x3;
  x2 -> previous = x1;
  x3 -> previous = x2;
  printf("Linked list restored\n");
  t -> current = x3;
  printf("Current pointer reset to end\n");
  deleteAfter(t);
  assert(t -> current -> value == 2);
  printf("test_delete: Testing deleteAfter when current position == end OK\n");
  free(t);
  free(x1);
  free(x2);
  free(x3);
}

void test() {
    test_StartEnd();
    printf(GRN "test_StartEnd Passed\n\n" NRM);
    test_insertNew();
    printf(GRN "test_insertNew Passed\n\n" NRM);
    test_insertBefore();
    printf(GRN "test_insertBefore Passed\n\n" NRM);
    test_insertAfter();
    printf(GRN "test_insertAfter Passed\n\n" NRM);
    test_get();
    printf(GRN "test_get Passed\n\n" NRM);
    test_delete();
    printf(GRN "test_delete Passed\n\n" NRM);
    printf(GRN "\n----------------\nAll tests passed.\n" NRM);
}


int main(int n, char *args[n]) {
    if (n == 1) test();

    return 0;
}
