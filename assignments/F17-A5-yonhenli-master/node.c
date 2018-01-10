#include "node.h"
#include <stdio.h>

Node *my_reverse(Node *head) {
    void *preVP;
    void *nextVP;
	Node *currN;
    Node *nextN;
	
	preVP = NULL;
    currN = head;
	
    nextVP = currN -> ptr;
    nextN = (Node*)(nextVP - 8);
	
    currN -> ptr = NULL;
    preVP = &(currN -> ptr);
    currN = nextN;
	
    while(currN -> ptr != NULL){
            nextVP = currN -> ptr;
            nextN = (Node*)(nextVP - 8);

            currN -> ptr = preVP;
            preVP = &(currN -> ptr);
			currN = nextN;
    }
	
    currN -> ptr = preVP;

	return currN;
}

