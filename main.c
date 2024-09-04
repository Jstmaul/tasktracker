#include "main.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  check_dir_exists();
  handle_arguments(argc, argv);
  return 0;
}

static void check_dir_exists() {
  DIR *dp = opendir("task-data");
  if (dp == NULL) {
    if (errno = ENOENT) {
      closedir(dp);
    } else if (errno != ENOENT) {
      printf("making task-data directory\n");
      mkdir("task-data");
      closedir(dp);
    }
  }
}

static void printdir(char *dir, int depth) {
  struct dirent *entry;
  struct _stat statbuf;
  char path[100];
  DIR *dp = opendir(dir);

  if (dp == NULL) {
    perror("opendir");
    return;
  }

  while ((entry = readdir(dp)) != NULL) {
    snprintf(path, 100, "%s/%s", dir, entry->d_name);
    if (_stat(path, &statbuf) == -1) {
      perror("stat");
      continue;
    }

    if (S_ISDIR(statbuf.st_mode)) {
      /* Found a directory, but ignore . and .. */
      if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
        continue;
      printf("%*s%s/\n", depth, "", entry->d_name);
      /* Recurse at a new indent level */
      printdir(path, depth + 4);
    } else
      printf("%*s%s\n", depth, "", entry->d_name);
  }

  closedir(dp);
}

static void add_task(const char *filename) {
  char bufr[256];

  snprintf(bufr, sizeof(bufr), "task-data/%s.bin", filename);
  FILE *file = fopen(bufr, "wb+");
  if (file == NULL) {
    perror("failed to create file");
    return;
  }
  int status = TODO;
  fwrite(&status, sizeof(int), 1, file);
  fclose(file);
  printf("Task added with status TODO to %s.bin\n", filename);
}

static void handle_arguments(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s task <command>\n", argv[0]);
    return;
  } else if (strcmp(argv[1], "list") == 0) {
    if (argc > 2) {
      if (strcmp(argv[2], "todo") == 0) {
      } else if (strcmp(argv[2], "in-progress") == 0) {
      } else if (strcmp(argv[2], "done") == 0) {
      } else {
        printf("no valid input\n");
        return;
      }
    } else {
      printdir("task-data", 0);
    }
  } else if (strcmp(argv[1], "add") == 0) {
    add_task(argv[2]);
    if (argc < 2) {
      printf("no filename provided\n");
      return;
    }
  } else if (strcmp(argv[1], "delete") == 0) {
    printf("Delete functionality not implemented yet.\n");
  } else if (strcmp(argv[1], "update") == 0) {
    printf("Update functionality not implemented yet.\n");
  } else if (strcmp(argv[1], "mark-done") == 0) {
    printf("Mark done functionality not implemented yet.\n");
  } else if (strcmp(argv[1], "mark-in-progress") == 0) {
    printf("Mark in-progress functionality not implemented yet.\n");
  } else {
    printf("no valid input\n");
  }
}