#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "messages.h"

#define DIM 256
#define BOMB_ON '.'
#define BOMB_OFF '*'
#define NO_BOMB '_'

typedef struct _event {
	int x;
  int y;
	int time;
	struct _event * next;
} event;


void menu() {
  puts(MSG_TITLE);
  puts("show                - show the mine map");
  puts("propagate <x> <y>   - explode bomb at <x> <y>");
  puts("log <x> <y>         - explode bomb at <x> <y>");
  puts("plant <x> <y>       - place bomb at <x> <y>");
  puts("export <filename>   - save file with current map");
  puts("quit                - exit program");
  puts("sos                 - show menu");
  puts(MSG_ENDTITLE);
}

char ** generateMap(int lines, int cols) {
  int i, k;
  char ** map;

  map = (char **)malloc(lines * sizeof(char*));

  for(i=0; i<lines; i++){
    map[i] = (char *)malloc(cols * sizeof(char));
  }
  
  for (i = 0; i < lines; i++)
  {
    for (k = 0; k < cols; k++)
    {
      map[i][k] = NO_BOMB;
    }
  }

  return map;
}

void showMap(char ** map, int totalLines, int totalCols) {
  int lineIndex, colIndex;

  for (lineIndex = 0; lineIndex < totalLines; lineIndex++) {
    for (colIndex = 0; colIndex < totalCols; colIndex++) {
      printf("%c", map[lineIndex][colIndex]);
    }
    printf("\n");
  }
}

void list(event * first, char ** map, int totalLines, int totalCols, int isPropagate)
{
	event * t;

	for (t = first ; t != NULL ; t = t -> next)
	{
    map[t->x][t->y] = BOMB_OFF;
    if (isPropagate)
    {
      showMap(map, totalLines, totalCols);
    }
    else {
		  printf("%d [%d, %d]\n", t->time, t->x, t->y);
    }
    
	}
}

int addEvent(event ** first, event p, char ** map, int totalLines, int totalCols, int check)
{
	event * aux = (event *) malloc(sizeof(event));
  event * t;

  if (!check || p.x < 0 || p.y < 0 || p.x >= totalLines || p.y >= totalCols || map[p.x][p.y] != BOMB_ON)
  {
    
    return 0;
  }

	if (aux == NULL)
  {
		return 0;
  }
	
	*aux = p;

	if (*first != NULL)
	{

    for (t = *first ; t != NULL ; t = t -> next)
    {
      if (p.time >= t -> time)
      {
        if (t -> next == NULL)
        {
          t -> next = aux;
          
          return 1;
        }
        else if ((t->next) -> time >= p.time ) {
          p.next = t -> next;
          t -> next = aux;
          
          return 1;
        }
        
      }
      
    }
    
		return 1;
	}

	*first = aux;

	return 1;
}

int deleteEvent (event ** first)
{
	event * aux;
	if (*first == NULL)
  {
		return 0;
  }

	aux = *first;
	*first = aux -> next;

	free(aux);

  return 1;
}

