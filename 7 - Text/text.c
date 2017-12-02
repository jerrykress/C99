/*Done*/
#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

struct text {
    int size;
    char *array;
};

// Create a new text structure, containing a copy of the given string.
// Note that this function is impossible to test fully.
text *new(char *s) {
    text *g = malloc(sizeof(text));
    g -> size = strlen(s) + 1;
    g -> array = malloc((g -> size) * sizeof(char));
    strcpy(g -> array, s);
    return g;
}

// Free up both the space for the struct and the space for the character array.
// Be careful not to access anything after it has been freed.
// Note that this function is imnpossible to test.
void discard(text *t) {
    free(t -> array);
    free(t);
}

int length(text *t) {
    int n = 0;
    n = strlen(t -> array);
    return n;
}

char get(text *t, int i) {
    return(t -> array[i]);
}

void set(text *t, int i, char c) {
    t -> array[i] = c;
}

text *copy(text *t) {
    return new(t -> array);
}

int compare(text *t1, text *t2) {
    int n = strcmp((t1 -> array), (t2 -> array));
    return n;
}

void append(text *t1, text *t2) {
    t1->size = t1->size + t2->size;
    t1 -> array = realloc(t1 -> array, t1->size);
    strcat(t1 -> array, t2 -> array);
}

text *slice(text *t, int i, int j) {
  text *r = malloc(sizeof(text));
  r -> size = t -> size;
  r -> array = malloc((r -> size) * sizeof(char));
  for(int p = 0; p <= j - i; p++) {
    r -> array[p] = t -> array[p + i];
  }
  r -> array[j - i] = '\0';
  return r;
}

int find(text *t, text *p) {
    int i = -1;
    do{i++;
      }while(t -> array[i] != p -> array[0]);
    if(t -> array[i+1] == p -> array[1] && t -> array[i+2] == p -> array[2]) return i;
    else{i = -1;}
    return i;
}

//-----------------------------------------------------------------------------
// Tests and a textMain function (renamed to main when compiled for testing).

// Check whether a text is like a given string, as far as can be checked
// without knowing how much memory has been allocated.
bool like(text *t, char *s) {
    if (t == NULL) return false;
    if (t->size <= strlen(s)) return false;
    if (strcmp(t->array, s) != 0) return false;
    return true;
}

// Check that everything is as expected after calling new.
void testNew() {
    text *t = new("");
    assert(like(t, ""));
    text *t2 = new("cat");
    assert(like(t2, "cat"));
    discard(t);
    discard(t2);
}

void testLength() {
    text *t = new("cat");
    assert(length(t) == 3);
    discard(t);
}

void testGet() {
    text *t = new("cat");
    assert(get(t,0) == 'c');
    assert(get(t,1) == 'a');
    assert(get(t,2) == 't');
    discard(t);
}

void testSet() {
    text *t = new("cat");
    set(t, 0, 'b');
    set(t, 2, 'r');
    assert(like(t, "bar"));
    discard(t);
}

void testCopy() {
    text *t = new("cat");
    text *t2 = copy(t);
    assert(like(t2, "cat"));
    discard(t);
    discard(t2);
}

void testCompare() {
    text *t = new("cat");
    text *t2 = new("cat");
    assert(compare(t, t2) == 0);
    text *t3 = new("cas");
    assert(compare(t, t3) > 0);
    text *t4 = new("cau");
    assert(compare(t, t4) < 0);
    discard(t);
    discard(t2);
    discard(t3);
    discard(t4);
}

void testAppend() {
    text *t = new("car");
    text *t2 = new("pet");
    append(t, t2);
    assert(like(t, "carpet"));
    discard(t);
    discard(t2);
}

void testSlice() {
    text *t = new("carpet");
    text *t2 = slice(t, 0, 3);
    assert(like(t2, "car"));
    text *t3 = slice(t, 3, 6);
    assert(like(t3, "pet"));
    discard(t);
    discard(t2);
    discard(t3);
}

void testFind() {
    text *t = new("carpet");
    text *t2 = new("car");
    assert(find(t, t2) == 0);
    text *t3 = new("pet");
    assert(find(t, t3) == 3);
    text *t4 = new("cat");
    assert(find(t, t4) == -1);
    discard(t);
    discard(t2);
    discard(t3);
    discard(t4);
}

// Test the library.  (With a real library, a renaming scheme would be needed.)
int textMain() {
    testNew();
    testLength();
    testGet();
    testSet();
    testCopy();
    testCompare();
    testAppend();
    testSlice();
    testFind();
    printf("Tests all pass.\n");
    return 0;
}
