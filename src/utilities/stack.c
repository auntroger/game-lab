#include <stack.h>

Stack* newStack() {
    Stack* stack = malloc(sizeof(Stack));

    if (stack == NULL) {
        return NULL;
    }

    stack->capacity = 64;

    stack->stack = malloc(stack->capacity);

    if (stack->stack == NULL) {
        free(stack);
        return NULL;
    }

    stack->stackPointer = 0;

    return stack;
}

int push(Stack* stack, void* data) {
    if (stack->stackPointer == stack->capacity - 1) {
        void* moreData = realloc(stack->stack, stack->capacity * 2);

        if (moreData == NULL) {
            return -1;
        }

        stack->stack = moreData;
        stack->capacity = stack->capacity * 2;
    }

    stack->stack[stack->stackPointer] = data;
    stack->stackPointer++;

    return 0;
}

void* pop(Stack* stack) {
    if (stack->stackPointer < 0) {
        printf("Nothing left to pop! \n");
        return NULL;
    }

    stack->stackPointer = stack->stackPointer - 1;

    return stack->stack[stack->stackPointer];
}

void destroyStack(Stack* stack) {
    free(stack->stack);
    free(stack);
}