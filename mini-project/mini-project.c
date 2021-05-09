#include <stdio.h>
#include <string.h>

#define SIZE 25
#define STR_LEN 166

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

void generateMap(char map[SIZE][SIZE], int lines, int cols){
  int i, k;

  for (i = 0; i < lines; i++)
  {
    for (k = 0; k < cols; k++)
    {
      map[i][k] = '_';
    }
  }
}

void readFile(FILE * fp, char map[SIZE][SIZE], int *totalLines, int *totalCols) {
  int line, col, initFlag = 1;
  char text[STR_LEN] = "",
       type[STR_LEN],
       space1,
       space2;

  while(fscanf(fp, " %[^\n]s", text) != EOF) {
    if (text[0] != '#') {
      if (text[0] == '.' || text[0] == '*') {
        sscanf(text, "%s%c%d%c%d", type, &space1, &line, &space2, &col);

        if ((space1 != ' ' && space1 != '\t') || (space2 != ' ' && space2 != '\t')) {
          generateMap(map, SIZE, SIZE);
          puts("File is corrupted");
          return;
        }

        if (line < 0 || line >= *totalLines || col < 0 || col >= *totalCols || strlen(type) > 1) {
          generateMap(map, SIZE, SIZE);
          puts("File is corrupted");
          return;
        }

        map[line][col] = type[0];
      }

      else {
        if (initFlag) {
          sscanf(text, "%d %d", &*totalLines, &*totalCols);

          if (*totalLines != SIZE || *totalCols != SIZE) {
            *totalLines = SIZE;
            *totalCols = SIZE;
            generateMap(map, SIZE, SIZE);
            puts("File is corrupted");
            return;
          }

          generateMap(map, SIZE, SIZE);
          initFlag = 0;
        }
        else {
          generateMap(map, SIZE, SIZE);
          puts("File is corrupted");
          return;
        }
      }
    }
  }
}

void writeFile(FILE * fp, char map[SIZE][SIZE], int totalLines, int totalCols) {
  int line, col;
  
  fprintf(fp, "%d %d\n", totalLines, totalCols);

  for (line = 0; line < totalLines; line++) {
    for (col = 0; col < totalCols; col++) {
      if (map[line][col] == '*' || map[line][col] == '.') {
        fprintf(fp, "%c %d %d\n", map[line][col], line, col);
      }
    }
    
  }
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

int execution(char map[SIZE][SIZE], int totalLines, int totalCols, int showMenu) {
  int lineIndex, colIndex, coordX, coordY, starterLines, starterCols;
  char option[SIZE] = "",
       filename[SIZE] = "";
  FILE *file;

  if (showMenu) {
    menu();
  }
  
  printf(">");
  scanf(" %s", option);

  switch (checkOption(option)) {
  case 1:
    scanf(" %[^\n]s", filename);
    file = fopen(filename, "r");

    if(file == NULL) {
      puts("Error opening file");
      return execution(map, totalLines, totalCols, 0);
    }

    readFile(file, map, &starterLines, &starterCols);
    fclose(file);

    return execution(map, starterLines, starterCols, 0);

    break;

  case 2:
  
    if (map[0][0] != '_' && map[0][0] != '*' && map[0][0] != '.') {
      generateMap(map, totalLines, totalCols);
    }
  
    for (lineIndex = 0; lineIndex < SIZE; lineIndex++) {
      for (colIndex = 0; colIndex < SIZE; colIndex++) {
        printf("%c", map[lineIndex][colIndex]);
      }
      printf("\n");
    }

    return execution(map, totalLines, totalCols, 0);
    
    break;

  case 3:
    scanf("%d %d", &coordX, &coordY);

    if (map[0][0] != '_' && map[0][0] != '*' && map[0][0] != '.') {
      generateMap(map, totalLines, totalCols);
    }

    if (coordX < 0 || coordX >= totalLines || coordY < 0 || coordY >= totalCols) {
      puts("Invalid coordinate");
      return execution(map, totalLines, totalCols, 0);
    }

    if (map[coordX][coordY] == '_') {
      puts("No mine at specified coordinate");
      return execution(map, totalLines, totalCols, 0);
    }

    map[coordX][coordY] = '*';
    return execution(map, totalLines, totalCols, 0);

    break;

  case 4:
    scanf("%d %d", &coordX, &coordY);

    if (map[0][0] != '_' && map[0][0] != '*' && map[0][0] != '.') {
      generateMap(map, totalLines, totalCols);
    }

    if (coordX < 0 || coordX >= totalLines || coordY < 0 || coordY >= totalCols) {
      puts("Invalid coordinate");
      return execution(map, totalLines, totalCols, 0);;
    }

    map[coordX][coordY] = '.';
    return execution(map, totalLines, totalCols, 0);;

    break;

  case 5:
    scanf(" %[^\n]s", filename);
    file = fopen(filename, "w");

    if(file == NULL) {
      puts("Error opening file");
      return execution(map, totalLines, totalCols, 0);
    }

    writeFile(file, map, totalLines, totalCols);
    fclose(file);

    return execution(map, totalLines, totalCols, 0);
    break;

  case 6:
    return 0;
    break;

  case 7:
    return execution(map, totalLines, totalCols, 1);;
    break;

  default:
    scanf("%[^\n]s", option);
    puts("Invalid command!");
    return execution(map, totalLines, totalCols, 0);;
    break;
  }

  return 0;
}

int main() {
  char map[SIZE][SIZE];
  generateMap(map, SIZE, SIZE);

  execution(map, SIZE, SIZE, 1);

  return 0;
}
