#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct partitions_s {
  uint32_t start;
  uint32_t end;
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
  if (argc > partitions_number + 1) {
    fprintf(stderr, "ERROR: the number of partitions to merge together (%d) is lower than the number of file passed through the command line (%d).\n", partitions_number, argc - 1 );
    return -1;
  }

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

  inc = rom_size / partitions_number;
  uint8_t buffer[inc];
  partitions_t part[partitions_number];
  for (i = 0; i < partitions_number; i++) {
    part[i].start = i * inc;
    part[i].end = ((i + 1) * inc) - 1;
    part[i].name = (i > argc - 2) ? NULL : argv[i + 1];
  }

  printf("Found %d files. Choose where to place them.\n", argc - 1);
  while (ch != 'y') {
    for (i = 0; i < partitions_number; i++) {
      printf("partition %d ", i);
      if (part[i].name)
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

  char output_file_name[] = "ROM_image.bin";
  printf("Writing \"%s\"...\n", output_file_name);
  fdout = fopen(output_file_name, "wb");
  if (!fdout) {
    fprintf(stderr, "ERROR: can't open or create \"%s\"\n", output_file_name);
    goto exit_with_error;
  }
  for (i = 0; i < partitions_number; i++) {
    memset((void *)buffer, filler, inc);
    if (part[i].name) {
      fdin = fopen(part[i].name, "rb");
      if (!fdin)  {
        fprintf(stderr, "ERROR: can't open \"%s\", does it exist?\n", part[i].name);
        goto exit_with_error;
      }
      if (fread((void *)buffer, 1, inc, fdin) <= 0) {
        fprintf(stderr, "ERROR: can't read \"%s\", do we have read permissions?\n", part[i].name);
        fclose(fdin);
        goto exit_with_error;
      }
      if (fwrite((void *)buffer, 1, inc, fdout) <= 0) {
        fprintf(stderr, "ERROR: can't write \"%s\", do we have write permissions?\n", output_file_name);
        fclose(fdin);
        goto exit_with_error;
      }
      fclose(fdin);
    } else if (fwrite((void *)buffer, 1, inc, fdout) <= 0)
      goto exit_with_error;
  }

  fclose(fdout);
  return 0;

exit_with_error:
  fprintf(stderr, "ERROR: \"%s\" not created or incomplete.\n", output_file_name);
  if(fdout)
    fclose(fdout);
  return -1;
}
