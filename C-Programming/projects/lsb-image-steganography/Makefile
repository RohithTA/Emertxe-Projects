.RECIPEPREFIX = >

CC      = gcc
CFLAGS  = -Wall -g
TARGET  = stego
SRC     = $(wildcard src/*.c)
HDR     = $(wildcard src/*.h)

all: $(TARGET)

$(TARGET): $(SRC) $(HDR)
> $(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
> rm -f $(TARGET) $(TARGET).exe stego.bmp decode.*

.PHONY: all clean
