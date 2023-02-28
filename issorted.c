#include <stdio.h>

#include <stdlib.h>

#include <string.h>

int cmpstringp(const void * p1,
  const void * p2) {
  return strcmp( * (const char ** ) p1, *(const char ** ) p2);
}

int main(int argc, char * argv[]) {
  int count = 0;
  FILE * fp = NULL;
  int use_file_input = 0;

  if ((argc == 2 && strcmp(argv[1], "--help") == 0) ||
    (argc == 2 && strcmp(argv[1], "-h") == 0)) {
    // display help
    printf("issorted 1.0.0 (c) 2023, Prasid Dahal\n");
    printf("======================================\n");
    printf("usage: issorted [(-n|i|r|s|l|h)|--help] [filename]\n\n");
    printf("\t-n \tsort natural numbers\n");
    printf("\t-i \tsort integers\n");
    printf("\t-r \tsort real numbers\n");
    printf("\t-s \tsort strings\n");
    printf("\t-l \tsort lines\n");
    printf("\t-h \tdisplay help\n\n");
    printf("\t--help display help\n");
    return EXIT_SUCCESS;
  } else if ((argc == 3 && strcmp(argv[1], "-n") == 0) ||
    (argc == 3 && strcmp(argv[1], "-i") == 0)) {
    // sort integers or natural numbers
    // read input from file if provided, otherwise from keyboard
    if (argc == 3) {
      fp = fopen(argv[2], "r");
      if (fp == NULL) {
        printf("Error: Unable to open file %s\n", argv[2]);
        return EXIT_FAILURE;
      }
      use_file_input = 1;
    }
    int sorted = 1;
    int prev = 0;
    int curr;
    while (1) {
      if (use_file_input) {
        if (fscanf(fp, "%d", & curr) != 1) {
          break;
        }
      } else {
        if (scanf("%d", & curr) != 1) {
          break;
        }
      }
      count++;
      if (count > 1 && curr < prev) {
        printf("element %d (%d) not sorted\n", count, curr);
        sorted = 0;
        break;
      }
      prev = curr;
    }
    if (sorted) {
      printf("sorted\n");
      return 101;
    } else {
      return 100;
    }
  } else if ((argc == 2 && strcmp(argv[1], "-n") == 0) ||
    (argc == 2 && strcmp(argv[1], "-i") == 0)) {
    int sorted = 1;
    int prev = 0;
    int curr;
    while (1) {
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
    if (sorted) {
      printf("sorted\n");
      return 101;
    } else {
      return 100;
    }
  } else if ((argc == 3 && strcmp(argv[1], "-r") == 0)) {
    // sort integers or natural numbers
    // read input from file if provided, otherwise from keyboard
    if (argc == 3) {
      fp = fopen(argv[2], "r");
      if (fp == NULL) {
        printf("Error: Unable to open file %s\n", argv[2]);
        return EXIT_FAILURE;
      }
      use_file_input = 1;
    }
    double sorted = 1;
    double prev = 0;
    double curr;
    while (1) {
      if (use_file_input) {
        if (fscanf(fp, "%lf", & curr) != 1) {
          break;
        }
      } else {
        if (scanf("%lf", & curr) != 1) {
          break;
        }
      }
      count++;
      if (count > 1 && curr < prev) {
        printf("element %d (%lf) not sorted\n", count, curr);
        sorted = 0;
        break;
      }
      prev = curr;
    }
    if (sorted) {
      printf("sorted\n");
      return 101;
    } else {
      return 100;
    }
  } else if ((argc == 2 && strcmp(argv[1], "-r") == 0)) {
    double sorted = 1.0;
    double prev = 0.0;
    double curr;
    while (1) {
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
    if (sorted) {
      printf("sorted\n");
      return 101;
    } else {
      return 100;
    }
  } else if ((argc == 3 && strcmp(argv[1], "-s")) == 0) {

    char ** strings = NULL; // array of strings
    char buffer[256]; // buffer for reading strings
    int size = 0; // size of array
    int capacity = 0; // capacity of array

    // Check if an input file is provided
    if (argc == 3) {
      fp = fopen(argv[2], "r");
      if (fp == NULL) {
        printf("Error: Unable to open file %s\n", argv[2]);
        return EXIT_FAILURE;
      }
    } else {
      fp = stdin;
    }

    // read strings from input
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
      size++; // increase size of array
      if (size > capacity) {
        // if needed, resize array
        capacity = size + 10; // increase capacity by 10
        strings = realloc(strings, capacity * sizeof(char * ));
        if (strings == NULL) {
          fprintf(stderr, "Error: out of memory\n");
          return EXIT_FAILURE;
        }
      }
      strings[size - 1] = strdup(buffer);
      if (strings[size - 1] == NULL) {
        fprintf(stderr, "Error: out of memory\n");
        return EXIT_FAILURE;
      }
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
  } else if ((argc == 2 && strcmp(argv[1], "-s")) == 0) {

    char ** strings = NULL; // array of strings
    char buffer[256]; // buffer for reading strings
    int size = 0; // size of array
    int capacity = 0; // capacity of array

    // read strings from console
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
      size++; // increase size of array
      if (size > capacity) {
        // if needed, resize array
        capacity = size + 10; // increase capacity by 10
        strings = realloc(strings, capacity * sizeof(char * ));
        if (strings == NULL) {
          fprintf(stderr, "Error: out of memory\n");
          return EXIT_FAILURE;
        }
      }
      strings[size - 1] = strdup(buffer);
      if (strings[size - 1] == NULL) {
        fprintf(stderr, "Error: out of memory\n");
        return EXIT_FAILURE;
      }
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
    const int buffer_size = 256;
    int size = 0;

    // define a function for reading lines
    void read_lines(FILE * fp) {
      char buffer[buffer_size];
      while (fgets(buffer, buffer_size, fp) != NULL) {
        size++;
        lines = realloc(lines, size * sizeof(char * ));
        lines[size - 1] = malloc(strlen(buffer) + 1);
        strcpy(lines[size - 1], buffer);
      }
    }

    // read lines from console or file
    if (use_file_input) {
      read_lines(fp);
    } else {
      read_lines(stdin);
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
  } else if ((argc == 2 && strcmp(argv[1], "-l")) == 0) {
    // To sort lines
    char ** lines = NULL;
    const int buffer_size = 256;
    int size = 0;

    // define a function for reading lines
    void read_lines(FILE * fp) {
      char buffer[buffer_size];
      while (fgets(buffer, buffer_size, fp) != NULL) {
        size++;
        lines = realloc(lines, size * sizeof(char * ));
        lines[size - 1] = malloc(strlen(buffer) + 1);
        strcpy(lines[size - 1], buffer);
      }
    }

    // read lines from console or file
    read_lines(stdin);
    if (fp) {
      read_lines(fp);
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
  // add code for other options here
}