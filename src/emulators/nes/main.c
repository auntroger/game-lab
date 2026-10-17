#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

// No multiplication?
// No division?

#define BYTES_TO_KB 1024 // 1024 bytes = 1 kilobyte

#ifdef __INTELLISENSE__
    #define PACKED
#else
    #define PACKED __attribute__((packed))
#endif

typedef struct PACKED {
    char magic[4];
    uint8_t programROMcount;
    uint8_t charRAMcount;
    uint8_t flags;
    char padding[9];
} NESHeader;

// General Purpose Registers
int A; // Accumulator
int X; // Index Register X
int Y; // Index Register Y

// Program Registers
int PC; // Program Counter
int SP; // Stack Pointer

int P; // Status Register

uint8_t* memoryBuffer;

void hexDump(uint8_t* buffer) {
    for (int i = 0; i < 4; i++) {
        printf("%02X ", buffer[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Invalid amount of arguments. Please input a filepath to a .nes ROM file. \n");
        return -1;
    }

    const char* filePath = argv[1];

    FILE* romPointer;
    romPointer = fopen(filePath, "rb");

    if (romPointer == NULL) {
        printf("No valid ROM provided. Please reboot and provide a valid ROM. \n");
        return -1;
    }

    NESHeader fileHeader;
    fread(&fileHeader, sizeof(NESHeader), 1, romPointer);

    if (memcmp(fileHeader.magic, "NES\x1A", 4) != 0) { // Magic must equal "NES" and 0x1A
        printf("This ROM is invalid. Please reboot and provide a valid ROM. \n");
        return -1;
    }

    if (fileHeader.programROMcount > 2) { // Max cartridge program size is 32kb
        printf("This ROM is too big. Please reboot and provide a valid ROM. \n");
        return -1;
    }

    if (fileHeader.charRAMcount > 1) { // Max cartridge graphic ROM size is 8kb
        printf("This ROM is too big. Please reboot and provide a valid ROM. \n");
        return -1;
    }

    memoryBuffer = malloc(sizeof(uint8_t) * BYTES_TO_KB * 64); // Allocate 64kb of Memory simulating the 64kb memory in the 6502 chip

    if (memoryBuffer == NULL) {
        printf("Insufficient memory to run the emulator. \n");
        printf("Try: \n");
        printf("  - Closing background apps \n");
        printf("  - Restarting your computer \n");
        printf("Then try booting the emulator again. \n");
        return -1;
    }

    size_t size = sizeof(uint8_t) * BYTES_TO_KB * 16 * fileHeader.programROMcount; // Use 16kb per every 16kb chunk of program data

    fread(memoryBuffer + 0x8000, size, 1, romPointer); // Pulls the program into the computers memory

    free(memoryBuffer);

    return 0;
}
