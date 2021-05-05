#include <stdio.h>

int main() {

  int n1;
  unsigned int n2, n3;

  puts("Wellcome to number informer v1");
  puts("Please insert Number 1 in Decimal:");
  scanf("%d", &n1);

  puts("Please insert Number 2 in Hexadecimal:");
  scanf("%x", &n2);

  puts("Please insert Number 3 in Octal:");
  scanf("%o", &n3);

  puts("+-----+--------+------+--------+--------+------+--------+");
  puts("| Nr. | Dec    | Hex  | Oct    | -Dec   | -Hex | -Oct   |");
  puts("+-----+--------+------+--------+--------+------+--------+");
  printf("| 1   | %06hd | %04hX | %06ho | %06hd | %04hx | %06ho |\n", n1, n1, n1, n1 * (-1), n1 * (-1), n1 * (-1));
  printf("| 2   | %06hd | %04hX | %06ho | %06hd | %04hx | %06ho |\n", n2, n2, n2, n2 * (-1), n2 * (-1), n2 * (-1));
  printf("| 3   | %06hd | %04hX | %06ho | %06hd | %04hx | %06ho |\n", n3, n3, n3, n3 * (-1), n3 * (-1), n3 * (-1));
  puts("+-----+--------+------+--------+--------+------+--------+");

  return 0;
}