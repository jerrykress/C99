/* Jerry Shengjing Wang, 1658284 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>


enum { Parallel, Identical, Perpendicular, Intersect, Illegal};

int lines(const char x1[], const char y1[], const char x2[], const char y2[], const char x3[], const char y3[], const char x4[], const char y4[]) {
float k1, k2, k3, k4;

long a, b, c, d, e, f, g, h;
a = atol(x1);
b = atol(y1);
c = atol(x2);
d = atol(y2);
e = atol(x3);
f = atol(y3);
g = atol(x4);
h = atol(y4);

//printf("Original Input: %s %s %s %s %s %s %s %s\n", x1, y1, x2, y2, x3, y3, x4, y4);  //debugging line
//printf("Integer check: %ld %ld %ld %ld %ld %ld %ld %ld\n", a, b, c, d, e, f, g, h);  //debugging line

for (int i=0; i < strlen(x1); i++) {
  if (!isdigit(x1[i])) return Illegal;
    //printf("%d", i);}  //debugging line
}
for (int i=0; i < strlen(y1); i++) {
  if (!isdigit(y1[i]))
  {return Illegal;
    printf("%d", i);}
}
for (int i=0; i < strlen(x2); i++) {
  if (!isdigit(x2[i])) return Illegal;
}
for (int i=0; i < strlen(y2); i++) {
  if (!isdigit(y2[i])) return Illegal;
}
for (int i=0; i < strlen(x3); i++) {
  if (!isdigit(x3[i])) return Illegal;
}
for (int i=0; i < strlen(y3); i++) {
  if (!isdigit(y3[i])) return Illegal;
}
for (int i=0; i < strlen(x4); i++) {
  if (!isdigit(x4[i])) return Illegal;
}
for (int i=0; i < strlen(y4); i++) {
  if (!isdigit(y4[i])) return Illegal;
}


k1 = (d - b) / (c - a);
//printf("k1 = %f\n", k1); //debugging line
k2 = (h - f) / (g - e);
//printf("k2 = %f\n", k2); //debugging line
k3 = (h - d) / (g - c);
//printf("k3 = %f\n", k3); //debugging line
k4 = (h - b) / (g - a);
//printf("k4 = %f\n", k4); //debugging line

if (k1 != k2) {
  if (k1 * k2 == -1) return Perpendicular;
  else return Intersect;
  }
if (k1 == k2) {
  if (k2 == k3 && k3 == k4) return Identical;
  else return Parallel;
  }

  return 0;
}

void print(int type) {
    switch (type) {
        case Parallel: printf("Parallel"); break;
        case Identical: printf("Identical"); break;
        case Perpendicular: printf("Perpendicular"); break;
        case Intersect: printf("Intersect"); break;
        case Illegal: printf("Illegal"); break;
    }
    printf("\n");
}


int main(int n, char **argv) {

    if (n == 9) {
        int result = lines(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
        print(result);
    }
    else {
        fprintf(stderr, "Use e.g.: ./lines x1 y1 x2 y2 x3 y3 x4 y4\n");
        exit(1);
    }
    return 0;
}
