#include <stdio.h>
#include <string.h>

#define SIZE 166

void menu() {
  puts("+-----------------------------------------------------");
  puts("read <filename>     - read input file");
  puts("show                - show the mine map");
  puts("trigger <x> <y>     - trigger mine at <x> <y>");
  puts("plant <x> <y>       - place armed mine at <x> <y>");
  puts("export <filename>   - save file with current map");
  puts("quit                - exit program");
  puts("sos                 - show menu");
  puts("+-----------------------------------------------------");
}

int checkOption(char option[]) {
  if(strcmp(option, "read") == 0) {
    return 1;
  }
  else if (strcmp(option, "show") == 0) {
    return 2;
  }
  else if (strcmp(option, "trigger") == 0) {
    return 3;
  }
  else if (strcmp(option, "plant") == 0) {
    return 4;
  }
  else if (strcmp(option, "export") == 0) {
    return 5;
  }
  else if (strcmp(option, "quit") == 0) {
    return 6;
  }
  else if (strcmp(option, "sos") == 0) {
    return 7;
  }
  else {
    return 0;
  }
}

int execution() {
  char option[SIZE] = "",
       filename[SIZE] = "";

  menu();
  printf(">");
  scanf(" %s", option);

  switch (checkOption(option)) {
  case 1:
    scanf(" %[^\n]s", filename);
    break;

  case 2:
    puts("show");
    break;

  case 3:
    puts("trigger");
    break;

  case 4:
    puts("plant");
    break;

  case 5:
    puts("export");
    break;

  case 6:
    return 0;
    break;

  case 7:
    return execution();
    break;

  default:
    break;
  }

  return 0;
}

int main() {
  execution();
  return 0;
}
