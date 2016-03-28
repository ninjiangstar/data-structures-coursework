all: clean bin/.dirstamp bin/Facile

bin/Facile: Facile.cpp bin/Statements.o bin/ProgramState.o bin/stackint.o bin/llistint.o
	g++ -g -Wall $^ $(GTEST_LL) -o $@

bin/Statements.o: Statements.cpp Statements.h Statement.h
	g++ -g -Wall -c $< -o $@

bin/ProgramState.o: ProgramState.cpp ProgramState.h
	g++ -g -Wall -c $< -o $@

bin/stackint.o: stackint.cpp stackint.h
	g++ -g -Wall -c $< -o $@

bin/llistint.o: llistint.cpp llistint.h
	g++ -g -Wall -c $< -o $@

clean:
	rm -rf bin

bin/.dirstamp:
	mkdir -p bin
	touch bin/.dirstamp
