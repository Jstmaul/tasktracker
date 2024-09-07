#ifndef MAIN_H
#define MAIN_H

// Enum for task status
enum { TODO = 0, IN_PROGRESS = 1, DONE = 2 };


static void handle_dir_check();
static void handle_display_task_list() ;
static void handle_add_task(const char *filename) ;
static void handle_display_list_list_sp(int task_status);
static void delete_task(char *filename) ;
static void handle_arguments(int argc, char **argv);

#endif  // MAIN_H
