#include <stdio.h>
#include <string.h>

#define SIZE 166

int execution(char previousText[SIZE]) {

  char text[SIZE] = "",
      rotatedString[SIZE] = "",
      finalString[SIZE] = "",
      option;

  int positions,
      baseIndex,
      i,
      j,
      limit,
      textLen,
      fullRotations,
      fullRotationsChars;

  scanf(" %c", &option);

  if(option == 'r') {
    scanf("%d %[^\n]s", &positions, text);
  }
  
  switch (option)
  {
  case 'r':
    textLen = strlen(text);

    if (positions < 0) {
      baseIndex = positions * -1;

      if (baseIndex > textLen) {
        fullRotations = baseIndex / textLen;
        fullRotationsChars = textLen * fullRotations;
        baseIndex = baseIndex - fullRotationsChars;
      }

      limit = textLen;

      for (i = baseIndex, j = 0; i < limit; i++, j++)
      {
        finalString[j] = text[i];
      }

      limit = strlen(finalString);

      for (i = 0, j = limit; i < baseIndex; i++, j++)
      {
        finalString[j] = text[i];
      }

      strcpy(rotatedString, finalString);
    }

    else {
      
      if (positions > textLen) {
        fullRotations = positions / textLen;
        fullRotationsChars = textLen * fullRotations;
        positions = positions - fullRotationsChars;
      }

      baseIndex = textLen - positions;
      limit = textLen;

      for (i = baseIndex, j = 0; i < limit; i++, j++)
      {
        finalString[j] = text[i];
      }

      limit = strlen(finalString);

      for (i = 0, j = limit; i < baseIndex; i++, j++)
      {
        finalString[j] = text[i];
      }

      strcpy(rotatedString, finalString);
    }

    printf("%s\n", rotatedString);

    return execution(rotatedString);

    break;

  case 'h':
    printf("%s\n", previousText);

    break;

  case 'q':
    puts("Exiting->");
    return 0;

    break;

  default:
    puts("Error: Unknown option");
    break;
  }
  
  return execution(previousText);
}


int main() {
  execution("");
  return 0;
}