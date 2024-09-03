#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to open a file with ".bin" extension
/*
FILE *open_file_with_extension(const char *filename) {
  // Allocate a buffer for the filename with ".bin" extension
  size_t len = strlen(filename) + 5;  // 4 for ".bin" + 1 for '\0'
  char *full_filename = (char *)malloc(len);
  if (full_filename == NULL) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }
  snprintf(full_filename, len, "%s.bin", filename);  // Format filename

  // Open the file
  FILE *file = fopen(full_filename, "wb+");
  free(full_filename);  // Free the allocated buffer
  return file;
}
*/

// Enum for task status
enum { TODO = 0, IN_PROGRESS = 1, DONE = 2 };

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("no valid input\n");
    return 1;
  } else if (strcmp(argv[1], "list") == 0) {
    if (argc > 2) {
      if(strcmp(argv[2], "todo") == 0) {
        
      }else if (strcmp(argv[2], "in-progress") == 0) {
        
      }else if(strcmp(argv[2], "done") == 0) {

      }else{
        printf("no valid input\n");
        return 1;
      }
    } else {
      //list all tasks

    }
  } else if (strcmp(argv[1], "add") == 0) {
    if (argc < 3) {
      printf("no filename provided\n");
      return 1;
    }
    char bufr[256];
    snprintf(bufr, sizeof(bufr), "%s.bin", argv[2]);
    FILE *file = fopen(bufr, "wb+");
    if (file == NULL) {
      perror("failed to create file");
      return 1;
    }
    int status = TODO;  // Use the integer value of TODO
    fwrite(&status, sizeof(int), 1, file);
    fclose(file);
    printf("Task added with status TODO to %s.bin\n", argv[2]);
  } else if (strcmp(argv[1], "delete") == 0) {
    // Implementation for deleting tasks goes here
    printf("Delete functionality not implemented yet.\n");
  } else if (strcmp(argv[1], "update") == 0) {
    // Implementation for updating tasks goes here
    printf("Update functionality not implemented yet.\n");
  } else if (strcmp(argv[1], "mark-done") == 0) {
    // Implementation for marking tasks as done goes here
    printf("Mark done functionality not implemented yet.\n");
  } else if (strcmp(argv[1], "mark-in-progress") == 0) {
    // Implementation for marking tasks as in progress goes here
    printf("Mark in-progress functionality not implemented yet.\n");
  } else {
    printf("no valid input\n");
  }

  return 0;
}
