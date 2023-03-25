#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
  // Check args
  if (argc == 1) {
    printf("%s: no input files, exit.\n", argv[0]);
    return 1;
  }
  FILE *inputFile = fopen(argv[1], "r");
  char sh[strlen(argv[1] + 30)];
  if (inputFile == NULL) {
    sprintf(sh, "wget -q -O index.html \"%s\"", argv[1]);
    if (system(sh) == 0) {
      inputFile = fopen("index.html", "r");
    } else {
      perror(argv[1]);
      return 1;
    }
  }
  char text[2000000];
  char link[500];
  while (fgets(text, 2000000, inputFile) != NULL) {
    char *point = text;
    while (1) {
      point = strstr(point, "//");
      if (point == NULL)
        break;
      point += 2;
      //printf("pt:\n%s\n", point);
      link[0] = '\0';
      strncat(link, point, strstr(point, "\"") - point);
      printf("%s\n", link);
    }
  }
  fclose(inputFile);
  return 0;
}
