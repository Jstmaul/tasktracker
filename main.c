#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc > 1) {
    if (!strcmp(argv[1], "list")) {
      if (argc > 2) {
        if (!strcmp(argv[2], "done")) {
        } else if (!strcmp(argv[2], "in-progress")) {
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
          char file_buffer[sizeof(*fptr)];

          if (fgets(file_buffer, sizeof(file_buffer), fptr)) {
            printf("%s", file_buffer);
          }
        }

        fclose(fptr);
      }
    } else if (!strcmp(argv[1], "add")) {
    } else if (!strcmp(argv[1], "delete")) {
    } else if (!strcmp(argv[1], "update")) {
    } else if (!strcmp(argv[1], "mark-done")) {
    } else if (!strcmp(argv[1], "mark-in-progress")) {
    } else {
      printf("no valid input\n");
    }
  }
  return 0;
}
