#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct partitions_s	{
	uint16_t start;
	uint16_t end;
	char *name;
} partitions_t;

int main(int argc, char *argv[])	{
	FILE *fdin, *fdout;
	char *tmp, ch = 'n';
	int INC, PARTITIONS_NUMBER, ROM_SIZE, i, a, b;
	uint8_t filler;
	printf("Please, specify the memory size in bytes. (0 for 65536): ");
	scanf("%d", &ROM_SIZE);
	getchar();
	if(ROM_SIZE <= 0) ROM_SIZE = 65536;
	printf("Please, specify the number of equally sized partitions. (0 for 4): ");
	scanf("%d", &PARTITIONS_NUMBER);
	getchar();
	if(PARTITIONS_NUMBER <= 0) PARTITIONS_NUMBER = 4;
	do	{
		printf("Please, specify if to fill blank partitions with ones (1) or zeros (0): ");
		scanf("%d", &filler);
		getchar();
		if(filler != 1 && filler != 0)	printf("Please, input 1 or 0.\n");
	} while(filler != 1 && filler != 0);
	if(filler == 1) filler = 0xFF;
	else filler = 0x00;
	if(!(argc <= PARTITIONS_NUMBER + 1)) return -1;
	INC = ROM_SIZE/PARTITIONS_NUMBER;
	uint8_t buffer[INC];
	partitions_t part[PARTITIONS_NUMBER];
	for(i = 0; i < PARTITIONS_NUMBER; i++)	{
		part[PARTITIONS_NUMBER - 1 - i].start = i * INC;
		part[PARTITIONS_NUMBER - 1 - i].end = ((i + 1) * INC) - 1;
		part[PARTITIONS_NUMBER - 1 - i].name = NULL;
	}
	for(i = 1; i < argc; i++)	part[i - 1].name = argv[i];
	printf("Found %d files. Choose where to place them.\n", argc - 1);
	while(ch != 'y')	{
		for(i = PARTITIONS_NUMBER - 1; i >= 0; i--)	{
			printf("partition %d ", i);
			if(part[i].name != NULL)	printf("@ 0x%08X-0x%08X filled with file: %s\n", part[i].start, part[i].end, part[i].name);
			else	printf("@ 0x%08X-0x%08X filled with %02Xs\n", part[i].start, part[i].end, filler);
		}
		printf("Apply changes? (y or n): ");
		scanf("%c", &ch);
		getchar();
		if(ch == 'y') continue;
		printf("Please, select which partition to swap.\n");
		do	{
			printf("Partition number: ");
			scanf("%d", &a);
			getchar();
			if(a >= PARTITIONS_NUMBER) printf("Please, insert a number less than %d.\n", PARTITIONS_NUMBER);
		} while(a >= PARTITIONS_NUMBER);
		do	{
			printf("goes to number: ", i);
			scanf("%d", &b);
			getchar();
			if(b >= PARTITIONS_NUMBER) printf("Please, insert a number less than %d.\n", PARTITIONS_NUMBER);
		} while(b >= PARTITIONS_NUMBER);
		tmp = part[a].name;
		part[a].name = part[b].name;
		part[b].name = tmp;
	}
	printf("Writing \"ROM_image.bin\"...\n");
	fdout = fopen("ROM_image.bin", "wb");
	if(fdout == NULL) return -1;
	for(i = PARTITIONS_NUMBER - 1; i >= 0; i--)	{
		memset((void*)buffer, filler, INC);
		if(part[i].name != NULL)	{
			fdin = fopen(part[i].name, "rb");
			if(fdin == NULL) return -1;
			if(fread((void*)buffer, 1, INC, fdin) <= 0) return -1;
			if(fwrite((void*)buffer, 1, INC, fdout) <= 0) return -1;
			fclose(fdin);
		} else	if(fwrite((void*)buffer, 1, INC, fdout) <= 0) return -1;
	}
	fclose(fdout);
	return 0;
}
