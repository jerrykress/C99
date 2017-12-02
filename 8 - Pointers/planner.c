#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#define RED "\x1B[31m" //Define colors;
#define NRM "\x1B[0m"
#define GRN "\x1B[32m"
#define BLU "\x1B[34m"
#define YEL "\x1B[33m"
#define clear() printf("\033[H\033[J") //Define clear screen command;

//Define single event structure;
struct event{
  struct event* previous;
  char* name;
  struct event* next;
};

//Define day structure;
struct day{
  struct event* start;
  struct event* current;
  struct event* end;
  struct event n1, n2, n3;
};

//Create a new day;
struct day* newDay() {
  struct day* newDay = malloc(sizeof(struct day));
  //Initialize day pointers;
  newDay -> start = NULL;
  newDay -> end = NULL;
  newDay -> current = newDay -> start;
  return newDay;
}

//Create a new event;
struct event* newEvent(char *s) {
  struct event* newEvent = (struct event*) malloc(sizeof(struct event) + 256);
  //Initialize event pointers;
  newEvent -> previous = NULL;
  newEvent -> next = NULL;
  //Name new event;
  newEvent -> name = malloc(50* sizeof(char)); //Input passed through pointers (tmp -> x -> s). However the momory of name have not yet been Initialized;
  strcpy(newEvent -> name, s);
  return newEvent;
}

//Set selection to the first event;
void start(struct event* e){
  //Loop start pointer to the beginning;
  while(e -> previous != NULL){
    e = e -> previous;
  }
}

//Set selection to the last event;
void end(struct event* e){
  //Loop end pointer to the last;
  while(e -> next != NULL){
    e = e -> next;
  }
}

//Find if selection is at start;
bool atStart(struct day *l){
  if(l -> current -> previous == NULL) return true;
    else return false;
}

//Find if selection is at end;
bool atEnd(struct day *l){
  if(l -> current -> next  == NULL) return true;
    else return false;
}

//Select previous event;
void previous(struct day* l){
  if(atStart(l) == true){
    printf(RED "Current selection is already the first event\n" NRM);
  }
  else{
    l -> current = l -> current -> previous;
  }
}

// Select next event;
void next(struct day* l){
  if(atEnd(l) == true){
    printf(RED "Current selection is already the last event\n" NRM);
  }
  else{
    l -> current = l -> current -> next;
  }
}

void insertNew(struct day* l, char* x){
  struct event* new = newEvent(x);
  //Reset day pointers;
  l -> start = new;
  l -> current = new;
  l -> end = new;
}

void insertBefore(struct day* l, char* x){
  //printf("iA %p %p\n", l -> current, l -> start);
  struct event* new = newEvent(x);
  if (atStart(l))
  {
    //printf("iE\n");
    l -> start = new;
    //printf("iF %p %p\n", l -> current, l -> start);
    new -> next = l -> current;
    l -> current -> previous = new;
  }

  else{
  //Reassign direction pointers
  //printf("iB %p\n", l->current);
  new -> next = l -> current;
  new -> previous = l -> current -> previous;
  //printf("iC %p\n", l->current);
  l -> current -> previous -> next = new;
  l -> current -> previous = new;
  //printf("iD %p\n", l -> current);
  }
  l -> current = l -> current -> previous; //auto advance current pointer
}

void insertAfter(struct day* l, char* x){
  //printf("IA %p %p\n", l -> current, l -> start);
  struct event* new = newEvent(x);
  if (atEnd(l))
  {
    //printf("IE\n");
    l -> end = new;
    //printf("IF current:%p start:%p\n", l -> current, l -> start);
    new -> previous = l -> current;
    l -> current -> next = new;
  }

  else{
  //Reassign direction pointers
  //printf("IB %p\n", l->current);
  new -> previous = l -> current;
  new -> next = l -> current -> next;
  //printf("IC %p\n", l->current);
  l -> current -> next -> previous = new;
  l -> current -> next = new;
  //printf("ID %p\n", l -> current);
  }
  l -> current = l -> current -> next; //auto advance current pointer
}

void deleteCurrent(struct day* l){
  struct event* del_tmp = l -> current;
  if(atStart(l) == true){
    l -> current = l -> current -> next;
    l -> start = l -> current;
    //printf("dA %p\n", l -> current);
    l -> current -> previous = NULL;
    //printf("dB %p\n", l -> current);
  }
  else if(atEnd(l) == true){
    l -> current = l -> current -> previous;
    l -> end = l -> current;
    l -> current -> next = NULL;
  }
  else{
    l -> current -> previous -> next = l -> current -> next;
    l -> current -> next -> previous = l -> current -> previous;
    l -> current = l -> current -> previous;
  }
  free(del_tmp);
}


