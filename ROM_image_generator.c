#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct partitions_s {
  uint16_t start;
  uint16_t end;
  char *name;
} partitions_t;

int main(int argc, char *argv[]) {
  FILE *fdin, *fdout;
  char *tmp, ch = 'n';
  int inc, partitions_number, rom_size, i, a, b;
  uint8_t filler;
  printf("Input the memory size in bytes. (0 for 65536): ");
  scanf("%d", &rom_size);
  getchar();
  if (rom_size <= 0)
    rom_size = 65536;
  printf("Input the number of equally sized partitions. (0 for 4): ");
  scanf("%d", &partitions_number);
  getchar();
  if (partitions_number <= 0)
    partitions_number = 4;
  do {
    printf("Input if to fill blank partitions with ones (1) or zeros (0): ");
    scanf("%hhu", &filler);
    getchar();
    if (filler != 1 && filler != 0)
      printf("Input 1 or 0.\n");
  } while (filler != 1 && filler != 0);
  if (filler == 1)
    filler = 0xFF;
  else
    filler = 0x00;
  if (argc > partitions_number + 1)
    return -1;
  inc = rom_size / partitions_number;
  uint8_t buffer[inc];
  partitions_t part[partitions_number];
  for (i = 0; i < partitions_number; i++) {
    part[partitions_number - 1 - i].start = i * inc;
    part[partitions_number - 1 - i].end = ((i + 1) * inc) - 1;
    part[partitions_number - 1 - i].name = NULL;
  }
  for (i = 1; i < argc; i++)
    part[i - 1].name = argv[i];
  printf("Found %d files. Choose where to place them.\n", argc - 1);
  while (ch != 'y') {
    for (i = partitions_number - 1; i >= 0; i--) {
      printf("partition %d ", i);
      if (part[i].name != NULL)
        printf("@ 0x%08X-0x%08X filled with file: %s\n", part[i].start,
               part[i].end, part[i].name);
      else
        printf("@ 0x%08X-0x%08X filled with %02Xs\n", part[i].start,
               part[i].end, filler);
    }
    printf("Apply changes? (y or n): ");
    scanf("%c", &ch);
    getchar();
    if (ch == 'y')
      continue;
    printf("Input which partition to swap.\n");
    do {
      printf("Partition number: ");
      scanf("%d", &a);
      getchar();
      if (a >= partitions_number)
        printf("Input a number less than %d.\n", partitions_number);
    } while (a >= partitions_number);
    do {
      printf("goes to number: ");
      scanf("%d", &b);
      getchar();
      if (b >= partitions_number)
        printf("Input a number less than %d.\n", partitions_number);
    } while (b >= partitions_number);
    tmp = part[a].name;
    part[a].name = part[b].name;
    part[b].name = tmp;
  }
  printf("Writing \"ROM_image.bin\"...\n");
  fdout = fopen("ROM_image.bin", "wb");
  if (fdout == NULL)
    return -1;
  for (i = partitions_number - 1; i >= 0; i--) {
    memset((void *)buffer, filler, inc);
    if (part[i].name != NULL) {
      fdin = fopen(part[i].name, "rb");
      if (fdin == NULL)
        return -1;
      if (fread((void *)buffer, 1, inc, fdin) <= 0)
        return -1;
      if (fwrite((void *)buffer, 1, inc, fdout) <= 0)
        return -1;
      fclose(fdin);
    } else if (fwrite((void *)buffer, 1, inc, fdout) <= 0)
      return -1;
  }
  fclose(fdout);
  return 0;
}
