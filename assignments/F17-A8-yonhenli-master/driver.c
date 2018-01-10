#include <stdio.h>
#include <stdlib.h>
#include "node.h"

Node na;

int main () {

	
	Node nb;
	
	Node *nc = (Node *)malloc(sizeof(Node));

	Node *nd = (Node *)malloc(sizeof(Node));
	
	na.prev = NULL;
	na.next = &nb;
	nb.prev = &na;
	nb.next = nc;
	nc -> prev = &nb;
       	nc -> next = nd;
	nd -> prev = nc;
       	nd -> next = NULL;	
	
	printf("address 1: %lx\n", &na);
	printf("address 2: %lx\n", &nb);
	printf("address 3: %lx\n", nc);
	printf("address 4: %lx\n", nd);
	
	Node *head = sort_nodes(&na);
	
	printf("address 1: %lx\n", head);
	printf("address 1 prev: %lx\n", head->prev);
	printf("address 2: %lx\n", head -> next);
	printf("address 2 prev: %lx\n", head -> next -> prev);
	printf("address 3: %lx\n", head -> next -> next);
	printf("address 3 prev: %lx\n", head -> next -> next -> prev);
	printf("address 4: %lx\n", head -> next -> next -> next);
	printf("address 4 prev: %lx\n", head -> next -> next -> next ->prev);
	return 0;
}
