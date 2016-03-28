#include <cstddef>

struct Node {
	int value;
	Node *next;
};

Node* merge(Node*& first, Node*& second){
	
	Node* merged = NULL;

	// BASE CASES
	if(first == NULL && second == NULL){
		return merged;
	}
	if(first && second == NULL){
		merged = first;
		merged->next = merge(first->next, second);
	}
	if(first == NULL && second){
		merged = second;
		merged->next = merge(second->next, first); // order doesn't matter here
	}

	// THE REAL SHIT
	if(first && second){
		// smaller values get recursed first
		if(first->value <= second->value){
			merged = first;
			merged->next = merge(first->next,second);
		}
		else if(first->value > second->value){
			merged = second;
			merged->next = merge(first, second->next);
		}
	}

	first = NULL;
	second = NULL;

	return merged;

}
