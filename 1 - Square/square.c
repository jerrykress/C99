/* Example program: say Hi. */
#include <stdio.h>

long square(long n) {
  return n * n;
}

int main() {
    // calculate the answer and store the result as a variable
    long result = square(50000);
    // print result to terminal
    printf("%ld\n", result);
    // finish the program
    return 0;
}
