/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    // General Purpose Registers
    uint8_t A; // Accumulator
    uint8_t X; // Index Register X
    uint8_t Y; // Index Register Y

    // Program Registers
    uint16_t PC; // Program Counter
    uint8_t SP; // Stack Pointer

    uint8_t P; // Status Register

    uint8_t* memory;
} CPU6502;

CPU6502* newCPU();
int fetch(CPU6502* cpu);
int decode(CPU6502* cpu, uint8_t opcode);
int execute(CPU6502* cpu, uint8_t opcode, uint16_t operands);
void unactivateCPU(CPU6502* cpu);
