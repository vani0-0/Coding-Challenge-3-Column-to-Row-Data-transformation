CC = gcc
CFLAGS = -g -Wall
SRC = src
OBJ = obj
BIN = bin

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

APP = $(BIN)/app

all: $(APP)

$(APP): $(OBJS) $(BIN)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	mkdir -p $@

$(BIN):
	mkdir -p $@

clean:
	$(RM) -r $(OBJ)
	$(RM) -r $(BIN)
