#include "heap.h"

using namespace std;

int main() {

	MinHeap<int> heap(3, NULL); // create triary heap

	for(int i = 35; i > 0; i--){
		heap.add(i,i); // add in backwards order
	}

	while(!heap.isEmpty()){
		cout << heap.peek() << endl; // output in sorted order
		heap.remove();
	}

	return 0;
}