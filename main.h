#ifndef MAIN_H
#define MAIN_H

// Enum for task status
enum { TODO = 0, IN_PROGRESS = 1, DONE = 2 };

static void handle_list(char *dir);
static void add_task(const char *filename);
static void check_dir_exists();
static void list_todo();
static void list_in_progress();
static void list_done();
static void handle_arguments(int argc, char *argv[]);

#endif  // MAIN_H