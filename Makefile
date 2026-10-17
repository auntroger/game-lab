CC = gcc
TARGET = build/nes.exe
EM_FOLDER = src/emulators/nes
SRCS = $(EM_FOLDER)/main.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)