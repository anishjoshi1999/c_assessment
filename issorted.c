#include <stdio.h>

#include <stdlib.h>

#include <string.h>

int cmpstringp(const void * p1,
  const void * p2) {
  return strcmp( * (const char ** ) p1, *(const char ** ) p2);
}

int main(int argc, char * argv[]) {

  int count = 0; // count of elements processed
  FILE * fp = NULL; // file pointer for input file

  // check for help option
  if (((argc == 2 && strcmp(argv[1], "--help")) == 0) || ((argc == 2 && strcmp(argv[1], "-h")) == 0)) {
    printf("issorted 1.0.0 (c) 2023, Prasid Dahal");
    printf("\n======================================");
    printf("\nusage: issorted [(-n|i|r|s|l|h)|--help] [filename]");
    printf("\n");
    printf("\n\t -n \tsort natural numbers");
    printf("\n\t -i \tsort integers numbers");
    printf("\n\t -r \tsort real numbers");
    printf("\n\t -s \tsort strings");
    printf("\n\t -l \tsort lines numbers");
    printf("\n\t -h \tdisplay help");
    printf("\n");
    printf("\n\t --help display help");
    printf("\n");
    return EXIT_SUCCESS;
  } else if (((argc == 2 && strcmp(argv[1], "-n")) == 0) || ((argc == 2 && strcmp(argv[1], "-i")) == 0)) {
    int sorted = 1; // assume initially sorted
    int prev = 0; // previous element in stream
    int curr; // current element in stream
    while (1) {
      // read from console
      if (scanf("%d", & curr) != 1) {
        break;
      }
      count++;
      if (count > 1 && curr < prev) {
        printf("element %d (%d) not sorted\n", count, curr);
        sorted = 0;
        break;
      }
      prev = curr;
    }
    // print result and return status code
    if (sorted) {
      printf("sorted\n");
      return 101;
    } else {
      return 100;
    }
  } else if ((argc == 2 && strcmp(argv[1], "-r")) == 0) {
    double sorted = 1.0; // assume initially sorted
    double prev = 0.0; // previous element in stream
    double curr; // current element in stream
    while (1) {
      // read from console
      if (scanf("%lf", & curr) != 1) {
        break;
      }
      count++;
      if (count > 1 && curr < prev) {
        printf("element %d (%lf) not sorted\n", count, curr);
        sorted = 0;
        break;
      }
      prev = curr;
    }
    // print result and return status code
    if (sorted) {
      printf("sorted\n");
      return 101;
    } else {
      return 100;
    }
  } else if ((argc == 2 && strcmp(argv[1], "-s")) == 0) {

    char ** strings = NULL; // array of strings
    char buffer[256]; // buffer for reading strings
    int size = 0; // size of array

    // read strings from console
    while (1) {
      if (fgets(buffer, 256, stdin) == NULL) {
        break;
      }
      size++;
      strings = realloc(strings, size * sizeof(char * ));
      strings[size - 1] = malloc(strlen(buffer) + 1);
      strcpy(strings[size - 1], buffer);
    }

    // sort strings using qsort
    qsort(strings, size, sizeof(char * ), cmpstringp);
    // print sorted strings
    for (int i = 0; i < size; i++) {
      printf("%s", strings[i]);
      free(strings[i]);
    }
    free(strings);
    // print result and return status code
    printf("sorted\n");
    return 101;
  } else if ((argc == 2 && strcmp(argv[1], "-l")) == 0) {
    // To sort lines
    char ** lines = NULL;
    char buffer[256];
    int size = 0;

    // read lines from console or file
    while (fgets(buffer, 256, stdin) != NULL) {
      size++;
      lines = realloc(lines, size * sizeof(char * ));
      lines[size - 1] = malloc(strlen(buffer) + 1);
      strcpy(lines[size - 1], buffer);
    }
    if (fp) {
      while (fgets(buffer, 256, fp) != NULL) {
        size++;
        lines = realloc(lines, size * sizeof(char * ));
        lines[size - 1] = malloc(strlen(buffer) + 1);
        strcpy(lines[size - 1], buffer);
      }
    }

    // sort lines using qsort
    qsort(lines, size, sizeof(char * ), cmpstringp);

    // print sorted lines
    for (int i = 0; i < size; i++) {
      printf("%s", lines[i]);
      free(lines[i]);
    }
    free(lines);

    // print result and return status code
    printf("sorted\n");
    return 101;
  } else if (argc == 2) {
    // check for input file
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
      printf("Error: Unable to open file %s\n", argv[1]);
      return EXIT_FAILURE;
    }
  } else {
    return EXIT_FAILURE;
  }

  return 0;
}