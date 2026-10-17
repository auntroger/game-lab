#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

// Note: This edition is a test to simply output an NES compatible cartridge

#ifdef __INTELLISENSE__
    #define PACKED
#else
    #define PACKED __attribute__((packed))
#endif

#define BYTES_TO_KB 1024 // 1024 bytes = 1 kilobyte

// Requires magic 0x4E, 0x45, 0x53, 0x1A or "NES" followed by a newline char
typedef struct PACKED {
    char magic[4];
    uint8_t programROMcount;
    uint8_t charRAMcount;
    uint8_t flags;
    char padding[9];
} NESHeader;

int main() {
    char programData[4] = { 0xA9, 0x02, 0x69, 0x02 }; // Executes 2 + 2
    char padding[BYTES_TO_KB * 16 - 4] = { 0 };

    NESHeader header;
    header.magic[0] = 'N';
    header.magic[1] = 'E';
    header.magic[2] = 'S';
    header.magic[3] = 0x1A;

    header.programROMcount = 1;
    header.charRAMcount = 0;
    header.flags = 0;

    FILE* file;
    file = fopen("testPrograms/tpt.nes", "wb");

    if (file == NULL) {
        printf("Failed to open file. \n");
        return -1;
    }

    if (fwrite(&header, sizeof(NESHeader), 1, file) != 1) {
        printf("Error writing file header to program. \n");

        fclose(file);

        return -1;
    }

    if (fwrite(programData, sizeof(programData), 1, file) != 1) {
        printf("Error writing program data to program. \n");

        fclose(file);

        return -1;
    }

    if (fwrite(padding, sizeof(padding), 1, file) != 1) {
        printf("Error writing padding to program. \n");

        fclose(file);

        return -1;
    }

    printf("Succesfully generated test program. \n");

    fclose(file);

    return 0;
}