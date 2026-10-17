/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void** stack;
    int stackPointer;
    int capacity;
} Stack;

Stack* newStack();
int push(Stack* stack, void* data);
void* pop(Stack* stack);
void destroyStack(Stack* stack);