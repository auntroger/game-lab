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

    cpu->PC = 0x8000; // Points to where the ROM is loaded in
    cpu->SP = 0xFD; // Points to 0x01FD on startup
    cpu->P = 0x24; // Startup status code

    return cpu;
}

int fetch(CPU6502* cpu) {
    if (cpu->PC > 64 * BYTES_TO_KB) {
        printf("Program got to the end of memory without halting! Stopping emulator immediately to prevent segmentation faults. \n");
        return -1;
    }

    uint8_t opcode = cpu->memory[cpu->PC];

    cpu->PC++;

    if (cpu->PC > 64 * BYTES_TO_KB) {
        printf("Program got to the end of memory without halting! Stopping emulator immediately to prevent segmentation faults. \n");
        return -1;
    }

    int expectedOperands = decode(cpu, opcode);

    if (expectedOperands == -1) {
        printf("Triple fault! Unexpected opcode: %02x! \n", opcode);
        return -1;
    }

    uint16_t operands = cpu->memory[cpu->PC];

    cpu->PC = cpu->PC + expectedOperands;

    execute(cpu, opcode, operands);

    return 0;
}

int decode(CPU6502* cpu, uint8_t opcode) {
    switch (opcode) {
        case 0x00: // No operation
            return 0;
        case 0x69: // Add immediate instruction
            return 1;
        case 0xA9: // Load accumulator instruction
            return 1;
        default:
            return -1;
    }
}

int execute(CPU6502* cpu, uint8_t opcode, uint16_t operands) {
    switch (opcode) {
        case 0x69: // Add immediate instruction
            cpu->A = cpu->A + (uint8_t)operands;

            return 0;
        case 0xA9: // Load accumulator instruction
            cpu->A = (uint8_t)operands;
            return 0;
    }
}

void unactivateCPU(CPU6502* cpu) {
    free(cpu->memory);
    free(cpu);
}
