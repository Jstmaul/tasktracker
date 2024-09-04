#ifndef MAIN_H
#define MAIN_H

// Enum for task status
enum { TODO = 0, IN_PROGRESS = 1, DONE = 2 };

static void printdir(char *dir, int depth);
static void add_task(const char *filename);
static void handle_arguments(int argc, char *argv[]);
static void check_dir_exists();

#endif  // MAIN_H