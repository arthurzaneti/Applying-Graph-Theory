CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
BIN_DIR = bin
SRC_DIR = src
HEADER_DIR = headers

all: $(BIN_DIR)/programa

$(BIN_DIR)/programa: $(BIN_DIR)/lista.o $(BIN_DIR)/grafo.o $(BIN_DIR)/aresta.o $(BIN_DIR)/main.o $(BIN_DIR)/arq_manager.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/lista.o: $(SRC_DIR)/lista.c $(HEADER_DIR)/lista.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/grafo.o: $(SRC_DIR)/grafo.c $(HEADER_DIR)/grafo.h $(HEADER_DIR)/lista.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/aresta.o: $(SRC_DIR)/aresta.c $(HEADER_DIR)/aresta.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/main.o: $(SRC_DIR)/main.c $(HEADER_DIR)/lista.h $(HEADER_DIR)/grafo.h $(HEADER_DIR)/aresta.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/arq_manager.o: $(SRC_DIR)/arq_manager.c $(HEADER_DIR)/arq_manager.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/programa

