all: clean zipf

zipf: report.cpp hash.h splay.h bst.h Map.h
	g++ -O3 -Wall $< $(GTEST_LL) -o $@

clean:
	rm -rf zipf