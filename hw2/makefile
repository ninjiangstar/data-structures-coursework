CXX = g++ -g -Wall
BIN = bin

all: .PHONY $(BIN)/.dirstamp $(BIN)/problem7part2 $(BIN)/problem6.o
	./$(BIN)/problem7part2

$(BIN)/problem7part2: $(BIN)/llistint.o problem7part2.cpp
	$(CXX) $^ -o $@

$(BIN)/llistint.o: llistint.cpp llistint.h
	$(CXX) -c $< -o $@
	
$(BIN)/problem6.o: problem6.cpp
	$(CXX) -c $< -o $@

$(BIN)/.dirstamp:
	mkdir -p $(BIN)
	touch $(BIN)/.dirstamp

.PHONY: clean
clean:
	rm -rf $(BIN)
