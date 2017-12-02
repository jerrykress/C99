/* Custom versions of standard string functions. */
/*Jerry Shengjing Wang 1658284*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

// Find the length of a string, assuming it has a null terminator (like strlen).
int length(const char s[]) {
    int count = 0;
    int i;
    for(i = 0; s[i] != '\0'; i++)
      {count++;}
    return count;
}

// Copy string s into the character array t (like strcpy).
void copy(char t[], const char s[]) {
    int i;
    for(i = 0; s[i] != '\0'; i++)
      {t[i] = s[i];}
      t[i] = '\0'; //Strings end with null element, which also needs to be copied manully
}

// Compare two strings, returning negative, zero or positive (like strcmp).
int compare(const char s[], const char t[]) {
    int sizea = 0;
    int sizeb = 0;
    int i;
    signed int ref = 0;
    for(i = 0; s[i] != '\0'; i++)
      {sizea++;}
    for(i = 0; t[i] != '\0'; i++)
      {sizeb++;}
    if (*s > *t || sizea > sizeb) {ref = 1;} //adding asterisk to access memory location to compare strings of same length
    else if (*s < *t || sizea < sizeb) {ref = -1;}
    else if (sizea == sizeb) {ref = 0;}
    return ref;
}

// Join string s to the end of string t (like strcat).
void append(char t[], const char s[]) {
    int i;
    int first;
    first = length(t);
    for(i = 0; s[i] != '\0'; i++)
      {t[i + first] = s[i];}
    t[i + first] = '\0';
}

// Find the (first) position of s in t, or return -1 (like strstr).
int find(const char t[], const char s[]) {
    int i;
    int count = 0;
    int max;
    max = length(t);
    for(i = 0; s[0] != t[i] && i <= max + 1; i++)
      {count++;}
    if(i > max) {return -1;}
    else {return count;}
}

// -----------------------------------------------------------------------------
// Tests and user interface

// Tests 1 to 5
void testLength() {
    assert(length("") == 0);
    assert(length("c") == 1);
    assert(length("ca") == 2);
    assert(length("cat") == 3);
    char s[] = "dog";
    assert(length(s) == 3);
}

// Tests 6 to 9
void testCopy() {
    char t[10];
    copy(t, "cat");
    assert(t[0] == 'c' && t[1] =='a' && t[2] == 't' && t[3] =='\0');
    copy(t, "at");
    assert(t[0] == 'a' && t[1] =='t' && t[2] =='\0');
    copy(t, "t");
    assert(t[0] == 't' && t[1] =='\0');
    copy(t, "");
    assert(t[0] == '\0');
}

// Tests 10 to 17
void testCompare() {
    assert(compare("cat", "dog") < 0);
    assert(compare("dog", "cat") > 0);
    assert(compare("cat", "cat") == 0);
    assert(compare("an", "ant") < 0);
    assert(compare("ant", "an") > 0);
    assert(compare("", "a") < 0);
    assert(compare("a", "") > 0);
    assert(compare("", "") == 0);
}

// Tests 18 to 20
void testAppend() {
    char t[10] = "cat";
    append(t, "");
    assert(t[0] == 'c' && t[1] =='a' && t[2] == 't' && t[3] =='\0');
    t[2] = '\0';
    append(t, "t");
    assert(t[0] == 'c' && t[1] =='a' && t[2] == 't' && t[3] =='\0');
    t[0] = '\0';
    append(t, "cat");
    assert(t[0] == 'c' && t[1] =='a' && t[2] == 't' && t[3] =='\0');
}

// Tests 21 to 25
void testFind() {
    assert(find("cat", "cat") == 0);
    assert(find("cat", "c") == 0);
    assert(find("cat", "t") == 2);
    assert(find("cat", "x") == -1);
    assert(find("banana", "an") == 1);
}

// Test the functions.
int main() {
    testLength();
    testCopy();
    testCompare();
    testAppend();
    testFind();
    printf("Tests all pass.\n");
    return 0;
}
