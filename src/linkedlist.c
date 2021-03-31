#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

// Given a pointer to pointer to the head of the list
// and add the new node to the end of the list
void add(struct list_element* head, int new_data) {
	struct list_element new_node;
	struct list_element* cur = head;
	// put the new value in the new node
	new_node.data = new_data;
	new_node.next = NULL;
	// if the list is empty, new node is head node
	if (head == NULL) {
		*head = new_node;
		return;
	}
	// else put the new node in the end of list
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = &new_node;
	return;
}


// Given a pointer to pointer to the head of the list
// and delete the node which hold the certain value
void remove_list(struct list_element* head, int value) {
	struct list_element* temp = head;
	// if list is empty
	
	if (temp == NULL) {
		return;
	}
	// if head is the node which we want to delete
	if (temp->data == value) {	
		head = temp->next;
		return;
	}

	// itearate the whole list to find the node which contains the certain value
	while (temp->next != NULL){
		struct list_element* cur_next = temp->next;
		if (cur_next->data = value) {
			temp->next = cur_next->next;
			break;
		}
		temp = temp->next;
	}
}

void print_list(struct list_element* head) {
        while (head != NULL) {
	       head = head->next;
        }
}
