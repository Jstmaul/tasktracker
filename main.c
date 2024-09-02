#include <stdio.h>
#include <string.h>

enum { TODO, IN_PROGRESS, DONE };

int main(int argc, char *argv[]) {
  if (argc > 1) {
    if (!strcmp(argv[1], "list")) {
      if (argc > 2) {
        if (!strcmp(argv[2], "done")) {
        } else if (!strcmp(argv[2], "in-progress")) {
        } else if (!strcmp(argv[2], "todo")) {
        }
      } else {
        FILE *fptr;

      read_to_do_list:

        fptr = fopen("to_do_list.txt", "r");

        if (fptr == NULL) {
          printf("No file detected %s\n", "Creating to_do_list.txt\n");

          fptr = fopen("to_do_list.txt", "w");

          goto read_to_do_list;

        } else {
          char file_buffer[1024];

          while (fgets(file_buffer, sizeof(file_buffer), fptr)) {
            printf("%s", file_buffer);
          }
        }

        fclose(fptr);
      }
    } else if (!strcmp(argv[1], "add")) {
      FILE *fptr;

      fptr = fopen("to_do_list.txt", "a");

      if (fptr == NULL) {
        printf("Error opening file!\n");

      } else {
        char *line = argv[2];

        fprintf(fptr, "%s %d\n", line, TODO);
      }
      fclose(fptr);

    } else if (!strcmp(argv[1], "delete")) {
      FILE *fptr;
      fptr = fopen("to_do_list.txt", "r");
      if (fptr == NULL) {
        printf("Error opening file!\n");
      } else {
        char file_buffer[1024];
        FILE *temp_fptr = fopen("temp.txt", "w");
        while (fgets(file_buffer, sizeof(file_buffer), fptr)) {
          file_buffer[strcspn(file_buffer, "\n")] = 0; // remove newline character
          if (strcmp(file_buffer, argv[2] + '\n') ==! 0) {
            fprintf(temp_fptr, "%s", file_buffer);
          }
        }
        fclose(fptr);
        fclose(temp_fptr);
        remove("to_do_list.txt");
        rename("temp.txt", "to_do_list.txt");
      }

    } else if (!strcmp(argv[1], "update")) {
    } else if (!strcmp(argv[1], "mark-done")) {
    } else if (!strcmp(argv[1], "mark-in-progress")) {
    } else {
      printf("no valid input\n");
    }
  }
  return 0;
}
