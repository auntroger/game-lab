#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

// No multiplication?
// No division?

// General Purpose Registers
int A; // Accumulator
int X; // Index Register X
int Y; // Index Register Y

// Program Registers
int PC; // Program Counter
int SP; // Stack Pointer

int P; // Status Register

void hexDump(uint8_t* buffer) {
    for (int i = 0; i < 4; i++) {
        printf("%02X ", buffer[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Invalid amount of arguments. Please input a filepath to a .nes ROM file.");
        return -1;
    }

    const char* filePath = argv[1];

    FILE* romPointer;
    romPointer = fopen(filePath, "rb");

    if (romPointer == NULL) {
        printf("No valid ROM provided. Please reboot and provide a valid ROM.");
        return -1;
    }

    uint8_t buffer[4];
    fread(buffer, sizeof(uint8_t), 4, romPointer);

    hexDump(buffer);

    return 0;
}