void generateEvents(event * first, char ** map, int totalLines, int totalCols, int line, int col, int currentTime) {
  event * t;
  int previousLine = line - 1,
      previousCol = col - 1,
      nextLine = line + 1,
      nextCol = col + 1;

  int checkTop = 1,
      checkLeftTop = 1,
      checkLeft = 1,
      checkLeftBot = 1,
      checkBot = 1,
      checkRightBot = 1,
      checkRight = 1,
      checkRightTop = 1;

  event top, leftTop, left, leftBot, bot, rightBot, right, rightTop;

  if (line < 0 || col < 0 || line >= totalLines || col >= totalCols || map[line][col] != BOMB_ON)
  {
    return;
  }

  for (t = first ; t != NULL ; t = t -> next)
	{
    if (t -> x == previousLine && t -> y == col) {
      checkTop = 0;
    }
    else if (t -> x == previousLine && t -> y == previousCol) {
      checkLeftTop = 0;
    }
    else if (t -> x == line && t -> y == previousCol) {
      checkLeft = 0;
    }
    else if (t -> x == nextLine && t -> y == previousCol) {
      checkLeftBot = 0;
    }
    else if (t -> x == nextLine && t -> y == col) {
      checkBot = 0;
    }
    else if (t -> x == nextLine && t -> y == nextCol) {
      checkRightBot = 0;
    }
    else if (t -> x == line && t -> y == nextCol) {
      checkRight = 0;
    }
    else if (t -> x == previousLine && t -> y == nextCol) {
      checkRightTop = 0;
    }
	}

  top.x = previousLine;
  top.y = col;
  top.time = currentTime + 10;
  top.next = NULL;

  leftTop.x = previousLine;
  leftTop.y = previousCol;
  leftTop.time = currentTime + 11;
  leftTop.next = NULL;

  left.x = line;
  left.y = previousCol;
  left.time = currentTime + 12;
  left.next = NULL;

  leftBot.x = nextLine;
  leftBot.y = previousCol;
  leftBot.time = currentTime + 13;
  leftBot.next = NULL;

  bot.x = nextLine;
  bot.y = col;
  bot.time = currentTime + 14;
  bot.next = NULL;

  rightBot.x = nextLine;
  rightBot.y = nextCol;
  rightBot.time = currentTime + 15;
  rightBot.next = NULL;

  right.x = line;
  right.y = nextCol;
  right.time = currentTime + 16;
  right.next = NULL;

  rightTop.x = previousLine;
  rightTop.y = nextCol;
  rightTop.time = currentTime + 17;
  rightTop.next = NULL;

  addEvent(&first, top, map, totalLines, totalCols, checkTop);
  addEvent(&first, leftTop, map, totalLines, totalCols, checkLeftTop);
  addEvent(&first, left, map, totalLines, totalCols, checkLeft);
  addEvent(&first, leftBot, map, totalLines, totalCols, checkLeftBot);
  addEvent(&first, bot, map, totalLines, totalCols, checkBot);
  addEvent(&first, rightBot, map, totalLines, totalCols, checkRightBot);
  addEvent(&first, right, map, totalLines, totalCols, checkRight);
  addEvent(&first, rightTop, map, totalLines, totalCols, checkRightTop);

  if (checkTop)
  {
    generateEvents(first, map, totalLines, totalCols, previousLine, col, currentTime + 10);
  }

  if (checkLeftTop)
  {
    generateEvents(first, map, totalLines, totalCols, previousLine, previousCol, currentTime + 11);
  }

  if (checkLeft)
  {
    generateEvents(first, map, totalLines, totalCols, line, previousCol, currentTime + 12);
  }
  
  if (checkLeftBot)
  {
    generateEvents(first, map, totalLines, totalCols, nextLine, previousCol, currentTime + 13);
  }

  if (checkBot)
  {
    generateEvents(first, map, totalLines, totalCols, nextLine, col, currentTime + 14);
  }
  
  if (checkRightBot)
  {
    generateEvents(first, map, totalLines, totalCols, nextLine, nextCol, currentTime + 15);
  }
  
  if (checkRight)
  {
    generateEvents(first, map, totalLines, totalCols, line, nextCol, currentTime + 16);
  }

  if (checkRightTop)
  {
    generateEvents(first, map, totalLines, totalCols, previousLine, nextCol, currentTime + 17);
  }
  
}

char ** readFile(FILE * fp, int *totalLines, int *totalCols) {
  char ** map;
  int line, col, initFlag = 1, n;
  char text[DIM] = "",
       type[DIM],
       space1,
       space2;

  while(fscanf(fp, " %[^\n]s", text) != EOF) {
    if (text[0] != '#') {
      if (text[0] == BOMB_ON || text[0] == BOMB_OFF) {
        n = sscanf(text, "%s%c%d%c%d", type, &space1, &line, &space2, &col);

        if (initFlag) {
          puts(MSG_FILE_CRP);
          return NULL;
        }

        if (n != 5) {
          puts(MSG_FILE_CRP);
          return NULL;
        }

        if ((space1 != ' ' && space1 != '\t') || (space2 != ' ' && space2 != '\t')) {
          puts(MSG_FILE_CRP);
          return NULL;
        }

        if (line < 0 || line >= *totalLines || col < 0 || col >= *totalCols || strlen(type) > 1) {
          puts(MSG_FILE_CRP);
          return NULL;
        }

        map[line][col] = type[0];
      }

      else {
        if (initFlag) {
          n = sscanf(text, "%d %d", &*totalLines, &*totalCols);

          if (n != 2) {
            puts(MSG_FILE_CRP);
            return NULL;
          }

          map = generateMap(*totalLines, *totalCols);
          initFlag = 0;
        }
        else {
          puts(MSG_FILE_CRP);
          return NULL;
        }
      }
    }
  }

  return map;
}

int getLastCurrentTime(event ** first) {
  event * t;

  for (t = *first ; t != NULL ; t = t -> next)
  {
    if (t -> next == NULL)
    {
      return t -> time;
    }
  }

  return 0;
}

