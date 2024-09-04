#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            /* Found a directory, but ignore . and .. */
            if(strcmp(".",entry->d_name) == 0 ||
                strcmp("..",entry->d_name) == 0)
                continue;
            printf("%*s%s/\n",depth,"",entry->d_name);
            /* Recurse at a new indent level */
            printdir(entry->d_name,depth+4);
        }
        else printf("%*s%s\n",depth,"",entry->d_name);
    }
    chdir("..");
    closedir(dp);
}


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
