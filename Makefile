CC = gcc
FLAGS = -I include/
TARGET = build/nes.exe
EM_FOLDER = src/emulators/nes
SRCS = $(EM_FOLDER)/main.c $(EM_FOLDER)/6502.c src/utilities/stack.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)