void writeFile(FILE * fp, char ** map, int totalLines, int totalCols) {
  int line, col;
  
  fprintf(fp, "%d %d\n", totalLines, totalCols);

  for (line = 0; line < totalLines; line++) {
    for (col = 0; col < totalCols; col++) {
      if (map[line][col] == BOMB_OFF || map[line][col] == BOMB_ON) {
        fprintf(fp, "%c %d %d\n", map[line][col], line, col);
      }
    }
    
  }
}

int checkOption(char option[]) {
  if (strcmp(option, "show") == 0) {
    return 1;
  }
  else if (strcmp(option, "propagate") == 0) {
    return 2;
  }
  else if (strcmp(option, "log") == 0) {
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

int execution(char ** map, int totalLines, int totalCols) {
  int coordX, coordY;
  int currentTime = 0;
  char option[DIM] = "",
       filename[DIM] = "";
  FILE *file;
  event * first = NULL;
  event p;

  menu();

  do
  {
    printf(MSG_PROMPT);
    scanf(" %s", option);

    switch (checkOption(option)) {
    
    case 1:
      showMap(map, totalLines, totalCols);
      
      break;

    case 2:
      scanf("%d %d", &coordX, &coordY);

      if (coordX < 0 || coordX >= totalLines || coordY < 0 || coordY >= totalCols) {
        puts(MSG_INVAL_CRD);
        break;
      }

      if (map[coordX][coordY] == NO_BOMB) {
        puts(MSG_NOBOMB);
        break;
      }

      if (map[coordX][coordY] == BOMB_OFF) {
        break;
      }

      p.x = coordX;
      p.y = coordY;
      p.time = currentTime;
      p.next = NULL;

      addEvent(&first, p, map, totalLines, totalCols, 1);
      
      generateEvents(first, map, totalLines, totalCols, coordX, coordY, currentTime);
      currentTime = getLastCurrentTime(&first);
      list(first, map, totalLines, totalCols, 1);
      while (deleteEvent(&first));

      break;

    case 3:
      scanf("%d %d", &coordX, &coordY);

      if (coordX < 0 || coordX >= totalLines || coordY < 0 || coordY >= totalCols) {
        puts(MSG_INVAL_CRD);
        break;
      }

      if (map[coordX][coordY] == NO_BOMB) {
        puts(MSG_NOBOMB);
        break;
      }

      if (map[coordX][coordY] == BOMB_OFF) {
        break;
      }

      p.x = coordX;
      p.y = coordY;
      p.time = currentTime;
      p.next = NULL;

      addEvent(&first, p, map, totalLines, totalCols, 1);
      
      generateEvents(first, map, totalLines, totalCols, coordX, coordY, currentTime);
      currentTime = getLastCurrentTime(&first);
      list(first, map, totalLines, totalCols, 0);
      while (deleteEvent(&first));   

      break;

    case 4:
      scanf("%d %d", &coordX, &coordY);

      if (map[0][0] != NO_BOMB && map[0][0] != BOMB_OFF && map[0][0] != BOMB_ON) {
        generateMap(totalLines, totalCols);
      }

      if (coordX < 0 || coordX >= totalLines || coordY < 0 || coordY >= totalCols) {
        puts(MSG_INVAL_CRD);
        break;
      }

      map[coordX][coordY] = BOMB_ON;

      break;

    case 5:
      scanf(" %[^\n]s", filename);
      file = fopen(filename, "w");

      if(file == NULL) {
        puts("Error opening file");
        break;
      }

      writeFile(file, map, totalLines, totalCols);
      fclose(file);

      break;

    case 6:
      return 0;
      break;

    case 7:
      menu();
      break;

    default:
      scanf("%[^\n]s", option);
      puts(MSG_INVAL_CMD);
      break;
    }
  } while (checkOption(option) != 6);
  

  return 0;
}

int main(int argc, char * argv[]) {
  char fileName[DIM];
  char ** map;
  int starterLines, starterCols;
  FILE *file;

  if(argc == 1)
  {
    puts(MSG_FNAME);
    return 0;
  }    
  else
  {
    sscanf(argv[1], "%s", fileName);

    file = fopen(fileName, "r");

    if(file == NULL) {
      puts(MSG_FILE_OPN);
      return 0;
    }

    map = readFile(file, &starterLines, &starterCols);

    if (map == NULL)
    {
      return 0;
    }
    
    fclose(file);
  }

  execution(map, starterLines, starterCols);

  return 0;
}
