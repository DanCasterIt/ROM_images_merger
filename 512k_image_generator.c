#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define ROM_SIZE			0x10000
#define PARTITIONS_NUMBER	4
#define INC					(ROM_SIZE/PARTITIONS_NUMBER)

#define sOFFSET1 0
#define sOFFSET2 INC
#define sOFFSET3 2*INC
#define sOFFSET4 3*INC

#define eOFFSET1 sOFFSET2-1
#define eOFFSET2 sOFFSET3-1
#define eOFFSET3 sOFFSET4-1
#define eOFFSET4 ROM_SIZE - 1

typedef struct partitions_s	{
	uint16_t start;
	uint16_t end;
	char *name;
} partitions_t;

int main(int argc, char *argv[])	{
	uint8_t buffer[INC];
	FILE *fdin, *fdout;
	char *tmp, ch = 'n';
	int i, a, b;
	partitions_t part[] = {
		{sOFFSET4, eOFFSET4, NULL},
		{sOFFSET3, eOFFSET3, NULL},
		{sOFFSET2, eOFFSET2, NULL},
		{sOFFSET1, eOFFSET1, NULL}
	};
	if(!(argc <= PARTITIONS_NUMBER + 1) || !(argc > 1)) return -1;
	for(i = 1; i < argc; i++)	part[i - 1].name = argv[i];
	printf("Found %d files. Choose where to place them.\n", argc - 1);
	while(ch != 'y')	{
		for(i = PARTITIONS_NUMBER - 1; i >= 0; i--)	{
			printf("partition %d, ", i);
			if(part[i].name != NULL)	printf("@ 0x%04X-0x%04X\tfile: %s\n", part[i].start, part[i].end, part[i].name);
			else	printf("@ 0x%04X-0x%04X\tones\n", part[i].start, part[i].end);
		}
		printf("Apply changes? (y or n): ");
		ch = getch();
		printf("%c", ch);
		if(ch == 'y') continue;
		printf("\nPlease, select which partition to swap.\n");
		printf("Partition number: ");
		a = getch() - 48;
		printf("%d", a);
		printf(" goes to number: ", i);
		b = getch() - 48;
		printf("%d\n", b);
		tmp = part[a].name;
		part[a].name = part[b].name;
		part[b].name = tmp;
	}
	printf("\nWriting \"512k_ROM_image.bin\"...\n");
	fdout = fopen("512k_ROM_image.bin", "wb");
	if(fdout == NULL) return -1;
	for(i = PARTITIONS_NUMBER - 1; i >= 0; i--)	{
		if(part[i].name != NULL)	{
			fdin = fopen(part[i].name, "rb");
			if(fdin == NULL) return -1;
			if(fread((void*)buffer, 1, INC, fdin) <= 0) return -1;
			if(fwrite((void*)buffer, 1, INC, fdout) <= 0) return -1;
			fclose(fdin);
		} else	{
			memset((void*)buffer, 0xFF, INC);
			if(fwrite((void*)buffer, 1, INC, fdout) <= 0) return -1;
		}
	}
	fclose(fdout);
	return 0;
}
