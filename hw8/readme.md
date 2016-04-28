# CS 104 HW8

## To run zipf
* run `make`
* run `./zipf`
* input 4 for splay, 5 for hash tables
* input file name
* output to report.out
* enjoy.

# Problem 6
* I tried the full text of Hamlet, the full text of Tale of Two Cities, as well as a 3mb file of Lorem Ipsum.
* Hash tables is faster for much larger text files. It was typically logn times as fast as Splay Trees. But then again, outputing is not alphabetical.
* The average runtime of Hash Tables insertion is O(1) and worst case O(n). The average and worst runtime of Splay Trees insertion is O(logn). We are given one guaruntee that the words are random, so hashing won't experience too many collisions, thus it runs closer to its amortized O(1). Plus, the only constant factor for Hash Tables is the process of hashing, while the constant for Splay Trees is the rotations made during splaying, which becomes more and more costly the larger the text file is. For smaller text files, both should be roughly equivalent in speed. 

* runtime comparisons (insertion of one element)
	* For adding, unsorted lists are slower than hash because unsorted lists need to scan through the existing list to determine incrementing or adding a new value, making insertion O(n) every time. Hash insertion amortized is O(1), but worst time is equivalent to unsorted list O(n). This makes sorted lists slower than Splay Trees too, which has a worst-case runtime of O(logn).
	* Sorted list is going to be even slower than unsorted lists in this situation, no matter what way you implement it. Since the key is a string, there is no way to determine the position in the sorted list given a string, thus we still have to scan the entire list for the position. And after each insertion, we have to re-sort everything, which can be as fast as O(nlogn). So the speed of adding and sorting is worst case O(n^2 * logn). This is the worst.
	* BST non-rotating is supposed to be slower than splay because insertion in splay is worst-case O(logn) and insertion in BST is worst-case O(n), however due to the expensive nature of making rotations, BST can sometimes appear faster in a non-uniform large input. But it should be still slower than Hash because Hash is O(1).
	* BST AVL Balancing should be slightly slower than splay trees because it rotates more frequently than splay trees. Also in terms of zipf distribution, it will be faster to access the most-used terms (which will be closer to the top) than to have a height-balanced tree where common terms may be at the very bottom.