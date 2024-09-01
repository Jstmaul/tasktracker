#include <stdio.h>

static char* user_i;

int main() {
  fgets(user_i, sizeof(user_i), stdin);
  switch (*user_i) {
    case '1':
      printf("done");
      break;
    case 'add':
    printf("what add?");
    break;
    default:
      printf("please input something\n");
      break;
  }
}
