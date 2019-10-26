CC = g++
CFLAGS = -Wall
LDFLAGS =
OBJFILES = LORA_PC.o extra.o socket_functions.o io.o
TARGET = LORA

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
