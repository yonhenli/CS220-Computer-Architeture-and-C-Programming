#include "node.h"
#include <stdlib.h>
#include <stdio.h>

Node *sort_nodes(Node *head) {
	Node *out_node = head;
	Node *ins_node;
	Node *max_node = NULL;
	Node *temp;
	ins_node = out_node;
		
	while (out_node) {
		while (ins_node) {
			if (ins_node > max_node) {
				max_node = ins_node;					
			}
			ins_node = ins_node ->next;
		}
				
		temp = out_node -> next;

		if (!out_node -> prev) head = max_node;
		
		if (max_node > out_node) {
			swap(out_node, max_node);
		}

		if (max_node->next == out_node) {
			temp = out_node;
		}	

		ins_node = temp;
		out_node = temp;
		max_node = NULL;
	}
	return head;
}

void swap (Node *n1, Node *n2) {
	Node *n1_prev = n1 -> prev;
	Node *n1_next = n1 -> next;
	Node *n2_prev = n2 -> prev;
	Node *n2_next = n2 -> next;
	/*check whether two nodes are next to each other*/
	int check = 0;
	if (n1->next == n2) {
		check = 1;
	}

	/*STEP 1: move n2 to the position of n1*/
	/*if prev of n1 is null, we do nothing*/
	if (n1_prev) {
		n1_prev -> next = n2;
	}
	n2 -> prev = n1_prev;
	if (!check){
		n2 -> next = n1_next;
		n1_next -> prev = n2;
	}
	else {
		n2 -> next = n1;
		n1 -> prev = n2;	
	}

	/*STEP 2: move n1 to the position of n2*/
	if (!check) {
		n2_prev -> next = n1;
		n1 -> prev = n2_prev;
	}
	n1 -> next = n2_next;
	/*if next of n2 is null*/
	if (n2_next) {
       		n2_next -> prev = n1;
	}
}

