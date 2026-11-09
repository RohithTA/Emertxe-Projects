.RECIPEPREFIX = >

CC      = gcc
CFLAGS  = -Wall -g
TARGET  = inverted_search
SRC     = $(wildcard src/*.c)
HDR     = $(wildcard src/*.h)

all: $(TARGET)

$(TARGET): $(SRC) $(HDR)
> $(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
> rm -f $(TARGET) $(TARGET).exe

.PHONY: all clean
