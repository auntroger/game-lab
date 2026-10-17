#include <6502.h>

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

// This code emulates a 6502 CPU used in NES consoles

#define BYTES_TO_KB 1024 // 1024 bytes = 1 kilobyte

CPU6502* newCPU() {
    CPU6502* cpu = malloc(sizeof(CPU6502));
    
    if (cpu == NULL) {
        return NULL;
    }

    cpu->memory = malloc(sizeof(uint8_t) * BYTES_TO_KB * 64); // Allocate 64kb of Memory simulating the 64kb memory in the 6502 chip

    if (cpu->memory == NULL) {
        free(cpu);
        return NULL;
    }

    cpu->PC = 0x8000;
    cpu->SP = 0xFD;

    return cpu;
}

void unactivateCPU(CPU6502* cpu) {
    free(cpu->memory);
    free(cpu);
}
