#include <stdio.h>
#include <dos.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

struct BOOT {  // For FAT16
    char jmp[3];
    char OEM[8];
    int bytes_per_sector;
    char sectors_per_cluster;
    int reserved;
    char FAT_cnt;
    int ROOT_size;
    int total_sectors;
    char media;
    int FAT_size;
    int sectors_per_track;
    int head_cnt;
    long hidden_sectors;
    long total_sectors_long;
    char unknown[3];
    long serial;
    char volume[11];
    char FAT_type[8];
    char loader[448];
    char mark[2];
};

void main() {
    int drive = 3; // A=0, B=1, C=2, D=3 ...
    BOOT boot;

    // Reading boot sector from disk D
    int res = absread(drive, 1, 0, &boot);
    if(res != 0){
        printf("Cannot read boot sector\n");
        return;
    }

    // Reading FAT16 table from disk D
    unsigned int *fat = (unsigned int *)malloc(boot.FAT_size * boot.bytes_per_sector);
    if (fat == NULL) {
        printf("Not enough memory\n");
        return;
    }

    res = absread(drive, boot.FAT_size, boot.reserved, fat);
    if(res != 0){
        printf("Cannot read FAT\n");
        return;
    }

    // Printing first 150 FAT entries
    printf("Content of first 150 FAT entries:\n");
    for (int i = 0; i < 150; i++) {
        printf("%u ", fat[i]);
    }
    printf("\n");

    free(fat);
}
