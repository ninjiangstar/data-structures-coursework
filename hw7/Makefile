all: clean Exam bin/.dirstamp tests/BST tests/AVL

Exam: exam.cpp avlbst.h bst.h
	g++ -g -Wall $< $(GTEST_LL) -o $@

tests/BST: bst_test.cpp bst.h
	g++ -g -Wall $< $(GTEST_LL) -o $@

tests/AVL: avl_test.cpp avlbst.h bst.h
	g++ -g -Wall $< $(GTEST_LL) -o $@

clean:
	rm -rf Exam
	rm -rf tests

bin/.dirstamp:
	mkdir -p tests
	touch tests/.dirstamp