struct event* tmp_printPtr(struct event* e){
  struct event* tmp;
  tmp = e;
  return tmp;
  //printf("Duplicated current pointer: %p\n", e);
}

void display(struct day* l){
  struct event* printPtr = tmp_printPtr(l -> start);
  //start(printPtr);
  printf("\nYour calendar for today:\n--------------------\n");
  int count = 1;
  //printf("dA %p %p %p\n", l -> current, l -> start, printPtr);


  for(count = 1; printPtr != NULL; count++)
  {
      char* print_buffer = malloc(50 * sizeof(char));
      strcpy(print_buffer, printPtr -> name);
      printf("%d.%s\n",count, print_buffer);
      printPtr = printPtr -> next;
  }
  printf(GRN "Current selection: %s\n" NRM, l -> current -> name);
}



void help(){
  printf(YEL "\n====================== Manual ======================\n\n");
  printf("---------DayPlanner by Jerry Shengjing Wang---------\n\n");
  printf("1.ADD BEFORE: Add an event before the current selection\n");
  printf("2.ADD AFTER: Add an event after the current selection\n");
  printf("3.SELECT UP: Move the current selection to the previous event\n");
  printf("4.SELECT DOWN: Move the current selection to the next event\n");
  printf("5.GO TO TOP: Move the current selection to the first event\n");
  printf("6.GO TO BOTTOM: Move the current selection to the last event\n");
  printf("7.REMOVE: Delete the current event\n");
  printf("8.HELP: Show manual\n\n");
  printf(">> Enter 9 to exit\n\n" NRM);
}

void autotest(){

}

int main(int n, char *args[n]) {
  if (n == 1) autotest();

  clear();
  int opt = 0;
  struct day* currentDay = newDay(); //Auto create new day, all pointers NULL;
  //Ask to create the first event;
  printf("\nCreate the first event of the day:");
  char* tmp = malloc(50 * sizeof(char)); //Allocate memory for input;
  scanf("%s", tmp);
  insertNew(currentDay, tmp);
  clear();
  display(currentDay);
  //start(currentDay);


  do{
    //Display function here;
    printf("\n\n---------------------------------------------------------------\n1. ADD BEFORE\t 2. ADD AFTER\t   3. SELECT UP\t 4. SELECT DOWN\n");
    printf("5. GO TO TOP\t 6. GO TO BOTTOM   7. REMOVE\t 8. HELP/EXIT \n---------------------------------------------------------------\n\nEnter the choice :: ");
    scanf("%d", &opt);
    switch (opt) {
      case 1:
          printf("Enter the event to be inserted before current selection:: ");
          scanf("%s", tmp);
          //printf("mA %p %p\n", currentDay->current, currentDay -> start);
          insertBefore(currentDay, tmp);
          //currentDay -> start = currentDay -> start -> previous;
          //printf("mB %p %p\n", currentDay->current, currentDay -> start);
          clear();
          display(currentDay);
          //printf("mC %p %p\n", currentDay->current, currentDay -> start);
          break;

      case 2:
          printf("Enter the event to be inserted after current selection:: ");
          scanf("%s", tmp);
          insertAfter(currentDay, tmp);
          clear();
          display(currentDay);
          break;

      case 3:
          clear();
          printf(BLU "Changing selection...\n" NRM);
          previous(currentDay);
          display(currentDay);
          break;

      case 4:
          clear();
          printf(BLU "Changing selection...\n" NRM);
          next(currentDay);
          display(currentDay);
          break;

      case 5:
          clear();
          printf(BLU "Changing selection...\n" NRM);
          currentDay -> current = currentDay -> start;
          display(currentDay);
          break;

      case 6:
          clear();
          printf(BLU "Changing selection...\n" NRM);
          currentDay -> current = currentDay -> end;
          display(currentDay);
          break;

      case 7:
          clear();
          printf("Deleting current selection...\n");
          if(currentDay -> current -> previous == NULL && currentDay -> current -> next == NULL){
            printf(RED "Cannot delete the last event on the list\n" NRM);
          }
          else{
            deleteCurrent(currentDay);
            clear();
            display(currentDay);
          }
          break;

      case 8:
            help();
          break;
    }
  }
  while(opt < 9);

printf("\n\nExiting...\n\n\n");

    return 0;
}
