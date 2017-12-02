#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


void reverse(){
  char str[100], tmp;
  int s, t = 0;

  printf("\nEnter the string:");
  scanf("%80[^\r\n]", str); //scanf incl. white spaces;

  s = 0;
  t = strlen(str) - 1;

  while (s < t) {
     tmp = str[s];
     str[s] = str[t];
     str[t] = tmp;
     s++;
     t--;
  } //reverse function;

  printf("\nThe reversed string is:%s\n\n", str);
}

void upper(){
  FILE *fp1, *fp2;
      char ch;
      fp1 = fopen("source.txt", "r");
      if (fp1 == NULL)
      {
            printf("File does not exist..\n");
            exit(1);
      }
      fp2 = fopen("target.txt", "w");
      if (fp2 == NULL)
      {
            printf("File does not exist..\n");
            fclose(fp1);
            exit(1);
      }
      while((ch=fgetc(fp1))!=EOF) //Read until the end of file;
      {
            ch = toupper(ch);
            fputc(ch,fp2);
      }
      printf("\nFile converted to uppercase..\n\n");

      //free() is not needed here because fclose() automatically cleans up the memory used by fopen();
      //free() is used to clean up the memory allocated by malloc();
}

void hex(){
  FILE *fp1, *fp2;
  char ch;
  fp1 = fopen("source.txt", "r");
  if (fp1 == NULL)
  {
        printf("File does not exist..\n");
        exit(1);
  }
  fp2 = fopen("target.txt", "w");
  if (fp2 == NULL)
  {
        printf("File does not exist..\n");
        fclose(fp1);
        exit(1);
  }
  while((ch=fgetc(fp1))!=EOF) //Read until the end of file;
  {
      fprintf(fp2, "%X\n", ch);
  }
  printf("\nFile converted to hex..\n\n");

}

void test(){
    printf("Use: ./io R  OR  ./io U  OR  ./io H\n");
}

int main(int n, char *args[n]) {
  if (n == 1) test();
  else if (n == 2 && strcmp(args[1],"R") == 0) reverse();
  else if (n == 2 && strcmp(args[1],"U") == 0) upper();
  else if (n == 2 && strcmp(args[1],"H") == 0) hex();
  else {
      fprintf(stderr, "Use: ./io  OR  ./io R  OR  ./io U  OR  ./io H\n");
      exit(1);
  }

  return 0;
}
