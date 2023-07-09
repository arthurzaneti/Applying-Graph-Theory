CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
BIN_DIR = bin
SRC_DIR = src
HEADER_DIR = headers

all: $(BIN_DIR)/programa

$(BIN_DIR)/programa: $(BIN_DIR)/lista.o $(BIN_DIR)/grafo.o $(BIN_DIR)/aresta.o $(BIN_DIR)/main.o $(BIN_DIR)/arq_manager.o $(BIN_DIR)/calcula_distancia.o $(BIN_DIR)/caminho.o $(BIN_DIR)/ufsm.o $(BIN_DIR)/heap.o $(BIN_DIR)/algoritmos.o
	$(CC) -o $@ $^ $(CFLAGS) -lm

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

$(BIN_DIR)/calcula_distancia.o: $(SRC_DIR)/calcula_distancia.c $(HEADER_DIR)/calcula_distancia.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/caminho.o: $(SRC_DIR)/caminho.c $(HEADER_DIR)/caminho.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/ufsm.o: $(SRC_DIR)/ufsm.c $(HEADER_DIR)/ufsm.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/heap.o: $(SRC_DIR)/heap.c $(HEADER_DIR)/heap.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/algoritmos.o: $(SRC_DIR)/algoritmos.c $(HEADER_DIR)/algoritmos.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/programa
