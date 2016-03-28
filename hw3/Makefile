GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: clean bin/.dirstamp tests bin/parse

bin/llisttest: bin/llistint.o llisttest.cpp
	g++ -g -Wall $^ $(GTEST_LL) -o $@

bin/parse: bin/llistint.o bin/stackint.o parse.cpp
	g++ -g -Wall $^ -o $@

bin/llistint.o: llistint.cpp llistint.h
	g++ -g -Wall -c $< -o $@
	
bin/stackint.o: stackint.cpp stackint.h
	g++ -g -Wall -c $< -o $@

clean:
	rm -rf bin

bin/.dirstamp:
	mkdir -p bin
	touch bin/.dirstamp

tests: bin/llisttest
	-@bin/llisttest
	-@echo "--- All Tested!---"
