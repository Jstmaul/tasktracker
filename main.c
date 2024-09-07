#include "main.h"

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
  handle_dir_check();
  handle_arguments(argc, argv);

  return 0;
}

static void handle_dir_check() {
  DIR *dp = opendir("task-data");

  if (dp == NULL) {
    if (errno != ENOENT) {
      closedir(dp);
    } else if (errno == ENOENT) {
      closedir(dp);
#if _WIN32
      mkdir("task-data");
#else
      mkdir("task-data", 0755);
#endif
      printf("task-data directory created\n");
    }
  }
}

static void handle_add_task(const char *filename) {
  char bufr[FILENAME_MAX];
  snprintf(bufr, sizeof(bufr), "task-data/%s", filename);
  FILE *file = fopen(bufr, "wb+");

  if (file == NULL) {
    perror("failed to create file");
    return;
  }
  int i = TODO;
  fwrite(&i, sizeof(int), 1, file);
  fclose(file);
  printf("Task added with status TODO to /task-data");
}

static void handle_display_task_list_sp(int task_status) {
  DIR *dp = opendir("task-data");
  struct dirent *entry;
  int file_count = 0;
  int task_with_status_found = 0;
  int i = 0;

  if (dp == NULL) {
    perror("opendir");
    return;
  }

  while ((entry = readdir(dp)) != NULL) {
    if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
      continue;
    file_count++;
  }

  char *get_task_name[file_count];
  rewinddir(dp);

  while ((entry = readdir(dp)) != NULL) {
    if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
      continue;

    get_task_name[i] = malloc(sizeof(char) * FILENAME_MAX);

    if (get_task_name[i] == NULL) {
      perror("malloc");
      return;
    }

    snprintf(get_task_name[i], sizeof(char) * FILENAME_MAX, "%s",
             entry->d_name);

    i++;
  }

  for (int i = 0; i < file_count; i++) {
    char bufr[FILENAME_MAX];
    int get_file_status;
    snprintf(bufr, sizeof(bufr), "task-data/%s", get_task_name[i]);

    FILE *file = fopen(bufr, "rb");

    if (file == NULL) {
      perror("failed to open file");
      return;
    }

    fread(&get_file_status, sizeof(int), 1, file);

    if (get_file_status == task_status) {
      printf("%s\n", get_task_name[i]);
      task_with_status_found++;
    }

    fclose(file);
    free(get_task_name[i]);
  }

  if(task_with_status_found == 0)  printf("No tasks with this status found");
  if (file_count == 0) printf("No tasks found\n");

  closedir(dp);
}

static void handle_display_task_list() {
  printf("Displaying all tasks :\n");
  printf("todo :\n");
  handle_display_task_list_sp(TODO);
  printf("in-progress :\n");
  handle_display_task_list_sp(IN_PROGRESS);
  printf("done :\n");
  handle_display_task_list_sp(DONE);
}

static void delete_task(char *filename) {
  char bufr[FILENAME_MAX];

  snprintf(bufr, sizeof(bufr), "task-data/%s", filename);

  if (remove(bufr) == 0) {
    printf("%s deleted\n", filename);
  } else {
    perror("Task not found");
  }
}

static void handle_update_task_sp(int task_status, char* argv){
  char bufr[10+FILENAME_MAX];
  snprintf(bufr, sizeof(bufr), "task-data/%s", argv);
  FILE *fp = fopen(bufr, "rb+");

  if(fp == NULL){
    printf("No task with %s name found", argv);
    return;
  }

  fwrite(&task_status, sizeof(int), 1, fp);
  fclose(fp);
  printf("%s updated",argv);
}

static void handle_arguments(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s task <command>\n", argv[0]);
    return;
  } else if (strcmp(argv[1], "list") == 0) {
    if (argc > 2) {
      if (strcmp(argv[2], "todo") == 0) {
        handle_display_task_list_sp(TODO);
      } else if (strcmp(argv[2], "in-progress") == 0) {
        handle_display_task_list_sp(IN_PROGRESS);
      } else if (strcmp(argv[2], "done") == 0) {
        handle_display_task_list_sp(DONE);
      } else {
        printf("invalid input\n");
        return;
      }
    } else {
      handle_display_task_list();
    }
  } else if (strcmp(argv[1], "add") == 0) {
    handle_add_task(argv[2]);
    if (argc < 2) {
      printf("no filename provided\n");
      return;
    }
  } else if (strcmp(argv[1], "delete") == 0) {
    delete_task(argv[2]);
  } else if (strcmp(argv[1], "mark") == 0) {
    if (argc < 2){
      printf("Usage mark: \"taskname\" <todo/in-progress/done>");
      return;
    }
    if (argc < 3){
      printf("please input command\n");
      printf("Usage mark: \"taskname\" <todo/in-progress/done>");
      return;
    }

    if(strcmp(argv[3], "todo") == 0){
      handle_update_task_sp(0,argv[2]);
    } 
    if(strcmp(argv[3], "in-progress") == 0){
      handle_update_task_sp(1,argv[2]);
    } 
    if(strcmp(argv[3], "done") == 0){
      handle_update_task_sp(3,argv[2]);
    } 
  } else {
    printf("invalid input\n");
  }
}
