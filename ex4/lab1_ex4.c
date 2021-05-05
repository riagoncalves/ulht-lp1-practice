#include <stdio.h>
#include <ctype.h> 

#define SIZE 166

int stringLength(char text[]) {
   int i = 0;

   while (text[i] != '\0') {
    i++;
   }

   return i;
}

int execution(char previousText[SIZE]) {

  char text[SIZE] = "",
      rotatedString[SIZE] = "",
      finalString[SIZE] = "",
      option,
      alphabet[SIZE] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  int positions,
      baseIndex,
      i,
      j,
      limit,
      textLen,
      fullRotations,
      fullRotationsChars,
      trueIndex;

  scanf(" %c", &option);

  if(option == 'r' || option == 's') {
    scanf("%d %[^\n]s", &positions, text);
  }
  
  switch (option)
  {
  case 'r':
    textLen = stringLength(text);

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

      limit = stringLength(finalString);

      for (i = 0, j = limit; i < baseIndex; i++, j++)
      {
        finalString[j] = text[i];
      }

      i = 0;
      while (finalString[i] != '\0') {
        rotatedString[i] = finalString[i];
        i++;
      }
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

      limit = stringLength(finalString);

      for (i = 0, j = limit; i < baseIndex; i++, j++)
      {
        finalString[j] = text[i];
      }

      i = 0;
      while (finalString[i] != '\0') {
        rotatedString[i] = finalString[i];
        i++;
      }
    }

    printf("%s\n", rotatedString);

    return execution(rotatedString);

    break;

  case 'h':
    printf("%s\n", previousText);

    break;

  case 's':
    if(positions >= -35 && positions <= 35) {		
      i = 0;
      while (text[i] != '\0') {
        text[i] = toupper(text[i]);
        i++;
      }

      i = 0;
      while (text[i] != '\0') {
        j = 0;

        while (alphabet[j] != '\0') {
          
          if (alphabet[j] == text[i]) {
            baseIndex = j;
            break;
          }

          j++;
        }

        if(j < 36) {
          trueIndex = baseIndex + positions;

          if (trueIndex > 35) {
            trueIndex = trueIndex - 36;
          }
          else if (trueIndex < 0) {
            trueIndex = 36 + trueIndex;
          }

          text[i] = alphabet[trueIndex];
        }

        i++;
      }

      printf("%s\n", text);
      return execution(text);
    }
    else {
      puts("Error: out of bound");
    }
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